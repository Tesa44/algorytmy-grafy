//
// Created by Mateusz on 03.06.2024.
//

#include "MatrixAlgorithm.h"
#include "Queue.h"
#include "Algorithm.h"

void MatrixAlgorithm::primMatrix(int **incidientMatrix, int *weights, int v, int e, string mode) {
    int *key = new int[v]; //Tablica do wag krawędzi
    int *p = new int[v];    //Tablica do poprzedników wierzchołków
    for (int i = 0; i < v ; i++) {
        key[i] = INF;
        p[i] = UNDEFINED;
    }
    key[0] = 0; //Wierzchołek startowy z drogą ustawioną na 0
    Queue queue(v); //inicjalizacja kolejki o pojemności ilości wierzchołków
    for (int i = 0; i < v; i++) queue.insertVertex({i,key[i]}); //Dodanie do kolejki wszystkich wierzchołków        V
    while (!queue.isEmpty()) {                                                                                                    //V
        Queue::vertex minV = queue.extractMin(); //Wybieramy wierzchołek o najkrótszej drodze z kolejki                             //logV
        int u = minV.v;     //Będziemy potrzebować tylko numer wierzchołka do reszty algorytmu
        int *adj = findAdjInMatrix(incidientMatrix,u,v,e); //Tablica z sąsiadami wierzchołka u                                //V*E
        for (int i = 1 ; i < adj[0] ; i++){ //adj[0] przechowuje długość tablicy z sąsiadami                                        //V-1 -> V
            int u2 = adj[i];
            int weight = findWeight(incidientMatrix,u,u2,v,e,weights); //waga między wierzchołem u a danym sąsiadem         //E
            if(queue.position[u2] != -1 and weight < key[u2] ) {
                key[u2] = weight;
                p[u2] = u;
                queue.decreaseKey(u2, key[u2]); //Zaktualizuj drogę w kolejce i napraw kopiec                            //LogE
            }
        }
    }
    //Wyświetlanie wyniku
    if (mode == "test") return;
    int mst = 0;
    cout << "Lista krawedzi do minimalnego drzewa rozpinajacego: " << endl;
    for (int i = 1 ; i < v ;i++){
        cout << p[i] << " - " << i << " : " << key[i] << endl;
        mst += key[i];
    }
    cout << "MST = " << mst << endl;
}

//u - wierzchołek dla którego szukamy sąsiadów
//v - ilość wierzchołków w grafie
//e - ilość krawędzi w grafie
int* MatrixAlgorithm::findAdjInMatrix(int **matrix, int u, int v, int e) {
    int adjCounter = 0;
    //Liczenie ilości sąsiadów dla podanego wierzchołka u
    for (int i = 0; i < e ; i++){
        if (matrix[u][i] == 1) adjCounter ++;
    }
    int *adj = new int[adjCounter+1]; //inicjalizacja dynamicznej tablicy dla sąsiadów
    adj[0] = adjCounter + 1; //pierwszy el w tablicy określa jej rozmiar
    adjCounter = 1; //zmieniamy licznik na 1 bo od tej pozycji będziemy wpisywać sąsiadów
    for (int i = 0; i < e ; i++){
        if (matrix[u][i] == 1) {
            for (int j = 0 ; j < v ; j++){
                if ((matrix[j][i] == 1 or matrix[j][i] == -1) and j != u) {
                    adj[adjCounter] = j;
                    adjCounter ++;
                    break;
                }
            }
        }
    }
    return adj;
}

int MatrixAlgorithm::findWeight(int **matrix, int u1, int u2, int v, int e, int *weights) {
    int edgeNum;
    for (int i = 0; i < e ; i++){
        if (matrix[u1][i] == 1 and (matrix[u2][i] == 1 or matrix[u2][i] == -1)) { //Szukamy numeru krawędzi, w których jest wierzchołek u1 i u2
            edgeNum = i;
            break;
        }
    }
    return weights[edgeNum];
}

///////////////////////////KRUSKA//////////////////////////////////////

void MatrixAlgorithm::kruskalMatrix(int **incidientMatrix, int *weights, int v, int e,string mode) {
    Model model;
    Model::edgeS *result = new Model::edgeS[v-1]; //Lista krawędzi wynikowych algorytmu
    int resultCounter = 0;
    Model::edgeS *edgeList = new Model::edgeS[e]; //Lista do krawędzi
    //Tworzenie listy krawędzi z macierzy incydencji
    for (int i = 0 ; i < e ; i++){
        Model::edgeS edge;
        for (int j = 0 ; j < v ; j++) {
            if (incidientMatrix[j][i] == 1) edge.begin = j;
            else if (incidientMatrix[j][i] == -1) edge.end = j;
        }
        edge.weight = weights[i];
        edgeList[i] = edge;
    }

    int *rank = new int[v];
    int *parent = new int[v];
    model.sortEdges(edgeList, e); //sortowanie krawędzi według wagi rosnąco
    //Inicjalizacja tablic do algorytmu
    for (int i = 0; i < v; i++) {
        rank[i] = 0; //Ranga każdego zbioru to 0
        parent[i] = i;  //Każdy wierzchołek jest swoim rodzicem
    }
    Model::edgeS curEdge;
    int u1, u2;
    for (int i = 0; i < e and resultCounter < v - 1; i++) {
        curEdge = edgeList[i];
        u1 = curEdge.begin;
        u2 = curEdge.end;

        int parentU1 = findParent(u1, parent);
        int parentU2 = findParent(u2, parent);

        if (parentU1 != parentU2) {
            result[resultCounter] = curEdge;
            resultCounter++;
            unionVertices(parentU1,parentU2,parent,rank);

        }
    }
    if (mode == "test") return;
    displayMST(result,resultCounter);
}

