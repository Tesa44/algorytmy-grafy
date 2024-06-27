//
// Created by Mateusz on 02.06.2024.
//

#ifndef GRAPHAPP_QUEUE_H
#define GRAPHAPP_QUEUE_H


class Queue {
public:
    Queue(int capacity);    //konstruktor kolejki | capacity - pojemność kolejki, czyli ilość wierzchołków
    struct vertex {
        int v;  //Numer wierzchołka
        int distance;   //odległość od wierzchołka startowego
    };
    vertex *heap;   //kopiec
    int *position; //pozycja wierzchołków w kopcu
    int size;   //rozmiar kopca
    int capacity;   //Pojemność kolejki
    void insertVertex(vertex ver);  //Dodaj wierzołek do kolejki
    vertex extractMin();    //Wyciągnij wierzchołek o najkrószej drodze
    void decreaseKey(int ver, int distance);    //Zaktualizuj drogę dla danego wierzchołka
    bool isEmpty();     //sprawdzanie czy kopiec pusty
    void heapify(int idx);  //Napraw kopiec

private:
    int parent(int idx) const { return (idx - 1) / 2; }     //Wzór na znalezienie rodzica
    int left(int idx) const { return 2 * idx + 1; }     //Wzór na znalezienie lewego potomka
    int right(int idx) const { return 2 * idx + 2; }    //Wzór na znalezienie prawego potomka




};


#endif //GRAPHAPP_QUEUE_H
