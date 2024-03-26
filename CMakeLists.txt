cmake_minimum_required(VERSION 3.28)
project(Projet)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.2/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Qml
        Quick
        Charts
        DataVisualization
        Graphs
        REQUIRED)

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
        model/variable/Variable.cpp
        model/variable/Variable.h
        model/operations/soustraction/Soustraction.h
        view/Graph3D.cpp
        view/Graph3D.h)

target_link_libraries(Projet PUBLIC
        Qt::Charts
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::DataVisualization
        Qt::Graphs
)
