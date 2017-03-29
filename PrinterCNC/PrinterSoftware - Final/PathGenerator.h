#ifndef PATH
#define PATH

#include <fstream>
#include <math.h>
#include <stack>
#include <Windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>

/**Number of used layers during printing
*/
const int LAYERNUMBER = 3;
/**Used layers
*first interval is empty (white)
*If you're changing the LAYERNUMBER don't forget to change the layers
*/
const int layers[LAYERNUMBER] = {
    255, 122, 0
};

/**Printing resolution
*/
const int resolucao = 200;

/**Point that contains an x and y coordinates
*/
struct point {
    int x;
    int y;
};
/**node class used on the tree
*/
class node {
    public:
    point ponto;
    node * pai;
    node * filhoEsquerdo;
    node * irmaoDireito;
    /**Constructor, needs its point (x) and father
    */
    node(point x, node* father);
    /**node destructor
    */
    ~node();
    /**insert a new node as the son of the node
    */
    void insertNode(point x);
};
/**Tree class
*/
class Arvore {
    public:
    node* raiz;
    /**Constructor, makes a standard point root = (0, 0)
    */
    Arvore();
    /**Destructor
    */
    ~Arvore();
    /**Returns the node that is more to the right
    */
    node* getUltimo();
};


/**Returns the path to the figure component as tree, which the node toGo is the root
*/
void plotFigure(short shadeLayer[resolucao][resolucao], bool** drawMatrix, int i, int j, int l, node* toGo);

/**this are the numbers which indicate the weighted average of each node, depending on its position with the center
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
    {0.01, 0.035, 0.075, 0.09, 0.12, 0.17, 0.17, 0.12, 0.09, 0.075, 0.035, 0.01, 0, 0, 0, 0}
};
/**Translates RGB to the luma greyscale
*/
short luma(int aux[]);

/**Caclulates the rest of the division axis/resolucao
*/
int howManyGround(int axis);

/**Translates a greyscale pixel to the layer system
*/
short translate(short pixel);

/**Translates a layer system pixel to greyscale
*Don't use this to return from translate, it may return different values
*this is only used to see the result of the layer system (debugging)
*/
short translate2(short pixel);

#endif


