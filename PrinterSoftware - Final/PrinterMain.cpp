#include "Communication.h"
#include "PathGenerator.h"

using namespace std;

int main(int argc, char* argv[]){
    ///Connection to printer
    //Declaring printer object
    Printer print;

    //Code for attaching printer to serial port
    int attach;

    for (int i = 0; i <= 50; ++i){
        std::cout<<"Attaching to COM" << i <<"\n";
        attach = print.attach(i);


        if (attach == 0){
            std::cout<<"Attach to COM" << i <<" succeded\n";
            std::cout<<"Connecting to COM" << i <<"\n";

            //Code for connecting to printer in a serial port
            if (print.connect()){
                std::cout<<"Connected to COM" << i <<"\n";
                break;
            }
        }
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
    //if the image is not greyscale
    if(strcmp(argv[2], "1") != 0) {
        for(int i = 0; i < yAxis; i++) {
            for(int j = 0; j < xAxis * 3; j++) {
                //equivalent to regex like code
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
    //if the image is already greyscale
    else {
        for(int i =0 ; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                //equivalent to regex like code
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
    //if the image is not resxres
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
    //if the image is resxres
    else {
        for(int i = 0; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                lowResImg[i][j] = imageGrid[i][j];
            }
        }
    }
    //making the layers!!!
    cout << "aqui";
    short shadeLayer[resolucao][resolucao];
    for(int i = 0; i < resolucao; i++) {
        for(int j = 0; j < resolucao; j++) {
            shadeLayer[i][j] = translate(lowResImg[i][j]);
        }
    }
    //pathMaking
    //i == y, j == x
    bool **drawMatrix = new bool*[resolucao];
    for(int i = 0; i < resolucao; i++) {
        drawMatrix[i] = new bool[resolucao];
    }
    Arvore* toGo = new Arvore();
    ///Plotter!!!!!!
    for(int l = 1; l < LAYERNUMBER; l++) {
        for(int i =0; i < resolucao; i++) {
            for(int j = 0; j < resolucao; j++) {
                //reset draw matrix for new layer
                drawMatrix[i][j] = false;
            }
        }
        for(int i = 1; i < resolucao - 1; i++) {
            for(int j = 1; j < resolucao - 1; j++) {
                if(shadeLayer[i][j] >= l && drawMatrix[i][j] == false) {//found something to draw
                    //plot the component
                    plotFigure(shadeLayer, drawMatrix, i, j, l, toGo->raiz);
                    //set the hook to the starting point
                    node* no = toGo->raiz->filhoEsquerdo;
                    node* ultimo = toGo->getUltimo();
                    //if(print.isLowered() == true)
                        //print.raise();
                    //print.go(no->ponto.x, no->ponto.y);
                    //print.lower();
                    //draw the component
                    while(no != ultimo) {
                        //print.go(no->ponto.x, no->ponto.y);
                        if(no->filhoEsquerdo == NULL) {
                            while(no->irmaoDireito == NULL) {
                                no = no->pai;
                                //print.go(no->ponto.x, no->ponto.y);
                            }
                            no = no->irmaoDireito;
                        }
                        else {
                            no = no->filhoEsquerdo;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
