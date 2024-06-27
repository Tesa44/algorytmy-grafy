//
// Created by Mateusz on 03.06.2024.
//

#ifndef GRAPHAPP_V3_LISTALGORITHM_H
#define GRAPHAPP_V3_LISTALGORITHM_H
#include "../Models/Model.h"
#include "../Models/ListModel.h"
#include "Algorithm.h"

class ListAlgorithm : public Algorithm{
public:
    void primList(ListModel::listS **neighbourList, int v,string mode = "default");
    void kruskalList(ListModel::listS **neighbourList,int v, int e,string mode = "default");
    void dijkstraList(ListModel::listS **neighbourList, int s, int v, int e,string mode = "default");
    void bellmanFordList(ListModel::listS **neighbourList, int s, int v, int e,string mode = "default");
};


#endif //GRAPHAPP_V3_LISTALGORITHM_H
