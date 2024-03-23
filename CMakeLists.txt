cmake_minimum_required(VERSION 3.28)
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
        model/operations/soustraction/Soustraction.h
        model/operations/puissance/Puissance.cpp
        model/operations/puissance/Puissance.h
        model/operationsUnaire/OperationUnaire.cpp
        model/operationsUnaire/OperationUnaire.h
        model/operationsUnaire/racine/Racine.cpp
        model/operationsUnaire/racine/Racine.h
        model/operationsUnaire/inverse/Inverse.cpp
        model/operationsUnaire/inverse/Inverse.h
        model/operationsUnaire/oppose/Oppose.cpp
        model/operationsUnaire/oppose/Oppose.h
        model/operationsUnaire/absolue/Absolue.cpp
        model/operationsUnaire/absolue/Absolue.h
        model/operationsUnaire/logNeperien/Ln.cpp
        model/operationsUnaire/logNeperien/Ln.h
        model/operationsUnaire/carre/Carre.cpp
        model/operationsUnaire/carre/Carre.h)
