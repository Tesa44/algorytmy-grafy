cmake_minimum_required(VERSION 3.27)
project(graphApp_v3)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphApp_v3 main.cpp
        Menu.cpp
        Menu.h
        Models/Model.cpp
        Models/Model.h
        App.cpp
        App.h
        Algorithms/Algorithm.cpp
        Algorithms/Algorithm.h
        Algorithms/Queue.cpp
        Algorithms/Queue.h
        Algorithms/MatrixAlgorithm.cpp
        Algorithms/MatrixAlgorithm.h
        Algorithms/ListAlgorithm.cpp
        Algorithms/ListAlgorithm.h
        Models/MatrixModel.cpp
        Models/MatrixModel.h
        Models/ListModel.cpp
        Models/ListModel.h)
