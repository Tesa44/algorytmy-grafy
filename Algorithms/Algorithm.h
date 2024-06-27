//
// Created by Mateusz on 27.05.2024.
//

#ifndef GRAPHAPP_ALGORITHMS_H
#define GRAPHAPP_ALGORITHMS_H


#include "../Models/Model.h"
#include "../Models/ListModel.h"
#define INF 999999
#define UNDEFINED -1

class Algorithm {
public:
    void displayShortestPath(int *distance, int *parent, int v);
    void displayMST(Model::edgeS *edgeList, int e);
    int findParent(int u, int *parent);
    void unionVertices(int u1, int u2, int *parent, int *rank); //łączenie zbiorów wierzchołków

};




#endif //GRAPHAPP_ALGORITHMS_H
