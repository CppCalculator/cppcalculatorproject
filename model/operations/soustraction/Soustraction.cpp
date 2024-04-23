//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Soustraction.h"
#include <fstream>
#include <ostream>
#include <string>

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

void Soustraction::afficherNPI(std::ostream& os) const {
    get_ed()->afficherNPI(os);
    os << " ";
    get_eg()->afficherNPI(os);
    os << " - ";
}

float Soustraction::calculer() {
    return get_ed()->calculer() - get_eg()->calculer();
}

void Soustraction::sauvegardeASCII(const std::string& n_fichier) {
    std::ofstream fichier(n_fichier);
    if (fichier) {
        afficherNPI(fichier); // Appel de la méthode afficherNPI de l'expression
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
    }
}
