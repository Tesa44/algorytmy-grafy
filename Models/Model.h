//
// Created by Mateusz on 27.05.2024.
//

#ifndef GRAPHAPP_MODEL_H
#define GRAPHAPP_MODEL_H
#include <iostream>
using namespace std;

class Model {
public:
    int v; // ilość wierzchołków
    int e; // ilość krawędzi
    void generateGraph(string mode = "default");   //wygerneruj graf jako lista krawędzi
    int calculateEdges(int densityPercent);
    void displayArray(int *array, int n);   //Wyświetl zawartość tablicy
    bool checkInArray(int *arr, int n, int el); //Sprawdzanie, czy w tablicy znajduje się podany element
    struct edgeS {  //Skrutura krawędzi
        int begin;  //wierzchołek początkowy
        int end;    //wierzchołek końcowy
        int weight; //waga krawędzi
    };
    edgeS *edgeList;    //Lista krawędzi
    void displayEdgeStruct(edgeS *edgeList, int n); //Wyświetlanie listy krawędzi
    void sortEdges(edgeS *edgeListCopy, int e);     //Sortowanie listy krawędzi według wagi rosnąco
    bool checkInEdgeStruct(int begin, int end, int n);  //Sprawdzanie, czy krawędź jest w liście krawędzi
    void convertFileToEdgeStruct(string path);      //Wczytanie z pliku txt listy krawędzi
    void freeEdgeList();
};


#endif //GRAPHAPP_MODEL_H
