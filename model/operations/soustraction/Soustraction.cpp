//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Soustraction.h"

#include <iostream>

void Soustraction::afficherNC() {
    std::cout << "(";
    get_ed()->afficherNC();
    std::cout << " - ";
    get_eg()->afficherNC();
    std::cout << ")\n";
}

void Soustraction::afficherNPI() {
    get_ed()->afficherNPI();
    std::cout << " ";
    get_eg()->afficherNPI();
    std::cout << " - ";
}

float Soustraction::calculer() {
    return get_ed()->calculer() - get_eg()->calculer();
}
