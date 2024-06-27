//
// Created by Mateusz on 03.06.2024.
//

#include "ListAlgorithm.h"
#include "Algorithm.h"
#include "Queue.h"
//////////////////////////////PRIME//////////////////////////////////

//mode: wpisać "test" dla trybu bez wyświetlania wyników
//v - ilość wierzchołków
void ListAlgorithm::primList(ListModel::listS **neighbourList, int v, string mode) {
    int *key = new int[v]; //Tablica do wag krawędzi
    int *p = new int[v];    //Tablica do poprzedników wierzchołków
    for (int i = 0; i < v ; i++) {
        key[i] = INF;
        p[i] = UNDEFINED;
    }
    key[0] = 0; //Wierzchołek startowy z drogą 0
    Queue queue(v); //inicjalizacja kolejki o pojemności ilości wierzchołków
    for (int i = 0; i < v; i++) queue.insertVertex({i,key[i]}); //Dodanie do kolejki wszystkich wierzchołków
    ListModel::listS *adj;
    while (!queue.isEmpty()) {
        Queue::vertex minV = queue.extractMin(); //Wybieramy wierzchołek o najkrótszej drodze z kolejki i go usuwamy z kolejki
        int u = minV.v;  //Będziemy potrzebować tylko numer wierzchołka do reszty algorytmu
        adj = neighbourList[u]; //pierwszy sąsiad
        while (adj) {   //Kolejni sąsiedzi
            if(queue.position[adj->v] != -1 and adj->w < key[adj->v] ) {    //Jeżeli sąsiad v jest w kolejce i jego obecna droga jest większa od drogi do wierzchołka u
                key[adj->v] = adj->w;      //to ustaw nową drogę
                p[adj->v] = u;              //Ustaw nowego rodzica
                queue.decreaseKey(adj->v, key[adj->v]); //Zaktualizuj drogę w kolejce i napraw kopiec
            }
            adj = adj->next;
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

////////////////////////////////KRUSKAL////////////////////////////////////////

void ListAlgorithm::kruskalList(ListModel::listS **neighbourList, int v, int e,string mode) {
    Model model;
    ListModel::listS *adj;
    Model::edgeS *result = new Model::edgeS[v-1]; //Lista krawędzi wynikowych algorytmu
    int resultCounter = 0;
    Model::edgeS *edgeList = new Model::edgeS[e]; //Lista do krawędzi
    int edgeCounter = 0;
    //Tworzenie listy krawędzi z listy sąsiedztwa
    for (int i = 0; i < v; i++) {
        adj = neighbourList[i];
        while (adj) {
            Model::edgeS edge;
            edge.begin = i;
            edge.end = adj->v;
            edge.weight = adj->w;
            edgeList[edgeCounter] = edge;
            edgeCounter++;

            adj = adj->next;
        }

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
    for (int i = 0; i < e and resultCounter < v - 1; i++) { //Algorytm może się skończyć, gdy przejdziemy wszystkie krawędzie lub będziemy mieć v-1 krawędzi w wyniku
        curEdge = edgeList[i];  //Pobieranie bieżącej krawędzi
        u1 = curEdge.begin; //pierwszy wierzchołek krawędzi
        u2 = curEdge.end;   //drugi

        int parentU1 = findParent(u1, parent);  //Szukamy rodzica pierwszego wierzchołka w tablicy parentów
        int parentU2 = findParent(u2, parent);  //Szukamy rodzica drugiego wierzchołka w tablicy parentów
        if (parentU1 != parentU2) {             //Jeżeli rodzice nie są tacy sami to znaczy, że grafy nie są połączone
            result[resultCounter] = curEdge;    //Dodajemy krawędź do wyniku
            resultCounter++;                    //Zwiększamy licznik krawędzi wynikowych
            unionVertices(parentU1,parentU2,parent,rank);   //Łączymy dwa grafy w jeden

        }
    }
    //Wyświetlanie wyniku
    if (mode == "test") return;
    displayMST(result,resultCounter);
}

void ListAlgorithm::dijkstraList(ListModel::listS **neighbourList, int s, int v, int e,string mode) {
    int *distance = new int[v];
    int *parent = new int[v];
    //int *extracted = new int[v];    //Tablica do sprawdzonych już wierzchołków
    //Inicjalizacja tablic z odległością i rodzicem
    for (int i = 0; i < v; i++) {
        distance[i] = INF; //Każda droga ma długość nieskończoność
        parent[i] = UNDEFINED; //Każdy wierzchołek nie ma rodzica
        //extracted[i] = UNDEFINED;
    }
    distance[s] = 0;
    Queue queue(v); //inicjalizacja kolejki o pojemności ilości wierzchołków
    for (int i = 0 ; i < v ; i++) queue.insertVertex({i, distance[i]}); //Dodanie do kolejki wszystkich wierzchołków
    ListModel::listS *adj;  //Lista sąsiadów
    while (!queue.isEmpty()) {
        Queue::vertex minV = queue.extractMin();    //Wyciągnij z kolejki wierzchołek o najkrótszej drodze
        int u = minV.v;     //Będziemy potrzebować tylko numer wierzchołka do reszty algorytmu
        adj = neighbourList[u]; //pierwszy sąsiad
        while (adj) {
            if ( distance[adj->v] > distance[u] + adj->w) {
                //Relaksacja krawędzi
                distance[adj->v] = distance[u] + adj->w;
                parent[adj->v] = u;
                if (queue.position[adj->v] != -1)   queue.decreaseKey(adj->v,distance[adj->v]); //Jeśli wierzchołek jest w kolejce to zaktualizuj jego droge i napraw kopiec
            }
            adj = adj->next;
        }
    }
    if (mode == "test") return;
    displayShortestPath(distance,parent,v);
}


void ListAlgorithm::bellmanFordList(ListModel::listS **neighbourList, int s, int v, int e,string mode) {
    ListModel::listS *adj;
    Model::edgeS *edgeList = new Model::edgeS[e]; //Lista do krawędzi
    int edgeCounter = 0;
    //Tworzenie listy krawędzi z listy sąsiedztwa
    for (int i = 0; i < v; i++) {
        adj = neighbourList[i];
        while (adj) {
            Model::edgeS edge;
            edge.begin = i;
            edge.end = adj->v;
            edge.weight = adj->w;
            edgeList[edgeCounter] = edge;
            edgeCounter++;

            adj = adj->next;
        }
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
