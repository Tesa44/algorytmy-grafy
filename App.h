//
// Created by Mateusz on 27.05.2024.
//

#ifndef GRAPHAPP_APP_H
#define GRAPHAPP_APP_H


#include "Menu.h"
#include "Models/Model.h"
#include "Models/ListModel.h"
#include "Models/MatrixModel.h"
#include "Algorithms/ListAlgorithm.h"
#include "Algorithms/MatrixAlgorithm.h"
class App {
public:
    Menu menu;
    Model model;
    ListModel listModel;
    MatrixModel matrixModel;
    ListAlgorithm listAlgorithm;
    MatrixAlgorithm matrixAlgorithm;
    double matrixDurTime = 0;   //Czas wykonywania sie algorytmu dla macierzy
    double listDurTime = 0;     //Czas wykonywania sie algorytmu dla listy sasiedztwa
    bool emptyFlag = true; //Sprawdzenie, czy jakis graf jest zaladowany w pamieci
    int numberOfTests;  //Ilosc testow do przeprowadzenia dla trybu testowania

    void runGraphPrep(); //podprogram przygotowujacy graf
    void runAlgorithms();   //Podprogram z mozliwoscia wybrania algorytmow
    void runTest();         //podprogram do testowania wydajnosci algorytmow
    void run();         //Glowny program łączący wyżej wymienione podprogramy

};


#endif //GRAPHAPP_APP_H
