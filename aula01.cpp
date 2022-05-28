# include <stdio.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

int nLinhas = 0, i=0, j=0;

int leGrafo(const char *name){
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
    } else{
        cout << "NÃ£o foi possÃ­vel ler o arquivo." << endl;
    }
        
    return 0;
}

int *x = (int *) malloc(nLinhas * sizeof(int));
int *y = (int *) malloc(nLinhas * sizeof(int));

int coordenadas(const char *name){
    ifstream myfile(name);
    if (myfile.is_open()) {
        while (!myfile.eof()) {

            int a;
            
            myfile >> a;
            myfile >> x[i];
            myfile >> y[i];
            i++;  
        }
        myfile.close();
    } else{
        cout << "NÃ£o foi possÃ­vel ler o arquivo." << endl;
    }
        
    return 0;
}

int peso(int *x, int *y, int i, int j){
    int p,a,b;
    a=x[j]-x[i];
    b=y[j]-y[i];
    p = sqrt(pow(a,2) + pow(b,2));
    return p;
}

void imprime(){
    for (int i = 0; i < nLinhas; i++)
    {
        cout << "x: " << x[i] << "\ty: " << y[i] << endl;
    }
}

void imprimeMatriz(int **m){
    for ( i = 0; i < nLinhas; i++)
    {
        for ( j = 0; j < nLinhas; j++)
        {
            cout << "["<< m[i][j] << "]\t";
        }
        cout << endl;
    }
}

int **matrizAloc(){
    int **mat;
    mat = (int **) malloc (nLinhas * sizeof (int*)) ;
    for (i=0; i < nLinhas; i++){
        mat[i] = (int *) malloc (nLinhas * sizeof (int)) ;
    }

   for (int lin = 0; lin < nLinhas; lin++)
   {
       for (int col = 0; col < nLinhas; col++)
       {
           if (lin == col)
           {
               mat[lin][col] = 0;
           }else{
               mat[lin][col] = peso(x, y, lin, col);
           }
       }
       
   }
    return mat;
}

void freeMatriz(int **m){
    for(i=0; i<nLinhas; i++){
        free(m[i]);
    }
    free(m);
}


int main(int argc, char**argv){

    leGrafo("aula3aeds.txt");
    coordenadas("aula3aeds.txt");
    //imprime();
    int **m = matrizAloc();
    imprimeMatriz(m);
    freeMatriz(m);

    return 0;
}
