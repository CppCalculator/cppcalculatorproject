cmake_minimum_required(VERSION 3.27)
project(Projet)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projet main.cpp
        model/operations/addition/Addition.cpp
        model/operations/addition/Addition.h
        model/operations/division/Division.cpp
        model/operations/division/Division.h
        model/operations/multiplication/Multiplication.cpp
        model/operations/multiplication/Multiplication.h
        model/operations/Operation.cpp
        model/operations/Operation.h
        model/constante/Constante.cpp
        model/constante/Constante.h
        model/expression/Expression.cpp
        model/expression/Expression.h
        model/operations/soustraction/Soustraction.cpp
        model/operations/soustraction/Soustraction.h)
