//
// Created by Mateusz on 27.05.2024.
//

#include "Algorithm.h"

//Funkcja do wyświetlania listy krawędzi drzewa MST
void Algorithm::displayMST(Model::edgeS *edgeList, int e) {
    int mst = 0;
    Model model;
    cout << "Lista krawedzi do minimalnego drzewa rozpinajacego: " << endl;\
    model.displayEdgeStruct(edgeList,e);
    for (int i = 0 ; i < e ;i++){
        mst += edgeList[i].weight;
    }
    cout << "MST = " << mst << endl;
}

//Funkcja do szukania rodzica wierzchołka
int Algorithm::findParent(int u, int *parent) {
    if (parent[u] != u) {
        parent[u] = findParent(parent[u], parent);
    }
    return parent[u];
}

//Funckja do łączenia zbiorów wierzchołków
void Algorithm::unionVertices(int u1, int u2, int *parent, int *rank)  {
    int rootU1 = findParent(u1, parent);
    int rootU2 = findParent(u2, parent);
    //Sprawdzanie, czy grafy nie są już połączone
    if (rootU1 != rootU2) {
        //Łączenie grafu o mniejszej wadze do grafu o większej wadze
        if (rank[rootU1] < rank[rootU2]) {
            parent[rootU1] = rootU2;
        } else if (rank[rootU1] > rank[rootU2]) {
            parent[rootU2] = rootU1;
        } else {
            parent[rootU2] = rootU1;    //Gdy są równe to łączymy do pierwszego grafu i zwiększamy jego rangę
            rank[rootU1]++;
        }
    }
}
//Funkcja do wyświetlania najkrótszej drogi odwiedzenia wszystkich wierzchołków
void Algorithm::displayShortestPath(int *distance, int *parent, int v) {
    cout << "Wierzcholki        " ;
    for (int i = 0; i < v ; i++) {
        cout << i << "   ";
    }
    cout << endl;
    cout << "Distance/Parent  " ;
    for (int i = 0; i < v; i++) {
        cout << distance[i] << "/" << parent[i] << " ";
    }
    cout << endl;
}


