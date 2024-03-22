//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Multiplication.h"
#include "../../constante/Constante.h"
#include <iostream>

void Multiplication::afficherNC() {
    get_ed()->afficherNC();
    std::cout << " * ";
    get_eg()->afficherNC();
    std::cout << "\n";
}

void Multiplication::afficherNPI() {
    get_ed()->afficherNPI();
    std::cout << " ";
    get_eg()->afficherNPI();
    std::cout << " * ";
}

float Multiplication::calculer() {
    return get_ed()->calculer() * get_eg()->calculer();
}

Expression *Multiplication::simplifier() {
    const float result = calculer();
    return new Constante(result);
}
