//
// Created by Mateusz on 03.06.2024.
//

#ifndef GRAPHAPP_V3_MATRIXALGORITHM_H
#define GRAPHAPP_V3_MATRIXALGORITHM_H


#include "Algorithm.h"

class MatrixAlgorithm : public Algorithm{
public:
    void primMatrix(int **incidientMatrix, int* weights, int v, int e, string mode = "default");
    void kruskalMatrix(int **incidientMatrix, int *weights, int v, int e,string mode = "default");
    void dijkstraMatrix(int **incidientMatrix, int *weights, int s, int v, int e,string mode = "default");
    void bellmanFordMatrix(int **incidientMatrix, int *weights, int s, int v, int e,string mode = "default");

private:
    int* findAdjInMatrix(int **matrix, int u, int v, int e);
    int findWeight(int **matrix, int u1, int u2, int v, int e, int* weights);
};


#endif //GRAPHAPP_V3_MATRIXALGORITHM_H
