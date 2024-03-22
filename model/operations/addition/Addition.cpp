//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Addition.h"
#include "../../constante/Constante.h"

#include <iostream>
#include <memory>

void Addition::afficherNC() {
    std::cout << "(";
    get_eg()->afficherNC();
    std::cout << " + ";
    get_ed()->afficherNC();
    std::cout << ")\n";
}

void Addition::afficherNPI() {
    get_eg()->afficherNPI();
    std::cout << " ";
    get_ed()->afficherNPI();
    std::cout << " + ";
}

float Addition::calculer() {
    return get_eg()->calculer() + get_ed()->calculer();
}

Expression *Addition::simplifier() {
    const float result = calculer();
    return new Constante(result);
}

