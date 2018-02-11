#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

const int LAYERNUMBER = 9;

const int resolucao = 100;

struct point {
    int x;
    int y;
};
struct node {
    point ponto;
    node * next;
    node * prev;
    node(point x) {
        ponto.x = x.x;
        ponto.y = x.y;
        next = NULL;
        prev = NULL;
    }
};
class Fila {
    private:
        node* head;
        node* tail;
    public:
        Fila() {
            point ponto;
            ponto.x = 0;
            ponto.y = 0;
            head = new node(ponto);
            head->next = NULL;
            head->prev = NULL;
            tail = head;
        }
        ~Fila() {
            while(isEmpty() == false);
                removeFirst();
            delete head;
        }
        bool isEmpty() {
            return head == tail;
        }
        point first() {
            return tail->prev->ponto;
        }
        void removeFirst() {
            tail = tail->prev;
            delete tail->next;
            tail->next = NULL;
        }
        void insertPoint(point x) {
            node* aux = new node(x);
            aux->next = head->next;
            aux->prev = head;
            head->next = aux;
            aux->next->prev = aux;
        }
};

void plotFigure(short shadeLayer[resolucao][resolucao], bool** drawMatrix, int** drawingMatrix,int i, int j, int l, Fila *toGo[]) {
    point ponto;
    ponto.x = j;
    ponto.y = i;
    drawingMatrix[i][j] = 1 + min(min(min(min(min(min(min(drawingMatrix[i + 1][j], drawingMatrix[i + 1][j + 1]), drawingMatrix[i][j + 1]), drawingMatrix[i - 1][j + 1]), drawingMatrix[i - 1][j]), drawingMatrix[i - 1][j - 1]), drawingMatrix[i][j + 1]), drawingMatrix[i][j - 1]);
    toGo[drawingMatrix[i][j]]->insertPoint(ponto);
    drawMatrix[i][j] = true;
    if(drawMatrix[i + 1][j + 1]  == false && shadeLayer[i + 1][j + 1] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i + 1, j + 1, l, toGo);
    if(drawMatrix[i + 1][j]  == false && shadeLayer[i + 1][j] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i + 1, j, l, toGo);
    if(drawMatrix[i + 1][j - 1]  == false && shadeLayer[i + 1][j - 1] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i + 1, j - 1, l, toGo);
    if(drawMatrix[i][j + 1]  == false && shadeLayer[i][j + 1] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i, j + 1, l, toGo);
    if(drawMatrix[i - 1][j + 1]  == false && shadeLayer[i - 1][j + 1] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i - 1, j + 1, l, toGo);
    if(drawMatrix[i - 1][j]  == false && shadeLayer[i - 1][j] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i - 1, j, l, toGo);
    if(drawMatrix[i - 1][j - 1]  == false && shadeLayer[i - 1][j - 1] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i - 1, j - 1, l, toGo);
    if(drawMatrix[i][j - 1]  == false && shadeLayer[i][j - 1] >= l)
        plotFigure(shadeLayer, drawMatrix, drawingMatrix, i, j - 1, l, toGo);
}

/*///Funcoes e propriedades da impressora
bool isLowered;

void raiseHook() {

}

void lowerHook() {

}
void moveTo(int x, int y) {

}
///Funcoes e propriedades da impressora
*/

