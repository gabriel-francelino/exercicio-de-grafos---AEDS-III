# include <stdio.h>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

int nLinhas = 0, i=0;
//int *x, *y;

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
        cout << "Não foi possível ler o arquivo." << endl;
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
        cout << "Não foi possível ler o arquivo." << endl;
    }
        
    return 0;
}

int distEuclid(){
    int dist;

    for ( i = 0; i < nLinhas/2; i++)
    {
        dist = sqrt((x[i+1]-x[i])^2 + (y[i+1]-y[i])^2 );
    }
    
    return dist;
}

void imprime(){
    for (int i = 0; i < nLinhas; i++)
    {
        cout << x[i] << endl;
    }
}

int **matrizAloc(){
    int **mat;
    mat = (int **) malloc (nLinhas * sizeof (int**)) ;
    for (i=0; i < nLinhas; i++){
        mat[i] = (int *) malloc (nLinhas * sizeof (int*)) ;
    }

   for (int lin = 0; lin < nLinhas; lin++)
   {
       for (int col = 0; col < nLinhas; col++)
       {
           mat[lin][col] = 0;
       }
       
   }
    return mat;
}


int main(int argc, char**argv){

    leGrafo("teste.txt");
    coordenadas("teste.txt");
    imprime();

    int **m = matrizAloc();

    for ( i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            cout << m[i][j] << " - ";
        }
        cout << endl;
    }
    

    float distEuc = distEuclid();

    cout << "numero de linhas: " << nLinhas << endl;

    return 0;
}