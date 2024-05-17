cmake_minimum_required(VERSION 3.5)

project(QTProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        model/operations/addition/Addition.cpp
        model/operations/addition/Addition.h
        model/operations/division/Division.cpp
        model/operations/division/Division.h
        model/operations/multiplication/Multiplication.cpp
        model/operations/multiplication/Multiplication.h
        model/operations/soustraction/Soustraction.cpp
        model/operations/soustraction/Soustraction.h
        model/operations/Operation.cpp
        model/operations/Operation.h
        model/constante/Constante.cpp
        model/constante/Constante.h
        model/expression/Expression.cpp
        model/expression/Expression.h
        model/variable/Variable.cpp
        model/variable/Variable.h
        view/graph3dview.h view/graph3dview.cpp
        controller/graph3dcontroller.h controller/graph3dcontroller.cpp
        model/fenetre/fenetre.h model/fenetre/fenetre.cpp
        view/button.cpp view/button.h
        view/calculator.cpp view/calculator.h
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
        model/operationsUnaire/carre/Carre.h
        controller/graph2dcontroller.h controller/graph2dcontroller.cpp
        view/graph2dview.h view/graph2dview.cpp
        model/console/Console.cpp
        model/console/Console.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QTProject
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(QTProject SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(QTProject
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QTProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QTProject)
endif()

set_target_properties(QTProject PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS QTProject
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QTProject)
endif()

if(WIN32)
    set_target_properties(QTProject PROPERTIES LINK_FLAGS "-mconsole")
endif()
