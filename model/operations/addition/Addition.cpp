//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Addition.h"
#include "../../constante/Constante.h"

#include <fstream>
#include <iostream>
#include <memory>
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

float Addition::calculer() {
    return get_eg()->calculer() + get_ed()->calculer();
}

void Addition::afficherNPI(std::ostream& os) const {
    get_eg()->afficherNPI(os);
    os << " ";
    get_ed()->afficherNPI(os);
    os << " +";
}

Expression *Addition::simplifier() {
    const float result = calculer();
    return new Constante(result);
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
