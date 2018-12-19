#include "PathGenerator.h"


node::node(point x, node* father) {
    ponto.x = x.x;
    ponto.y = x.y;
    pai = father;
    filhoEsquerdo = NULL;
    irmaoDireito = NULL;
}
node::~node() {
    node* aux = this;
    if(aux->irmaoDireito)
        delete aux->irmaoDireito;
    if(aux->filhoEsquerdo)
        delete aux->filhoEsquerdo;
    delete aux;
}
void node::insertNode(point x) {
    if(filhoEsquerdo == NULL) {
        filhoEsquerdo = new node(x, this);
        return;
    }
    node* aux = filhoEsquerdo;
    while(aux->irmaoDireito != NULL) {
        aux = aux->irmaoDireito;
    }
    aux->irmaoDireito = new node(x, this);
}
Arvore::Arvore() {
    point ponto;
    ponto.x = ponto.y = 0;
    raiz = new node(ponto, NULL);
}
Arvore::~Arvore() {
    delete raiz;
}
node* Arvore::getUltimo() {
    node* aux = raiz->filhoEsquerdo;
    while(aux->filhoEsquerdo != NULL || aux->irmaoDireito != NULL) {
        while(aux->irmaoDireito != NULL) {
            aux = aux->irmaoDireito;
        }
        if(aux->filhoEsquerdo) {
            aux = aux->filhoEsquerdo;
        }
    }
    return aux;
}
void plotFigure(short shadeLayer[resolucao][resolucao], bool** drawMatrix, int i, int j, int l, node* toGo) {
    if(i < 1 || i >= resolucao - 1 || j < 1 || j >= resolucao - 1) return;
    point ponto;
    ponto.x = i;
    ponto.y = j;
    toGo->insertNode(ponto);
    drawMatrix[i][j] = true;
    if(drawMatrix[i + 1][j] == false && shadeLayer[i + 1][j] >= l) {
        plotFigure(shadeLayer, drawMatrix, i + 1, j, l, toGo);
    }
    if(drawMatrix[i + 1][j + 1] == false && shadeLayer[i + 1][j + 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i + 1, j + 1, l, toGo);
    }
    if(drawMatrix[i + 1][j - 1] == false && shadeLayer[i + 1][j - 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i + 1, j - 1, l, toGo);
    }
    if(drawMatrix[i][j + 1] == false && shadeLayer[i][j + 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i, j + 1, l, toGo);
    }
    if(drawMatrix[i - 1][j + 1] == false && shadeLayer[i - 1][j + 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i - 1, j + 1, l, toGo);
    }
    if(drawMatrix[i][j - 1] == false && shadeLayer[i][j - 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i, j - 1, l, toGo);
    }
    if(drawMatrix[i - 1][j] == false && shadeLayer[i - 1][j] >= l) {
        plotFigure(shadeLayer, drawMatrix, i - 1, j, l, toGo);
    }
    if(drawMatrix[i - 1][j - 1] == false && shadeLayer[i - 1][j - 1] >= l) {
        plotFigure(shadeLayer, drawMatrix, i - 1, j - 1, l, toGo);
    }
}
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
