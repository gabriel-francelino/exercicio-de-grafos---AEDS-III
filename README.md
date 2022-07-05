
## Relatório - Trabalho Prático 1 (AED's III)

Alunos: 
- Gabriel Fracelino Nascimento (2021.1.08.030) 
- Gabriel Kusumota Nadalin (2021.1.08.007) 
- Gabriel Piva Pereira (2021.1.08.008)

### Objetivo
O problema apresentado se trata de uma leitura de um arquivo, em que cada linha 
apresenta as coordenadas de um vértice no plano cartesiano. Assim, com todos os vértices 
do arquivo e suas respectivas coordenadas, deve-se representar um grafo completo, em que 
todos os vértices estão ligados entre si e cada aresta possui o peso correspondente a 
distância entre os dois vértices, calculada pela fórmula da distância euclidiana. Deve-se criar 
uma árvore geradora mínima do grafo e encontrar o maior subgrafo de três vértices dentro 
da árvore encontrada. Para este problema, que será implementado em C++, utilizaremos o algoritmo 
de árvore geradora mínima de Kruskal, classes para representação e sobrecarga de operadores.

### Abordagem
A abordagem utilizada para resolver o problema foi, inicialmente, salvar o número de
linhas (ou número de vertices do grafo) na variável nVertices. Após isso, foi feita a
leitura do arquivo, que foi salvo em uma matriz chamada matArquivo, que possui cada
linha do arquivo como uma linha da matriz, e para cada linha, 2 colunas que
representam as coordenadas X e Y do arquivo. 

