#include "Communication.h"
#include "PathGenerator.h"

using namespace std;

const int LAYERNUMBER = 3;

const int resolucao = 100;

struct point {
    int x;
    int y;
};
struct node {
    point ponto;
    point father;
    node * next;
    node * prev;
    node(point x, point y) {
        ponto.x = x.x;
        ponto.y = x.y;
        father.x = y.x;
        father.y = y.y;
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
            head = new node(ponto, ponto);
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
        node* first() {
            return tail->prev;
        }
        void removeFirst() {
            tail = tail->prev;
            delete tail->next;
            tail->next = NULL;
        }
        void insertPoint(point x, point y) {
            node* aux = new node(x, y);
            aux->next = head->next;
            aux->prev = head;
            head->next = aux;
            if(aux->next != NULL)
                aux->next->prev = aux;
            else tail = aux;
        }
};

void plotFigure(short shadeLayer[resolucao][resolucao], bool** drawMatrix, int i, int j, int l, Fila* toGo, int paiX, int paiY) {
    if(i < 1 || i >= resolucao - 1 || j < 1 || j >= resolucao - 1) return;
    point ponto1, ponto2;
    ponto1.x = i;
    ponto1.y = j;
    ponto2.x = paiX;
    ponto2.y = paiY;
    toGo->insertPoint(ponto1, ponto2);
    drawMatrix[i][j] = true;
    if(drawMatrix[i + 1][j] == false && shadeLayer[i + 1][j] >= l) {
        plotFigure(shadeLayer, drawMatrix, i + 1, j, l, toGo, i, j);
    }
    if(drawMatrix[i + 1][j + 1] == false && shadeLayer[i + 1][j + 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i + 1, j + 1, l, toGo, i, j);
    }
    if(drawMatrix[i + 1][j - 1] == false && shadeLayer[i + 1][j - 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i + 1, j - 1, l, toGo, i, j);
    }
    if(drawMatrix[i][j + 1] == false && shadeLayer[i][j + 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i, j + 1, l, toGo, i, j);
    }
    if(drawMatrix[i - 1][j + 1] == false && shadeLayer[i - 1][j + 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i - 1, j + 1, l, toGo, i, j);
    }
    if(drawMatrix[i][j - 1] == false && shadeLayer[i][j - 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i, j - 1, l, toGo, i, j);
    }
    if(drawMatrix[i - 1][j] == false && shadeLayer[i - 1][j] >= l) {
        plotFigure(shadeLayer, drawMatrix, i - 1, j, l, toGo, i, j);
    }
    if(drawMatrix[i - 1][j - 1] == false && shadeLayer[i - 1][j - 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i - 1, j - 1, l, toGo, i, j);
    }
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
    255, 122, 0
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
short translate2(short pixel) {
    return layers[pixel];
}

int main(int argc, char* argv[]){
    ///Connection to printer

    Printer print;
    bool attach = false;
    for (int i = 0; i <= 50; ++i){
        std::cout<<"Attaching to COM" << i <<"\n";
        attach = print.attach(i);
        if (!attach){
            std::cout<<"Attach to COM" << i <<" succeded\n";
            std::cout<<"Connecting to COM" << i <<"\n";
            if (print.connect()){
                std::cout<<"Connected to COM" << i <<"\n";
                break;
            }
        }

        attach = false;
    }
/*
    print.go(100,0);
    print.go(50,50);
    print.go(100,100);
    print.go(0,100);
    print.raise();
    print.go(0,110);
    print.lower();
    print.go(100, 210);
    print.go(0, 310);
    print.raise();
    print.go(50,160);
    print.lower();
    print.go(50, 260);
*/

    ///Connection to printer

     if(argc < 4) {
        cout << "Insira 3 argumentos: imagem.png; 0 (se a imagem for RGB) 1 (se a imagem for greyscale); 0 (se a imagem for diferente de 100x100) 1 (se a imagem for igual a 100x100)";
        return 0;
    }

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
    if(strcmp(argv[2], "1") != 0) {
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
    }
    else {
        for(int i =0 ; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                do{
                    dottxt.get(c);
                    if(c == ']') {
                        dottxt.get(c);
                        dottxt.get(c);
                        dottxt.get(c);
                    }
                }while(c != '[' && c != ' ');
                dottxt >> imageGrid[i][j];
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
    if(strcmp(argv[3], "1") != 0) {
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
    }
    else {
        for(int i = 0; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                lowResImg[i][j] = imageGrid[i][j];
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
    //print low res image
    if(true) {
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
    }


    //making the layers!!!
    short shadeLayer[resolucao][resolucao];
    for(int i = 0; i < resolucao; i++) {
        for(int j = 0; j < resolucao; j++) {
            shadeLayer[i][j] = translate(lowResImg[i][j]);
        }
    }
    if(true) {
        ofstream greyscaled;
        greyscaled.open("wot.txt");
        for(int i = 0; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                greyscaled << shadeLayer[i][j] << " ";
            }
            greyscaled << endl;
        }

        string hu3 = "python lel.py wot.txt ";
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
    }
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
    for(int i = 0; i < resolucao; i++) {
        drawMatrix[i] = new bool[resolucao];
    }
    Fila * toGo = new Fila();
    ///Plotter!!!!!!
    for(int l = 1; l < LAYERNUMBER; l++) {
        for(int i =0; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                drawMatrix[i][j] = false;
            }
        }
        for(int i = 1; i < resolucao - 1; i++) {
            for(int j = 1; j < resolucao - 1; j++) {
                if(shadeLayer[i][j] >= l && drawMatrix[i][j] == false) {//found something to draw
                    plotFigure(shadeLayer, drawMatrix, i, j, l, toGo, i, j);
                    while(toGo->isEmpty() == false) {
                        cout << "ged rekt" << l << endl;
                        node* no = toGo->first();
                        if(no->father.x != print.getX() || no->father.y != print.getY()) {
                            if(print.isLowered() == true)
                                print.raise();
                            print.go(toGo->first()->father.x, toGo->first()->father.y);
                            print.lower();
                        }
                        if(print.isLowered() == false)
                            print.lower();
                        print.go(no->ponto.x, no->ponto.y);
                        toGo->removeFirst();
                    }
                }
            }
        }
    }


    return 0;
}
