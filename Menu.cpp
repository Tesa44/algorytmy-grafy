//
// Created by Mateusz on 27.05.2024.
//

#include "Menu.h"
#include <iostream>
using namespace std;


void Menu::listMenu() {
    while (true) {
        cout << "Witaj w menu programu" << endl;
        cout << "1. Uzyj ostatnio utworzony graf" << endl;
        cout << "2. Wygeneruj graf losowo" << endl;
        cout << "3. Wczytaj graf z pliku o zadanej nazwie" << endl;
        cout << "4. Tryb do testowania szybkosci algorytmow grafow" << endl;
        cin >> listChoice;
        if (checkChoices(listChoice, '4'))
            return;
    }
}
void Menu::graphMenu() {
    while (true) {
        cout << "Witaj w trybie testowania szybkosci algorytmow" << endl;
        cout << "Wybierz reprezentacje grafu do testowania" << endl;
        cout << "1. Macierz incydencji" << endl;
        cout << "2. Lista sasiedztwa" << endl;
        cin >> graphChoice;
        if (checkChoices(graphChoice, '2'))
            return;
    }
}

string Menu::inputPath() {
    string path;
    cout << "Podaj sciezke do pliku tekstowego " << endl;
    cin >> path;
    return path;
}

int Menu::inputLen() {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj ilosc wierzcholkow do grafu" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))
                guard = false;
        }
        if (guard) {
            int n = stoi(input);
            return n;
        }
        cout << "To nie jest liczba" << endl;
    }
}

int Menu::inputDensity() {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj gestosc grafu (0 - 100) [%]" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))
                guard = false;
        }
        if (guard) {
            int n = stoi(input);
            if (n <= 0 or n > 100) return 50;
            return n;
        }
        cout << "To nie jest liczba" << endl;
    }
}


//Metoda służy do sprawdzania czy wybór wpisany przez użytkownika jest zgodny z jakimkolwiek wyborem
//char choice - znak podany przez użytkownika określający wybór
//char choiceQuantity - ile posiadamy wyborów w menu
bool Menu::checkChoices(char choice, char choiceQuantity) {
    if (choice >= '1' && choice <= choiceQuantity)
        return true;
    cout << "Niepoprawny wybor!" << endl;
    return false;
}

void Menu::displayMenu(string message) {
    while (true) {
        cout << "Czy wyswietlic " << message << " graf" << endl << "w postaci macierzy incydencji i listy sasiedztwa?" << endl;
        cout << "1. Tak" << endl;
        cout << "2. Nie" << endl;
        cin >> displayChoice;
        if (checkChoices(displayChoice, '2'))
            return;
    }
}

void Menu::exitRepeatMenu() {
    while (true) {
        cout << "Czy chcesz wyjsc z programu?" << endl;
        cout << "1. Wroc do algorytmow" << endl;
        cout << "2. Zamknij program" << endl;
        cin >> exitRepeatChoice;
        if (checkChoices(exitRepeatChoice, '2'))
            return;
    }
}

void Menu::algorithmMenu() {
    while (true) {
        cout << "Wybierz algorytm dla ostatnio utworzonego lub wczytanego grafu" << endl;
        cout << "1. Algorytm Prime" << endl;
        cout << "2. Algorytm Kruskala" << endl;
        cout << "3. Algorytm Dijkstry" << endl;
        cout << "4. Algorytm Bellmana-Forda" << endl;
        cin >> algorithmChoice;
        if (checkChoices(algorithmChoice, '4'))
            return;
    }
}

int Menu::inputStart(int v) {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj wierzcholek startowy" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))
                guard = false;
        }
        if (guard) {
            int n = stoi(input);
            if (n >= v) return 0;
            return n;
        }
        cout << "To nie jest liczba" << endl;
    }
}

int Menu::inputNumberOfTests() {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj liczbe testow, z ktorych zostanie obliczony sredni czas wybranego sortowania" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))     //Sprawdzanie czy każdy podany znak jest liczbą
                guard = false;
        }
        if (guard) {
            int numberOfTests = stoi(input);    //Konwertowanie string na int
            return numberOfTests;
        }
        cout << "To nie jest liczba" << endl;
    }
}
