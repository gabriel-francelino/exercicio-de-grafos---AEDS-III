#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <math.h>

#define true 1
#define false 0

using namespace std;

int nLinhas = 0, i = 0, j = 0;
int *x; 
int *y;


//--------------------------------------------------LISTA DE ADJACENCIA--------------------------------------------------------
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice; //vertice de destino
    TIPOPESO peso; //peso associado a aresta que leva ao vertice de destino
    struct adjacencia *prox; //prox elemento da lista de adjacencia
    int ind;    //indicativo para a busca (branco=-1, cinza=0, preto=1)
} ADJACENCIA;

/**
 * @brief Dados armazenados vão aqui
 * 
 */
typedef struct vertice {
    ADJACENCIA *cab; //possui apenas a cabeça de adjacencia
} VERTICE;

typedef struct grafo {
    int vertices; //num de vertices total
    int arestas; //num de arestas totais
    VERTICE *adj; //arranjo de vertices da estrutura
} GRAFO;

/**
 * @brief função para criar um GRAFO
 * 
 * @param v num de vértices
 * @return GRAFO* 
 */
GRAFO *criaGrafo(int v) {
    GRAFO *g = (GRAFO*) malloc(sizeof (GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE*) malloc(v * sizeof (VERTICE));

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
    ADJACENCIA *temp = (ADJACENCIA*) malloc(sizeof (ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    temp->ind = 0;
    return temp;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) { //vai de vi a vf
    if (!gr) return (false); //validações se o grafo existe 

    ADJACENCIA *novo = criaAdj(vf, p); //crio adjacencia com o vértice final e o peso
    //coloco a adjacencia na lista do vértice inicial
    novo->prox = gr->adj[vi].cab; //o campo prox da adjacencia vai receber a cabeça da lista
    gr->adj[vi].cab = novo; // e a cabeça da lista passa a ser o novo elemento
    gr->arestas++; // atualizo o numero de aresta no grafo
    return (true);
}

void imprimeLista(GRAFO *gr) {
    cout << "---------------LISTA DE ADJACENCIA-------------" << endl;
    cout << "Vertices: " << gr->vertices << "\tArestas: " << gr->arestas << endl;
    for (i = 0; i < gr->vertices; i++) {
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

void freeLista(GRAFO *g) {
    for(int i = 0; i < g->vertices; i++) {
        free(g->adj[i].cab);
    }
    free(g->adj);
    free(g);
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
        x = (int *) malloc((nLinhas) * sizeof (int));
        y = (int *) malloc((nLinhas) * sizeof (int));
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

void imprime() {
    for (int i = 0; i < nLinhas; i++) {
        cout << "x: " << x[i] << "\ty: " << y[i] << endl;
    }
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
    mat = (int **) malloc(nLinhas * sizeof (int*));
    for (i = 0; i < nLinhas; i++) {
        mat[i] = (int *) malloc(nLinhas * sizeof (int));
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
        free(m[i]);
    }
    free(m);
}
//------------------------------------------------BUSCA EM LARGURA---------------------------------------------------------------
/*
https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/bfs.html
https://www.pucsp.br/~jarakaki/grafos/Aula6.pdf

void GRAPHbfs( Graph G, vertex s) 
{ 
   int cnt = 0;
   for (vertex v = 0; v < G->V; ++v)
      num[v] = -1;
   QUEUEinit( G->V);
   num[s] = cnt++; 
   QUEUEput( s); 

   while (!QUEUEempty( )) {
      vertex v = QUEUEget( ); 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (num[a->w] == -1) {
            num[a->w] = cnt++; 
            QUEUEput( a->w); 
         }
   }
   QUEUEfree( ); 
}
*/

void buscaBFS(GRAFO g, int raiz){
    int cont = 0;
    ADJACENCIA *u = g.adj->cab;
    for ( i = 0; i < g.vertices; i++)
    {
        while (u->vertice != raiz)
        {
            u = u->prox;     
        }    
        u->ind = -1;
    }
    //QUEUEinit(g.vertices);
    
}

//-------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char**argv) {
    leGrafo("teste.txt");
    coordenadas("teste.txt");

    int **m = matrizAloc();
    GRAFO *gr = criaGrafo(nLinhas);

    for (i = 0; i < nLinhas; i++) {
        for (j = 0; j < nLinhas; j++) {
            if (i != j) {
                criaAresta(gr, i, j, m[i][j]);
            }
        }
    }

    imprimeLista(gr);
    imprimeMatriz(m);
    freeLista(gr);
    freeMatriz(m);

    return 0;
}
