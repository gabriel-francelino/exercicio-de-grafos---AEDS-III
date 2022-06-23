#include <fstream>
#include <iostream>
#include <math.h>
#include <list>

using namespace std;

int *x, *y, nLinhas = 0;

//======================================== LISTA ADJ ===============================================
typedef struct adjacencia {
    int vertice; //vertice de destino
    TIPOPESO peso; //peso associado a aresta que leva ao vertice de destino
    struct adjacencia *prox; //prox elemento da lista de adjacencia
} ADJACENCIA;

/**
 * @brief Dados armazenados vão aqui
 * 
 */
typedef struct vertice {
    ADJACENCIA *cab; //possui apenas a cabeça de adjacencia
    int ind;    //indicativo para a busca (branco=-1, cinza=0, preto=1)
    int d;      //distancia do vertice

    
} VERTICE;

typedef struct grafo {
    int vertices; //num de vertices total
    int arestas; //num de arestas totais
    VERTICE *adj; //arranjo de vertices da estrutura
} GRAFO;

GRAFO *criaGrafo(int v) {
    list<GRAFO> g;
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE*) malloc(v * sizeof (VERTICE));

    for (int i = 0; i < v; i++) {
        g->adj[i].cab = NULL;
    }
    return g;
}

// ADJACENCIA *criaAdj(int v, int peso) {
//     ADJACENCIA *temp = (ADJACENCIA*) malloc(sizeof (ADJACENCIA));
//     temp->vertice = v;
//     temp->peso = peso;
//     temp->prox = NULL;
//     return temp;
// }

//======================================== MATRIZ ADJ ===============================================

void grafoNumLinhas(const char *name) {
    ifstream myfile(name);
    if (myfile.is_open()) {
        while (!myfile.eof()) {
            //ler o tipo
            int a, b, c, n;

            myfile >> a;
            myfile >> b;
            myfile >> c;
            nLinhas++;
        }
        myfile.close();
        x = new int[nLinhas];
        y = new int[nLinhas];
    }
}

int coordenadas(const char *name) {
    ifstream myfile(name);
    if (myfile.is_open()) {
        int i=0;
        while (!myfile.eof()) {

            int a;

            myfile >> a;
            myfile >> x[i];
            myfile >> y[i];
            i++;
        }
        myfile.close();
    } else {
        cout << "NÃ£o foi possÃ­vel ler o arquivo." << endl;
    }

    return 0;
}

int pesoAresta(int *x, int *y, int i, int j) {
    int p, a, b;
    a = x[j] - x[i];
    b = y[j] - y[i];
    p = sqrt(pow(a, 2) + pow(b, 2));
    return p;
}

int **matrizAdj() {
    int **mat;
    mat = new int*[nLinhas];
    for (int i = 0; i < nLinhas; i++) {
        mat[i] = new int[nLinhas];
    }

    for (int lin = 0; lin < nLinhas; lin++) {
        for (int col = 0; col < nLinhas; col++) {
            if (lin == col) {
                mat[lin][col] = 0;
            } else {
                mat[lin][col] = pesoAresta(x, y, lin, col);
            }
        }
    }
    return mat;
}

void deleteMatriz(int **m) {
    for (int i = 0; i < nLinhas; i++) {
        delete(m[i]);
    }
    delete(m);
}

void imprimeMatrizAdj(int **m) {
    cout << "-------------------------MATRIZ DE ADJACENCIA----------------------" << endl;
    for (int i = 0; i < nLinhas; i++) {
        for (int j = 0; j < nLinhas; j++) {
            cout << "|\t" << m[i][j] << "\t|";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------------------" << endl;
}

//===================================================================================================

int main(int argc, char const *argv[])
{
    
    return 0;
}