const double multiplicadores[16][16] = {//multiplicador de pixel para diminuir a resolucao
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.5, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.17, 0.66, 0.17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.125, 0.375, 0.375, 0.125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.08, 0.14, 0.56, 0.14, 0.08, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.09, 0.17, 0.24, 0.24, 0.17, 0.09, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.03, 0.09, 0.16, 0.44, 0.16, 0.09, 0.03, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.04, 0.08, 0.12, 0.26, 0.26, 0.12, 0.08, 0.04, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.01, 0.06, 0.11, 0.15, 0.30, 0.15, 0.11, 0.06, 0.01, 0, 0, 0, 0, 0, 0, 0},
    {0.02, 0.05, 0.09, 0.14, 0.20, 0.20, 0.14, 0.09, 0.05, 0.02, 0, 0, 0, 0, 0, 0},
    {0.008, 0.032, 0.06, 0.10, 0.14, 0.36, 0.24, 0.10, 0.06, 0.032, 0.008, 0, 0, 0, 0, 0},
    {0.01, 0.035, 0.075, 0.09, 0.12, 0.17, 0.17, 0.12, 0.09, 0.075, 0.035, 0.01, 0, 0, 0, 0},
    {0.17, 0.66, 0.17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.17, 0.66, 0.17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.17, 0.66, 0.17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0.17, 0.66, 0.17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
const int layers[LAYERNUMBER] = {//first interval is empty (white)
    255, 223, 191, 159, 127, 95, 63, 31, 0
};
short luma(int aux[]) {
    double grey = aux[0]*0.299 + aux[1]*0.587 + aux[2]*0.114;
    short greyInt = grey;
    return greyInt;
}
int howManyGround(int axis) {
    return resolucao - axis % resolucao;
}
short translate(short pixel) {
    short shade = 0;
    for(int i = 1; i < LAYERNUMBER; i++) {
        if(pixel < layers[i]) shade++;
    }
    return shade;
}

int main(int argc, char* argv[])
{
    string fileName = "plsWork.py";
    string command = "python ";
    string imageName = argv[1];
    string txtName;
    string reader;
    ifstream dottxt;
    int layers = 5;
    int xAxis, yAxis;
    //read image name, file name and layers

    //finish read image
    //string management
    txtName = imageName.substr(0, imageName.find(".") + 1) + "txt";//changing extension to .txt
    command += fileName;
    command += " ";
    command += imageName;

    system(command.c_str());

    dottxt.open(txtName.c_str());
    dottxt >> xAxis;
    dottxt >> yAxis;//read image dimension

    short imageGrid[yAxis][xAxis];
    int aux[3];
    char c;
    getline(dottxt, reader);//eliminate \n
    dottxt.get(c);//eliminate first [
    //setting greyscale
    for(int i = 0; i < yAxis; i++) {
        for(int j = 0; j < xAxis * 3; j++) {
            do{
                dottxt.get(c);
                if(c == ']') {
                    dottxt.get(c);
                    dottxt.get(c);
                    dottxt.get(c);

                }
            }while(c != '[' && c != ' ');
            dottxt >> aux[j % 3];
            if((j + 1) % 3 == 0){
                imageGrid[i][j/3] = luma(aux);
            }
        }
    }
    //lowering resolution
    //remember that the y is the first index!
    short lowResImg[resolucao][resolucao];
    int xGround = howManyGround(xAxis);
    int yGround = howManyGround(yAxis);
    int xRatio = xAxis / resolucao;
    int yRatio = yAxis / resolucao;
    short average;
    short sum = 0;
    int xTransform;
    int yTransform;
    int x;
    int y;
    for(int i = 0; i < resolucao; i++) {
        for(int j = 0; j < resolucao; j++) {
            if(j < xGround && i < yGround) {
                y = i * yRatio;
                x = j * xRatio;
                yTransform = yRatio;
                xTransform = xRatio;
                double sum = 0;
                for(int k = 0; k < yTransform; k++) {
                    for(int l = 0; l < xTransform; l++) {
                        sum += multiplicadores[xTransform][l] * multiplicadores[yTransform][k] * imageGrid[y + k][x + l];
                    }
                }
                lowResImg[i][j] = sum;
            }
            else if(j < xGround && i >= yGround) {
                y = yGround * yRatio + (i - yGround) * (yRatio + 1);
                x = j * xRatio;
                yTransform = yRatio + 1;
                xTransform = xRatio;
                double sum = 0;
                for(int k = 0; k < yTransform; k++) {
                    for(int l = 0; l < xTransform; l++) {
                        sum += multiplicadores[xTransform][l] * multiplicadores[yTransform][k] * imageGrid[y + k][x + l];
                    }
                }
                lowResImg[i][j] = sum;
            }
            else if(j >= xGround && i < yGround) {
                y = i * yRatio;
                x = xGround * xRatio + (j - xGround) * (xRatio + 1);
                yTransform = yRatio;
                xTransform = xRatio + 1;
                double sum = 0;
                for(int k = 0; k < yTransform; k++) {
                    for(int l = 0; l < xTransform; l++) {
                        sum += multiplicadores[xTransform][l] * multiplicadores[yTransform][k] * imageGrid[y + k][x + l];
                    }
                }
                lowResImg[i][j] = sum;
            }
            else {
                y = yGround * yRatio + (i - yGround) * (yRatio + 1);
                x = xGround * xRatio + (j - xGround) * (xRatio + 1);
                yTransform = yRatio + 1;
                xTransform = xRatio + 1;
                double sum = 0;
                for(int k = 0; k < yTransform; k++) {
                    for(int l = 0; l < xTransform; l++) {
                        sum += multiplicadores[xTransform][l] * multiplicadores[yTransform][k] * imageGrid[y + k][x + l];
                    }
                }
                lowResImg[i][j] = sum;
            }
        }
    }
    if(true) {
        //print greyscaled image
        ofstream greyscaled;
        greyscaled.open("hu3.txt");
        for(int i = 0; i < yAxis; i++) {
            for(int j = 0; j < xAxis; j++) {
                greyscaled << imageGrid[i][j] << " ";
            }
            greyscaled << endl;
        }
        string hu3 = "python lel.py hu3.txt ";
        string w, h;
        stringstream outW;
        stringstream outH;
        outW << xAxis;
        outH << yAxis;
        w = outW.str();
        h = outH.str();
        hu3 += w;
        hu3 += " ";
        hu3 += h;
        system(hu3.c_str());
    }
    /*
    //print low res image
    ofstream greyscaled;
    greyscaled.open("wwe.txt");
    for(int i = 0; i < resolucao; i++) {
        for(int j = 0; j < resolucao; j++) {
            greyscaled << lowResImg[i][j] << " ";
        }
        greyscaled << endl;
    }

    string hu3 = "python lel.py wwe.txt ";
    string w, h;
    stringstream outW;
    stringstream outH;
    outW << resolucao;
    outH << resolucao;
    w = outW.str();
    h = outH.str();
    hu3 += w;
    hu3 += " ";
    hu3 += h;
    system(hu3.c_str());

    //making the layers!!!
    short shadeLayer[resolucao][resolucao];
    for(int i = 0; i < resolucao; i++) {
        for(int j = 0; j < resolucao; j++) {
            shadeLayer[i][j] = translate(lowResImg[i][j]);
        }
    }
    */

    //pathMaking
    //i == y component j == x component
    ///Impressora!!!!!
    /*
    for(int l = 1; l < LAYERNUMBER; l++) {
        for(int i = 0; i < resolucao; i++) {
            if(isLowered) raiseHook();
            moveTo(0, i);
            for(int j = 0; j < resolucao; j++) {
                if(shadeLayer[i][j] >= l) {
                    if(!isLowered) lowerHook();

                }
                else {
                    if(isLowered) raiseHook();
                }
                moveTo(j + 1, i);
            }
        }
    }*/

    //i == y, j == x
    bool **drawMatrix = new bool*[resolucao];
    int **drawingMatrix = new int*[resolucao];
    Fila * toGo[resolucao];
    ///Plotter!!!!!!
    for(int l = 1; l < LAYERNUMBER; l++) {
        for(int i =0; i < resolucao; i++) {
            drawingMatrix[i] = new int[resolucao];
            drawMatrix[i] = new bool[resolucao];
            for(int j = 0; j < resolucao; j++) {
                drawingMatrix[i][j] = 0;
                drawMatrix[i][j] = false;
            }
            toGo[i] = new Fila();
        }
        for(int i = 0; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                if(shadeLayer[i][j] >= l && drawMatrix[i][j] == false) {//found something to draw
                    plotFigure(shadeLayer, drawMatrix, drawingMatrix, i, j, l, toGo);
                    //printFigure(toGo);//sua funcao aloysio
                }
            }
        }
    }


    return 0;
}
