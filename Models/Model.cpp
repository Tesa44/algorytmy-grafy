//
// Created by Mateusz on 27.05.2024.
//

#include "Model.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;




void Model::displayArray(int *array, int n) {
    cout << "[ ";
    for (int i = 0; i < n-1 ; i ++) {
        cout << array[i] << ", ";
    }
    cout << array[n-1] << " ]" << endl;
}

int Model::calculateEdges(int densityPercent) {
    double d = (double)densityPercent / 100;
    e = d*v*(v-1)/2;
    return e;
}

void Model::generateGraph(string mode) {
    srand(time(NULL));

    edgeList = new edgeS[e];
    edgeS edge;
    int begin = 0, end = v, weight;
    int notVisitedVertces[v];
    for (int i = 0; i < v; i++) {
        notVisitedVertces[i] = i;
    }
    notVisitedVertces[0] = -1;
    int i = 0;
    //Generowanie krawędzi do grafu spójnego
    while (i < v - 1) {
        while (!checkInArray(notVisitedVertces, v, end)) {
            end = rand() % v;
        }
        notVisitedVertces[end] = -1; // Zaznaczamy jako odwiedzony
        weight = rand() % 9 + 1;
        //cout << begin << end << weight << endl;
        //Wpisanie danych o utworzonej krawędzi do tablicy z krawędziami
        edge.begin = begin;
        edge.end = end;
        edge.weight = weight;
        edgeList[i] = edge;

        begin = end;
        i ++;
    }
    weight = rand() % 9 + 1;
    //cout << begin << "0" << weight;
    //Wpisanie ostatniej krawędzi tworzącej graf spójny
    edge.begin = begin;
    edge.end = 0;
    edge.weight = weight;
    edgeList[i] = edge;
    //Generowanie pozostałych losowych krawędzi
    i++;
    begin = rand() % v;
    end = rand() % v;
    while (i < e) {
        while (checkInEdgeStruct(begin,end, i+1) or begin == end) {
            begin = rand() % v;
            end = rand() % v;
            weight = rand() % 9 + 1;
        }
        edge.begin = begin;
        edge.end = end;
        edge.weight = weight;
        edgeList[i] = edge;
        i++;
    }
    if (mode == "test") return;
    cout << "Wygenerowana lista krawedzi grafu: " << endl;
    displayEdgeStruct(edgeList,e);
}

bool Model::checkInArray(int *arr,int n, int el) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == el) return true;
    }
    return false;
}

void Model::displayEdgeStruct(edgeS *edgeList, int n) {
    for (int i = 0 ; i < n ; i++) {
        edgeS curEl = edgeList[i];
        cout << curEl.begin << " " << curEl.end << " " << curEl.weight << endl;
    }
}

bool Model::checkInEdgeStruct(int begin, int end, int n) {
    edgeS curEl;
    for (int i = 0 ; i < n ; i++) {
        curEl = edgeList[i];
        if ((curEl.begin == begin and curEl.end == end) or (curEl.begin == end and curEl.end == begin)) return true;
    }
    return false;
}

void Model::convertFileToEdgeStruct(std::string path) {
    fstream file;
    file.open(path, ios_base::in);
    file >> v >> e; //Czytamy liczbę wierzchołków i krawędzi z pierwszej linii pliku txt
    int begin, end, weight;
    edgeList = new edgeS[e]; //inicjalizujemy listę do struktur krawędzi
    edgeS edge; //zmienna pomocniczna do przypisywania wartości z txt
    for (int i = 0; i < e; i++) {
        file >> begin >> end >> weight;  //początek, koniec, waga krawędzi zczytanej z pliku
        edge.begin = begin;
        edge.end = end;
        edge.weight = weight;
        edgeList[i] = edge;
    }
}

void Model::sortEdges(Model::edgeS *edgeListCopy, int e) {
    int i, j;
    int key,begin,end;
    for (i = 1; i < e; i++) {
        key = edgeListCopy[i].weight;
        begin = edgeListCopy[i].begin;
        end = edgeListCopy[i].end;
        j = i - 1;
        while (j >= 0 && edgeListCopy[j].weight > key) {
            edgeListCopy[j+1].weight = edgeListCopy[j].weight;
            edgeListCopy[j+1].begin = edgeListCopy[j].begin;
            edgeListCopy[j+1].end = edgeListCopy[j].end;
            j = j - 1;
        }
        edgeListCopy[j+1].weight = key;
        edgeListCopy[j+1].begin = begin;
        edgeListCopy[j+1].end = end;
    }
}

void Model::freeEdgeList() {
    delete []edgeList;
}
