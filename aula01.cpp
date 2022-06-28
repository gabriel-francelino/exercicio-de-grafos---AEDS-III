#include <fstream>
#include <iostream>
#include <math.h>


#define infinito 10000000

using namespace std;

int nLinhas = 0, i = 0, j = 0;
int *x; 
int *y;


//--------------------------------------------------LISTA DE ADJACENCIA--------------------------------------------------------
typedef int TIPOPESO;

/**
 * @brief estrutura para a lista de adjacencia.
 * 
 */
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
    int nVertices; //num de vertices total
    int nArestas; //num de arestas totais
    VERTICE *adj; //arranjo de vertices da estrutura
} GRAFO;

//teste-----------------------------------------
typedef struct aresta
{
    int v1, v2;     //vertices da aresta
    int peso;       //peso da aresta
}ARESTA;

/**
 * @brief função para criar um GRAFO
 * 
 * @param v num de vértices
 * @return GRAFO* 
 */
GRAFO *criaGrafo(int v) {
    GRAFO *g = new GRAFO;
    g->nVertices = v;
    g->nArestas = 0;
    g->adj = new VERTICE[v];

    for (i = 0; i < v; i++) {
        g->adj[i].cab = NULL;
    }
    return g;
}

/**
 * @brief função para adicionar arestas no GRAFO
 * 
 * @param v vértice alvo da adjacencia
 * @param peso peso da aresta
 * @return ADJACENCIA* 
 */
ADJACENCIA *criaAdj(int v, int peso) {
    ADJACENCIA *adj = new ADJACENCIA;
    adj->vertice = v;
    adj->peso = peso;
    adj->prox = NULL;
    return adj;
}

void criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) { //vai de vi a vf
    //if (!gr) return (false); //validações se o grafo existe 

    //crio adjacencia com o vértice final e o peso
    ADJACENCIA *novo = criaAdj(vf, p); 

    //coloco a adjacencia na lista do vértice inicial
    //o campo prox da adjacencia vai receber a cabeça da lista
    novo->prox = gr->adj[vi].cab; 
    // e a cabeça da lista passa a ser o novo elemento
    gr->adj[vi].cab = novo; 
    // atualizo o numero de aresta no grafo
    gr->nArestas++; 
    
    //return (true);
}

void imprimeLista(GRAFO *gr) {
    cout << "---------------LISTA DE ADJACENCIA-------------" << endl;
    cout << "Vertices: " << gr->nVertices << "\tArestas: " << gr->nArestas << endl;
    for (i = 0; i < gr->nVertices; i++) {
        cout << "v" << i << ": ";
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad) {
            cout << " -->  v" << ad->vertice << "(" << ad->peso << ")";
            ad = ad->prox;
        }
        cout << endl;
    }
    cout << "----------------------------------------------" << endl;
}

void deleteLista(GRAFO *g) {
    for(int i = 0; i < g->nVertices; i++) {
        delete(g->adj[i].cab);
    }
    delete(g->adj);
    delete(g);
}

void criaListAdj(GRAFO *gr, int** m){
    for (i = 0; i < nLinhas; i++) {
        for (j = 0; j < nLinhas; j++) {
            if (i != j) {
                criaAresta(gr, i, j, m[i][j]);
            }
        }
    }
}
//--------------------------------------------------MATRIZ DE ADJACENCIA-------------------------------------------------------

void leGrafo(const char *name) {
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
        i=0;
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

int peso(int *x, int *y, int i, int j) {
    int p, a, b;
    a = x[j] - x[i];
    b = y[j] - y[i];
    p = sqrt(pow(a, 2) + pow(b, 2));
    return p;
}

void imprimeMatriz(int **m) {
    cout << "-------------------------MATRIZ DE ADJACENCIA----------------------" << endl;
    for (i = 0; i < nLinhas; i++) {
        for (j = 0; j < nLinhas; j++) {
            cout << "|\t" << m[i][j] << "\t|";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------------------" << endl;
}

int **matrizAloc() {
    int **mat;
    mat = new int*[nLinhas];
    for (i = 0; i < nLinhas; i++) {
        mat[i] = new int[nLinhas];
    }

    for (int lin = 0; lin < nLinhas; lin++) {
        for (int col = 0; col < nLinhas; col++) {
            if (lin == col) {
                mat[lin][col] = 0;
            } else {
                mat[lin][col] = peso(x, y, lin, col);
            }
        }

    }
    return mat;
}

void freeMatriz(int **m) {
    for (i = 0; i < nLinhas; i++) {
        delete(m[i]);
    }
    delete(m);
}

//--------------------------------------------------DIJKSTRA-------------------------------------------------------
// GRAFO* inicializaDijkstra(GRAFO* g, VERTICE* v){
//     //int *d = new int[nLinhas];
//     for(int i=0; i< nLinhas; i++){
//         g->vertices
//     }
    
// }


//-------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char**argv) {
    leGrafo("teste.txt");
    coordenadas("teste.txt");

    int **m = matrizAloc();
    GRAFO *gr = criaGrafo(nLinhas);

    criaListAdj(gr, m);
    imprimeLista(gr);
    imprimeMatriz(m);
    deleteLista(gr);
    freeMatriz(m);

    return 0;
}