/////////////////////////////////DIJKSTRA//////////////////////////////

void MatrixAlgorithm::dijkstraMatrix(int **incidientMatrix, int *weights, int s, int v, int e,string mode) {
    int *distance = new int[v];
    int *parent = new int[v];
    int *extracted = new int[v];    //Tablica do sprawdzonych już wierzchołków
    //Inicjalizacja tablic z odległością i rodzicem
    for (int i = 0; i < v; i++) {
        distance[i] = INF; //Każda droga ma długość nieskończoność
        parent[i] = UNDEFINED; //Każdy wierzchołek nie ma rodzica
        extracted[i] = UNDEFINED;
    }
    distance[s] = 0; //Ustawiamy drogę wierzchołka startowego na 0

    Queue queue(v); //inicjalizacja kolejki o pojemności ilości wierzchołków
    for (int i = 0 ; i < v ; i++) queue.insertVertex({i, distance[i]}); //Dodanie do kolejki wszystkich wierzchołków
    while (!queue.isEmpty()) {
        Queue::vertex minV = queue.extractMin(); //Wybieramy wierzchołek o najkrótszej drodze z kolejki
        int u = minV.v; //Dodajemy wierzchołek do listy z odwiedzonymi wierzchołkami
        int *adj = findAdjInMatrix(incidientMatrix,u,v,e); //Tablica z sąsiadami wierzchołka u
        for (int i = 1 ; i < adj[0] ; i++){ //adj[0] przechowuje długość tablicy z sąsiadami
            int u2 = adj[i];    //kolejni sąsiedzi wierzchołka u
            int weight = findWeight(incidientMatrix,u,u2,v,e,weights); //waga między wierzchołem u a danym sąsiadem
            if (distance[u2] > distance[u] + weight) {
                //Relaksacja krawędzi
                distance[u2] = distance[u] + weight;
                parent[u2] = u;
                if (queue.position[u2] != -1)   queue.decreaseKey(u2,distance[u2]); //Jeśli wierzchołek jest w kolejce to zaktualizuj jego droge i napraw kopiec
            }
        }
    }
    if (mode == "test") return;
    displayShortestPath(distance,parent,v);
}

/////////////////////////////////BELLMAN-FORD//////////////////////////////

void MatrixAlgorithm::bellmanFordMatrix(int **incidientMatrix, int *weights, int s, int v, int e,string mode) {
    Model::edgeS *edgeList = new Model::edgeS[e]; //Lista do krawędzi
    //Tworzenie listy krawędzi z macierzy incydencji
    for (int i = 0 ; i < e ; i++) {
        Model::edgeS edge;
        for (int j = 0; j < v; j++) {
            if (incidientMatrix[j][i] == 1) edge.begin = j; //Przypisz wierzchołek początkowy
            else if (incidientMatrix[j][i] == -1) edge.end = j; //Przypisz wierzchołek końcowy
        }
        edge.weight = weights[i]; //Przypisz wagę z tablicy wag, gdzie wagi są według numerów krawędzi
        edgeList[i] = edge; //Wpisz krawędź do listy krawędzi
    }

    int *distance = new int[v];
    int *parent = new int[v];
    //Inicjalizacja tablic z odległością i rodzicem
    for (int i = 0; i < v; i++) {
        distance[i] = INF; //Każda droga ma długość nieskończoność
        parent[i] = UNDEFINED; //Każdy wierzchołek nie ma rodzica
    }
    distance[s] = 0; //Droga wierzchołka startowego ustawiana jest na 0

    for (int i = 1 ; i < v - 1 ; i++) {
        int stopCounter = 0;
        for (int edgeNum = 0 ; edgeNum < e ; edgeNum++) {
            Model::edgeS curEdge = edgeList[edgeNum];
            int u1 = curEdge.begin;
            int u2 = curEdge.end;
            int weight = curEdge.weight;
            if (distance[u2] > distance[u1] + weight) {
                //Relaksacja krawędzi
                distance[u2] = distance[u1] + weight;
                parent[u2] = u1;
            }
            else stopCounter++; //jeśli nie następuje relaksacja krawędzi to zwięsz licznik zatrzymania
        }
        if (stopCounter == e) break;    //Jeśli nie nastąpiła ani jedna relaksacja krawędzi to można skończyć pętlę i
    }
    //Sprawdzenie, czy nie ma cyklu ujemnego
    for (int edgeNum = 0 ; edgeNum < e; edgeNum++) {
        Model::edgeS curEdge = edgeList[edgeNum];
        int u1 = curEdge.begin;
        int u2 = curEdge.end;
        int weight = curEdge.weight;
        if (distance[u2] > distance[u1] + weight) {
            cout << "CYKL UJEMNY!!!!" << endl;
            break;
        }
    }
    if (mode == "test") return;
    displayShortestPath(distance,parent,v);
}