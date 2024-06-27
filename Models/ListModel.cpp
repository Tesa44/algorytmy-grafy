//
// Created by Mateusz on 03.06.2024.
//

#include <iomanip>
#include "ListModel.h"

void ListModel::loadNeighbourList(edgeS *edgeList) {
    neighbourList = new listS*[v];
    undirectedNList = new listS *[v];
    //Tablicę wypełniamy pustymi listami
    for (int i = 0; i < v ; i++) {
        neighbourList[i] = NULL;
        undirectedNList[i] = NULL;
    }
    //int begin, end, weight;
    listS *p, *r;
    edgeS curEdge;
    for (int i = 0; i < e ; i++) {
        curEdge = edgeList[i];
        //file >> begin >> end >> weight;  //początek, koniec, waga krawędzi zczytanej z pliku
        p = new listS; //Tworzymy nowy element
        p->v = curEdge.end;     //Numerujemy go jako wierzchołek końcowy
        p->w = curEdge.weight;  //Przypisujemy wagę
        p->next = neighbourList[curEdge.begin]; //Dodajemy go na początek listy sąsiedztwa [begin]
        neighbourList[curEdge.begin] = p;
    }
}

void ListModel::convertToUndirectedList(edgeS *edgeList) {
    //inicjalizacja nowej listy sąsiadów
    undirectedNList = new listS *[v];
    //Tablicę wypełniamy pustymi listami
    for (int i = 0; i < v; i++) undirectedNList[i] = NULL;
    listS *p, *r;
    edgeS curEdge;
    for (int i = 0; i < e; i++) {
        curEdge = edgeList[i];
        //file >> begin >> end >> weight;  //początek, koniec, waga krawędzi zczytanej z pliku
        p = new listS; //Tworzymy nowy element
        p->v = curEdge.end;     //Numerujemy go jako wierzchołek końcowy
        p->w = curEdge.weight;  //Przypisujemy wagę
        p->next = undirectedNList[curEdge.begin]; //Dodajemy go na początek listy sąsiedztwa [begin]
        undirectedNList[curEdge.begin] = p;
        //Teraz traktujemy wierzchołek startowy jako końcowy i końcowy jako startowy
        r = new listS;
        r->v = curEdge.begin;
        r->w = curEdge.weight;
        r->next = undirectedNList[curEdge.end];
        undirectedNList[curEdge.end] = r;
    }
}

void ListModel::displayNeighbourList(ListModel:: listS **list) {
    listS *p;
    cout << "Lista sasiedztwa: " << "v: " << v << " e: " << e << endl;
    for(int i = 0; i < v; i++)
    {
        cout << "v [" << i << "] = ";
        p =  list[i];
        while(p)
        {
            cout << setw (3) << p->v <<"(" << p->w << ")";
            p = p->next;
        }
        cout << endl;
    }
}

void ListModel::freeNeighbourList() {
    listS *p, *r;
    for(int i = 0; i < v; i++)
    {
        p =  neighbourList[i];
        while(p)
        {
            r = p;
            p = p->next;
            delete r;
        }
    }
    delete [] neighbourList;
    //Jeśli nieskierowana lista sąsiedztwa zawiera elementy to z niej też zwolnij pamięć
    if (undirectedNList[0] !=NULL) {
        listS *up, *ur;
        for (int i = 0; i < v; i++) {
            up = undirectedNList[i];
            while (up) {
                ur = up;
                up = up->next;
                delete ur;
            }
        }
        delete[] undirectedNList;
    }
}
