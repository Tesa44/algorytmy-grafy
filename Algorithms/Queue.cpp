//
// Created by Mateusz on 02.06.2024.
//

#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue(int cap) {
    capacity = cap;
    size = 0;
    heap = new vertex[cap];
    position = new int[cap];
    for (int i = 0; i < cap ; i++) position[i] = -1;
}

void Queue::insertVertex(vertex ver) {
    if (size == capacity) {
        cout << "Stos przepelniony" << endl;
        return;
    }

    size++;
    int i = size - 1;
    heap[i] = ver;
    position[ver.v] = i;

    //Naprawa kopca
    while (i != 0 && heap[parent(i)].distance > heap[i].distance) {
        std::swap(heap[i], heap[parent(i)]);
        std::swap(position[heap[i].v], position[heap[parent(i)].v]);
        i = parent(i);
    }
}

Queue::vertex Queue::extractMin() {
    if (size <= 0) {
        return { -1, INT_MAX };
    }
    if (size == 1) {
        size--;
        position[heap[0].v] = -1;
        return heap[0];
    }

    vertex root = heap[0];  //Pobieramy najmniejszy element
    heap[0] = heap[size - 1];   //Zamieniamy go miejscem z ostatnim elementem
    position[heap[0].v] = 0;    //Ustawiamy pozycje ostatniego elementu na pozycje 0.
    position[root.v] = -1;      //Pozycje najmniejszego elementu ustawiamy na -1. Oznacza to, że tego elementu już nie ma w kolejce
    size--;                     //Zmniejszamy rozmiar kolejki
    heapify(0);             //Naprawiamy kopiec

    return root;                //Zwracamy najmniejszy element
}

void Queue::decreaseKey(int vertex, int distance) {
    int i = position[vertex];
    heap[i].distance = distance;
    //Naprawa kopca
    while (i != 0 && heap[parent(i)].distance > heap[i].distance) {
        std::swap(heap[i], heap[parent(i)]);
        std::swap(position[heap[i].v], position[heap[parent(i)].v]);
        i = parent(i);
    }
}

void Queue::heapify(int idx) {
    int l = left(idx);  //lewe dziecko rodzica idx
    int r = right(idx); //Prawe dziecko rodzica idx
    int smallest = idx;
    if (l < size && heap[l].distance < heap[smallest].distance) {
        smallest = l;
    }
    if (r < size && heap[r].distance < heap[smallest].distance) {
        smallest = r;
    }
    if (smallest != idx) {
        std::swap(heap[idx], heap[smallest]);
        std::swap(position[heap[idx].v], position[heap[smallest].v]);
        heapify(smallest);
    }
}

bool Queue::isEmpty() {
    return size == 0;
}
