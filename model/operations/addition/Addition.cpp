//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Addition.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

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


void Addition::afficherNPI(std::ostream& os) const {
    get_eg()->afficherNPI(os);
    os << " ";
    get_ed()->afficherNPI(os);
    os << " +";
}

float Addition::calculer() {
    return get_eg()->calculer() + get_ed()->calculer();
}

void Addition::sauvegardeASCII(const std::string& n_fichier) {
    std::ofstream fichier(n_fichier);
    if (fichier) {
        afficherNPI(fichier); // Appel de la méthode afficherNPI de l'expression
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
    }
}
