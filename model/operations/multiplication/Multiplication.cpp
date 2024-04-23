//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Multiplication.h"
#include <fstream>
#include <ostream>
#include <string>

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

void Multiplication::afficherNPI(std::ostream& os) const {
    get_ed()->afficherNPI(os);
    os << " ";
    get_eg()->afficherNPI(os);
    os << " * ";
}

float Multiplication::calculer() {
    return get_ed()->calculer() * get_eg()->calculer();
}

void Multiplication::sauvegardeASCII(const std::string& n_fichier) {
    std::ofstream fichier(n_fichier);
    if (fichier) {
       afficherNPI(fichier);
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
    }
}