Foram utilizadas as classes Aresta (que possui os vértices que a formam (v1 e v2) e o peso) e 
Grafo (que possui o seu número de vértices e um vetor com todas as suas arestas). Para o vetor 
de arestas, foi utilizada a classe [vector](https://cplusplus.com/reference/vector/vector/) do 
tipo Aresta.

```cpp
classe Aresta {
publico:
    inteiro v1;
    inteiro v2;
    inteiro peso;
    ...
};

classe Grafo {
publico:
    inteiro nVertices;
    vector<Aresta> arestas;
    ...
};
```

Nas classes foram definidos seus respecivos construtores e métodos, que serão apresentados a 
seguir no relatório.

Assim, com a matriz do arquivo e o número de vértices definidos, é criado um Grafo g, e com ele 
é chamada a função *criarGrafoArquivo()*, função da classe Grafo que recebe a matArquivo para 
gerar o grafo com seus vértices e suas respectivas distâncias. Na função, para todos os vértices 
representados na matriz, foi adicionada uma aresta para cada um dos outros vértices, formando 
assim o grafo completo. O peso de cada aresta foi calculado com a fórmula da distância euclidina 
e as arestas foram adicionadas com a função 
[push_back](https://cplusplus.com/reference/vector/vector/push_back/) no vetor de arestas do
grafo.

```cpp
// Classe Grafo
    funcao criarGrafoArquivo(inteiro **matArquivo) {
        para(inteiro i = 0; i < nVertices; i++) {
            para(inteiro j = i+1; j < nVertices; j++) {
                Aresta a(i+1, j+1, calcularPeso(matArquivo[i][0], matArquivo[i][1], matArquivo[j][0], matArquivo[j][1]));
                arestas.push_back(a);
            }
        }
    }
```

Assim, com o grafo já definido, é necessário criar a sua Árvore Geradora Mínima. Utiliza-se 
então o algoritmo de Kruskal, realizado em uma função da classe Grafo chamada *kruskal()*.

Para a ordenação das arestas foi utilizado o método 
[sort](https://cplusplus.com/reference/algorithm/sort/), possível através da sobreposição do 
operador < para a classe Aresta.

```cpp
// Classe Aresta
    lógico operator < (const Aresta& a2) const {
		retorno (peso < a2.peso);
	}
```

É utilizado um vetor chamado conjunto para realizar a estratégia dos conjuntos (union-find), 
presente no algoritmo kruskal, aliado com a função 
[memset](https://cplusplus.com/reference/cstring/memset/) para iniciar o vetor conjunto com -1 
em todas as posições. Após a execução do algoritmo de Kruskal, ele retorna um vetor de arestas 
chamado arvore, que possui apenas as arestas que formam a arvore geradora minima do grafo 
original.

```cpp
// Classe Grafo
    vector<Aresta> kruskal(){
        sort(arestas.begin(), arestas.end());
        vector<Aresta> arvore;
        inteiro *conjunto = new inteiro[nVertices+1];
        memset(conjunto, -1, sizeof(inteiro) * (nVertices+1));
        para(Aresta x : arestas) {
            inteiro v1 = buscarConjunto(conjunto, x.v1);
            inteiro v2 = buscarConjunto(conjunto, x.v2);
            se(v1 != v2) {
                arvore.emplace_back(x);
                unirConjunto(conjunto, v1, v2);
            }
        }
        retorno arvore;
    }
```

É criado um novo Grafo arvoreMinima, com nVertices, e o retorno da função *g.kruskal()*, ou 
seja, as arestas que formam a árvore de g, é salvo no vetor de arestas de arvoreMinima. 

Dessa forma, o grafo arvoreMinima representa a própria árvore geradora buscada, com seus 
nVertices e vetor de arestas que a compõe.

```cpp
// AGM com Kruskal
Grafo arvoreMinima(nVertices);
arvoreMinima.arestas = g.kruskal();
```

Após isso, é utilizada a classe Subgrafo, criada para representar um subgrafo de 3 vértices e o 
seu peso (soma de suas duas arestas), com seu construtor e métodos.

```cpp
classe Subgrafo {
publico:
    inteiro v1;
    inteiro v2;
    inteiro v3;
    inteiro peso;
    ...
};
```

Nessa classe, foi definida a função *definirMaiorSubgrafo()*, que recebe o grafo arvoreMinima.
Na função, é criado um subgrafo chamado maiorSub, iniciado com todos os dados -1. Com um for, 
para cada aresta x presente no vetor de arestas da árvore, é iniciado outro for que percorre 
todas as arestas y do mesmo vetor e compara se x tem algum vértice em comum com y, ou seja, se 
as arestas possuem um vértice em comum. Se sim, é criado um novo subgrafo s com os 3 vértices e 
a soma dos pesos de x e y. Esse subgrafo s é comparado com com o peso de maiorSub, e se for 
maior, ele se torna o maiorSub. Ao final das repetições, maiorSub terá como seus atributos os 
três vértices que formam o subgrafo com maior peso. 

```cpp
// Classe Subgrafo
    Subgrafo definirMaiorSubgrafo(Grafo arvoreMinima) {
        vector<Aresta> arestasArvore = arvoreMinima.arestas;
        Subgrafo maiorSub(-1, -1, -1, -1);
        para(Aresta x : arestasArvore) {
            para (Aresta y : arestasArvore) {
                se(x.v1 == y.v1 e x.v2 != y.v2) {
                    Subgrafo s(x.v2, y.v1, y.v2, (x.peso + y.peso));
                    se(s.peso > maiorSub.peso) {
                        maiorSub = s;
                    }
                }
                se(x.v1 == y.v2) {
                    Subgrafo s(x.v2, x.v1, y.v1, (x.peso + y.peso));
                    se(s.peso > maiorSub.peso) {
                        maiorSub = s;
                    }
                }
                se(x.v2 == y.v1) {
                    Subgrafo s(x.v1, x.v2, y.v2, (x.peso + y.peso));
                    se(s.peso > maiorSub.peso) {
                        maiorSub = s;
                    }
                }
                se(x.v2 == y.v2 e x.v1 != y.v1) {
                    Subgrafo s(x.v1, x.v2, y.v1, (x.peso + y.peso));
                    se(s.peso > maiorSub.peso) {
                        maiorSub = s;
                    }
                }
            }
        }
        returno maiorSub;
    }
```

É criado um Subgrafo e a função é chamada, passando arvoreMinima como argumento. Assim, com o maior subgrafo já definido, seus vértices e peso são mostrados na tela com a função *exibirMaiorSubgrafo()*, finalizando a execução.

```cpp
// Definicao do maior subgrafo da arvore
Subgrafo maiorSub = maiorSub.definirMaiorSubgrafo(arvoreMinima);
maiorSub.exibirMaiorSubgrafo();
```

### Respostas
Os dados apresentados na execução do código com cada um dos arquivos solicitados, com seu respectivo tempo de execução médio.
```
arc/a28.txt
276 6 7 
30
```
Executado em 0.6s


```
arc/att48.txt
35 10 26 
2231
```
Executado em 0.4s

```
arc/att532.txt
471 432 398 
1125
```
Executado em 0.8s

```
arc/berlin52.txt
15 43 33 
606
```
Executado em 0.4s

```
arc/bier127.txt
123 97 98 
7738
```
Executado em 0.6s

```
arc/brd14501.txt
13855 13825 12494 
1357
```
Executado em 432.9s
```
arc/burma14.txt
7 6 5 
5
```
Executado em 0.4s

```
arc/d15112.txt
12536 13960 5371 
1619
```
Executado em 512.8s

```
arc/eil101.txt
36 49 64 
20
```
Executado em 0.6s

### Conclusão
As maiores dificuldades foram a ordenação do vetor de arestas, realizada com a sobrecarga de 
operador na classe Aresta, que era necessária para a realização do algoritmo de Kruskal, e a 
criação da lógica da função definirMaiorSubgrafo, para definir o subgrafo com maior peso, além da refatoração do código para executar de forma mais otimizada e rápida.