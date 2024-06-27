//
// Created by Mateusz on 03.06.2024.
//

#ifndef GRAPHAPP_V3_MATRIXMODEL_H
#define GRAPHAPP_V3_MATRIXMODEL_H

#include "Model.h"

class MatrixModel : public Model {
public:
    int **incidientMatrix; //wskaźnik na macierz incydencji
    int **undirectedIncMatrix;  //Wskaźnik na nieskierowaną macierz incydencji
    int *weights; //Wagi krawędzi. Pozycja w tablicy odpowiada numerze krawędzi według kolejności w pliku txt
    void initMatrix();  //Inicjalizacja macierz indycencji skierowaną i nieskierowaną
    void copyMatrix(int **matrix, int **matrixCopy);    //Kopiowanie zawartości macierzy do innej macierzy
    void freeMatrix();  //Zwolnienie pamięci macierzy
    void displayMatrix(int **matrix);   //Wyświetlenie macierzy
    void loadMatrix(edgeS *edgeList);      //Załadowanie skierowanego grafu do macierzy indydencji ze struktury krawędzi
    void convertToUndirectedMatrix(edgeS *edgeList); //Tworzenie nieskierowanej macierzy indydencji ze skierowanej macierzy
};


#endif //GRAPHAPP_V3_MATRIXMODEL_H
