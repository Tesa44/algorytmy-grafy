//
// Created by Mateusz on 03.06.2024.
//

#include "MatrixModel.h"
#include <iostream>
#include <stdio.h>
using namespace std;

void MatrixModel::initMatrix() {
    incidientMatrix = new int*[v];
    undirectedIncMatrix = new int*[v];
    for (int i = 0; i < v ; i++) {
        incidientMatrix[i] = new int[e];
        undirectedIncMatrix[i] = new int[e];
    }
    //Uzupełnienie całej macierzy zerami
    for (int i = 0; i < v ; i++){
        for (int j = 0; j < e; ++j) {
            incidientMatrix[i][j] = 0;
            undirectedIncMatrix[i][j] = 0;
        }
    }
}

void MatrixModel::loadMatrix(edgeS *edgeList) {
    initMatrix();
    weights = new int[e];
    edgeS curEdge;
    for (int i = 0; i < e; i++) {
        curEdge = edgeList[i];
        incidientMatrix[curEdge.begin][i] = 1;
        incidientMatrix[curEdge.end][i] = -1;
        weights[i] = curEdge.weight;
    }
}

void MatrixModel::displayMatrix(int **matrix) {
    cout << "Macierz incydencji: " << "v: " << v << " e: " << e << endl;
    cout << "v/kr ";
    for (int i = 0 ; i < e; i++) {
        printf("kr%i ",i+1);
    }
    cout << endl;
    for (int i = 0; i < v ; i++){
        printf("%-*d",3,i);
        for (int j = 0 ; j < e ; j ++) {
            if (j < 10)
                printf("%*d",4,matrix[i][j]);
            else
                printf("%*d",5,matrix[i][j]);
        }
        cout << endl;
    }
}

void MatrixModel::freeMatrix() {
    for (int i = 0; i < v ; i++) {
        delete[] incidientMatrix[i];
        delete[] undirectedIncMatrix[i];
    }
    delete[] incidientMatrix;
    delete[] undirectedIncMatrix;
}

void MatrixModel::copyMatrix(int **matrix, int **matrixCopy) {
    for (int i = 0; i < v ; i++){
        for (int j = 0 ; j < e ; j ++) {
            matrixCopy[i][j] = matrix[i][j];
        }
    }
}

void MatrixModel::convertToUndirectedMatrix(edgeS *edgeList) {
    edgeS curEdge;
    for (int i = 0; i < e; i++) {
        curEdge = edgeList[i];
        //file >> begin >> end >> weight;
        undirectedIncMatrix[curEdge.begin][i] = 1;
        undirectedIncMatrix[curEdge.end][i] = 1;
        //weights[i] = curEdge.weight;
    }
}
