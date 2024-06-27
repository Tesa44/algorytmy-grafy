//
// Created by Mateusz on 27.05.2024.
//

#ifndef GRAPHAPP_MENU_H
#define GRAPHAPP_MENU_H
#include <iostream>
using namespace std;

class Menu {
public:
    char listChoice;
    char algorithmChoice;
    char displayChoice;
    char exitRepeatChoice;
    char graphChoice;
    void listMenu();
    void algorithmMenu();
    void graphMenu();
    int inputLen();
    int inputDensity();
    int inputStart(int v);
    int inputNumberOfTests();
    int n;
    bool checkChoices(char choice, char choiceQuantity);
    string inputPath();
    void displayMenu(string message);
    void exitRepeatMenu();

};


#endif //GRAPHAPP_MENU_H
