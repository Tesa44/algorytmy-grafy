//
// Created by Mateusz on 03.06.2024.
//

#ifndef GRAPHAPP_V3_LISTMODEL_H
#define GRAPHAPP_V3_LISTMODEL_H

#include "Model.h"

class ListModel : public Model {
public:
    struct listS {  //Struktura sąsiada
        int v;  //Numer wierzchołka
        int w;  //Waga krawędzi
        listS *next;    //Wskaźnik na kolejnego sąsiada
    };
    listS **neighbourList;  //Lista sąsiedztwa
    listS **undirectedNList;    //Nieskierowana lista sąsiedztwa
    void loadNeighbourList(edgeS *edgeList);   //Załadowanie skierowanego grafu do listy sąsiedztwa ze struktury krawędzi
    void displayNeighbourList(ListModel:: listS **list);    //Wyświetlanie listy sąsiedztwa
    void freeNeighbourList();   //Zwolnienie pamięci listy sąsiedztwa
    void convertToUndirectedList(edgeS *edgeList);  //Tworzenie nieskierowanej listy sąsiedztwa ze skierowanej listy sąsiedztwa
};


#endif //GRAPHAPP_V3_LISTMODEL_H
