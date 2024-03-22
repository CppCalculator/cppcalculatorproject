//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Division.h"
#include "../../constante/Constante.h"

#include <iostream>

void Division::afficherNC() {
    get_ed()->afficherNC();
    std::cout << " / ";
    get_eg()->afficherNC();
    std::cout << "\n";
}

void Division::afficherNPI() {
    get_ed()->afficherNPI();
    std::cout << " ";
    get_eg()->afficherNPI();
    std::cout << " / ";
}

float Division::calculer() {
    return get_ed()->calculer() / get_eg()->calculer();
}

Expression *Division::simplifier() {
    const float result = calculer();
    return new Constante(result);
}