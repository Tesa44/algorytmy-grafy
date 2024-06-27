//
// Created by Mateusz on 27.05.2024.
//

#include <chrono>
#include "App.h"
#include "Menu.h"

using namespace std::chrono;

void App::runGraphPrep(){
    menu.listMenu();
    switch (menu.listChoice) {
        case '1':
            if (emptyFlag) {
                cout << "Nie masz utworzonego grafu" << endl;
                model.v = listModel.v = matrixModel.v = menu.inputLen();
                model.e = listModel.e = matrixModel.e = model.calculateEdges(menu.inputDensity());
                model.generateGraph();
                matrixModel.loadMatrix(model.edgeList);
                listModel.loadNeighbourList(model.edgeList);
                menu.displayMenu("wygenerowany");
                switch (menu.displayChoice) {
                    case '1':
                        cout << "Twoj graf to: " << endl;
                        matrixModel.displayMatrix(matrixModel.incidientMatrix);
                        listModel.displayNeighbourList(listModel.neighbourList);
                        break;
                }
                emptyFlag = false;
            }
            else {
                menu.displayMenu("obecny");
                switch (menu.displayChoice) {
                    case '1':
                        cout << "Twoj graf to: " << endl;
                        matrixModel.displayMatrix(matrixModel.incidientMatrix);
                        listModel.displayNeighbourList(listModel.neighbourList);
                        break;
                }
            }
            break;
        case '2':
            model.v = listModel.v = matrixModel.v = menu.inputLen();
            model.e = listModel.e = matrixModel.e = model.calculateEdges(menu.inputDensity());
            model.generateGraph();
            matrixModel.loadMatrix(model.edgeList);
            listModel.loadNeighbourList(model.edgeList);
            menu.displayMenu("wygenerowany");
            switch (menu.displayChoice) {
                case '1':
                    cout << "Twoj graf to: " << endl;
                    matrixModel.displayMatrix(matrixModel.incidientMatrix);
                    listModel.displayNeighbourList(listModel.neighbourList);
                    break;
            }
            emptyFlag = false;
            break;
        case '3':
            model.convertFileToEdgeStruct(menu.inputPath());
            matrixModel.v = listModel.v = model.v;
            matrixModel.e = listModel.e = model.e;
            matrixModel.loadMatrix(model.edgeList);
            listModel.loadNeighbourList(model.edgeList);
            menu.displayMenu("wczytany");
            switch (menu.displayChoice) {
                case '1':
                    cout << "Twoj graf to: " << endl;
                    matrixModel.displayMatrix(matrixModel.incidientMatrix);
                    listModel.displayNeighbourList(listModel.neighbourList);
                    break;
            }
            emptyFlag = false;
            break;
        case '4':
            break;
    }
}
void App::runAlgorithms() {
    menu.algorithmMenu();
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();;
    auto diff = duration_cast<nanoseconds>(begin - end); // Różnica czasu między begin i end
    int startV;
    string algName;
    switch (menu.algorithmChoice) {
        case '1':
            algName = "Prime";
            matrixModel.convertToUndirectedMatrix(model.edgeList);
            listModel.convertToUndirectedList(model.edgeList);
            //Liczenie czasu dla algorytmu Prime i macierzy incydencji
            begin = std::chrono::steady_clock::now();
            matrixAlgorithm.primMatrix(matrixModel.undirectedIncMatrix, matrixModel.weights, matrixModel.v,
                                       matrixModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            matrixDurTime = (double)diff.count() / 1000000;
            //Liczenie czasu dla algorytmu Prime i listy sąsiedztwa
            begin = std::chrono::steady_clock::now();
            listAlgorithm.primList(listModel.undirectedNList, listModel.v);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            listDurTime = (double)diff.count() / 1000000;
            break;
        case '2':
            algName = "Kruskala";
            //Liczenie czasu dla algorytmu Kruskala i macierzy incydencji
            begin = std::chrono::steady_clock::now();
            matrixAlgorithm.kruskalMatrix(matrixModel.incidientMatrix, matrixModel.weights, matrixModel.v,
                                          matrixModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            matrixDurTime = (double)diff.count() / 1000000;
            //Liczenie czasu dla algorytmu Kruskala i listy sąsiedztwa

            begin = std::chrono::steady_clock::now();
            listAlgorithm.kruskalList(listModel.neighbourList, listModel.v, listModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            listDurTime = (double)diff.count() / 1000000;
            break;
        case '3':
            algName = "Dijkstry";
            startV = menu.inputStart(model.v);
            //Liczenie czasu dla algorytmu Dijkstry i macierzy incydencji
            begin = std::chrono::steady_clock::now();
            matrixAlgorithm.dijkstraMatrix(matrixModel.incidientMatrix, matrixModel.weights, startV, matrixModel.v,
                                           matrixModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            matrixDurTime = (double)diff.count() / 1000000;
            //Liczenie czasu dla algorytmu Dijkstry i listy sąsiedztwa
            begin = std::chrono::steady_clock::now();
            listAlgorithm.dijkstraList(listModel.neighbourList, startV, listModel.v, listModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            listDurTime = (double)diff.count() / 1000000;
            break;
        case '4':
            algName = "Bellmana-Forda";
            startV = menu.inputStart(model.v);
            //Liczenie czasu dla algorytmu Bellmana-Forda i macierzy incydencji
            begin = std::chrono::steady_clock::now();
            matrixAlgorithm.bellmanFordMatrix(matrixModel.incidientMatrix, matrixModel.weights, startV, matrixModel.v,
                                              matrixModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            matrixDurTime = (double)diff.count() / 1000000;
            //Liczenie czasu dla algorytmu Bellmana-Forda i listy sąsiedztwa
            begin = std::chrono::steady_clock::now();
            listAlgorithm.bellmanFordList(listModel.neighbourList, startV, listModel.v, listModel.e);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<nanoseconds>(end - begin);
            listDurTime = (double)diff.count() / 1000000;
            break;
        default:
            cout << "Error";
            break;

    }
    cout << "Czas dzialania algorytmu " << algName << " to:" << endl;
    cout << "Dla macierzy incydencji: " << matrixDurTime << " [ms]" << endl;
    cout << "Dla listy sasiedztwa: " << listDurTime << " [ms]" << endl;
}

void App::runTest() {
    menu.graphMenu();   //Wybierz reprezentacje grafu do testowania
    menu.algorithmMenu(); //Wybierz algorytm do testowania
    numberOfTests = menu.inputNumberOfTests();  //Podaj ilość testów na daną partię danych w tablicy
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto diff = duration_cast<nanoseconds>(begin - end);
    int arrLens[7] = {20,40,60,80,100,120,140}; //7 ilości wierzchołków do testowania
    double *sortTimeResults = new double[7];    //Tablica, która przetrzymuje średnie wyniki czasu sortowania z każdej partii danych
    int density = menu.inputDensity();  //Podawanie gęstości grafu w % (0-100)

    srand(time(NULL));
    string algName;
    int startV;
    for (int i = 0; i < 7; i++) {    //Pętla do wykonywania testów na kolejnych długościach tablic danych do sortowania
        model.v = listModel.v = matrixModel.v = arrLens[i];       //Bierzemy po kolei ilości wierzchołków do testowania z arrLens
        model.e = listModel.e = matrixModel.e = model.calculateEdges(density); //Obliczanie ilości krawędzi na podstawie podanej gęstości grafu
        double totalDurTime = 0;        //Zmienna do sumowania wyników testów, służy do obliczenia średniej
        double avgDurTime = 0;          //Wierzchołek startowy dla aglorytmów Dijkstry i Bellmana-Forda
        for (int j = 0; j < numberOfTests; j++) {     //Petla do wykonywania testów
            model.generateGraph("test");      //Generowanie losowego grafu w postaci listy krawędzi

            switch (menu.graphChoice) {
                //Algorytmy dla macierzy incydencji
                case '1':
                    matrixModel.loadMatrix(
                            model.edgeList);        //Tworzenie macierzy incydencji z wygenerowanej listy krawędzi
                    switch (menu.algorithmChoice) {
                        case '1':       //Algorytm Prime
                            algName = "Prime";
                            matrixModel.convertToUndirectedMatrix(model.edgeList);
                            //listModel.convertToUndirectedList(model.edgeList);
                            begin = std::chrono::steady_clock::now();
                            matrixAlgorithm.primMatrix(matrixModel.undirectedIncMatrix,matrixModel.weights,matrixModel.v,matrixModel.e, "test");
                            //listAlgorithm.primList(listModel.undirectedNList,listModel.v,"test");
                            end = std::chrono::steady_clock::now();
                            diff = duration_cast<nanoseconds>(end - begin);
                            totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                            break;
                        case '2':       //Algorytm Kruskala
                            algName = "Kruskala";
                            begin = std::chrono::steady_clock::now();
                            matrixAlgorithm.kruskalMatrix(matrixModel.incidientMatrix,matrixModel.weights,matrixModel.v,matrixModel.e,"test");
                            end = std::chrono::steady_clock::now();
                            diff = duration_cast<nanoseconds>(end - begin);
                            totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                            break;
                        case '3':       //Algorytm Dijkstry
                            algName = "Dijkstry";
                            startV = rand() % matrixModel.v;
                            begin = std::chrono::steady_clock::now();
                            matrixAlgorithm.dijkstraMatrix(matrixModel.incidientMatrix,matrixModel.weights,startV,matrixModel.v,matrixModel.e,"test");
                            end = std::chrono::steady_clock::now();
                            diff = duration_cast<nanoseconds>(end - begin);
                            totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                            break;
                        case '4':
                            algName = "Bellmana-Forda";
                            startV = rand() % matrixModel.v;
                            begin = std::chrono::steady_clock::now();
                            matrixAlgorithm.bellmanFordMatrix(matrixModel.incidientMatrix,matrixModel.weights,startV,matrixModel.v,matrixModel.e,"test");
                            end = std::chrono::steady_clock::now();
                            diff = duration_cast<nanoseconds>(end - begin);
                            totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                            break;
                        default:
                            cout << "error" << endl;
                    }
                    matrixModel.freeMatrix();
                    break;

                //Algorytmy dla Listy sąsiedztwa
                case '2':
                    listModel.loadNeighbourList(model.edgeList);    //Tworzenie listy sąsiedztwa z wygenerowanej listy krawędzi
                        switch (menu.algorithmChoice) {
                            case '1':       //Algorytm Prime
                                algName = "Prime";
                                listModel.convertToUndirectedList(model.edgeList);
                                begin = std::chrono::steady_clock::now();
                                listAlgorithm.primList(listModel.undirectedNList,listModel.v,"test");
                                end = std::chrono::steady_clock::now();
                                diff = duration_cast<nanoseconds>(end - begin);
                                totalDurTime += (double)diff.count() /1000000;       //Dodaj czas testu do sumy wszystkich testów
                                break;
                            case '2':       //Algorytm Kruskala
                                algName = "Kruskala";
                                begin = std::chrono::steady_clock::now();
                                listAlgorithm.kruskalList(listModel.neighbourList,listModel.v,listModel.e,"test");
                                end = std::chrono::steady_clock::now();
                                diff = duration_cast<nanoseconds>(end - begin);
                                totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                                break;
                            case '3':       //Algorytm Dijkstry
                                algName = "Dijkstry";
                                startV = rand() % matrixModel.v;
                                begin = std::chrono::steady_clock::now();
                                listAlgorithm.dijkstraList(listModel.neighbourList,startV,listModel.v,listModel.e,"test");
                                end = std::chrono::steady_clock::now();
                                diff = duration_cast<nanoseconds>(end - begin);
                                totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                                break;
                            case '4':
                                algName = "Bellmana-Forda";
                                startV = rand() % matrixModel.v;
                                begin = std::chrono::steady_clock::now();
                                listAlgorithm.bellmanFordList(listModel.neighbourList,startV,listModel.v,listModel.e,"test");
                                end = std::chrono::steady_clock::now();
                                diff = duration_cast<nanoseconds>(end - begin);
                                totalDurTime += (double)diff.count() / 1000000;       //Dodaj czas testu do sumy wszystkich testów
                                break;
                        }
                        listModel.freeNeighbourList();
            }
            cout << "Test" << j << "wykonany ";
            cout << " w czasie  " << (double)diff.count() / 1000000 << "[ms]" << endl;    //Informacja o czasie algorytmu dla danego testu
            model.freeEdgeList();   //Zwolnij pamięć dynamicznej listy krawędzi
        }
        avgDurTime = totalDurTime / numberOfTests;  //Obliczanie średniej z czasów algorytmu wszytkich testow dla danej ilości wierzchołków
        cout << "Ilosc wierzcholkow: " << model.v << " | Gestosc grafu: " <<  density << "%" << endl;
        cout <<  "Sredni czas algorytmu " << algName <<" to: " <<avgDurTime << " [ms]" << endl << endl;
        sortTimeResults[i] = avgDurTime;

    }
    cout << "------- Podsumowanie -------" << endl << "Gestosc grafu: " << density << "%" << endl;     //Wyświetlanie podusmowania zawierającego średnie czasy sortowania dla wszystkich długości
    for (int i = 0; i < 7; i ++){
        cout << "Sredni czas algorytmu dla " << arrLens[i] << " wierzcholkow to " << sortTimeResults[i] << " [ms]" << endl;
    }
    cout << endl;
}

void App::run() {
    while (true) {
        runGraphPrep();
        if (menu.listChoice == '4')
            runTest();
        else
            runAlgorithms();

        menu.exitRepeatMenu();
        if (menu.exitRepeatChoice == '2')
            return;
        emptyFlag = false;
    }
}

