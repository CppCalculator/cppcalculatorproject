//
// Created by antho on 23/03/2024.
//

#include "Puissance.h"
#include "../../constante/Constante.h"

#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <memory>
#include <fstream>


using namespace std;

void Puissance::afficherNC() {
    get_eg()->afficherNC();
    cout << "^" ;
    get_ed()->afficherNC();
}

void Puissance::afficherNPI() {
    get_eg()->afficherNC();
    cout << "^" ;
    get_ed()->afficherNC();
}

float Puissance::calculer() {
    return pow(get_eg()->calculer(), get_ed()->calculer());
}

Expression *Puissance::simplifier() {
    const float result = calculer();
    return new Constante(result);
}


void Puissance::sauvegardeASCII(const std::string& n_fichier) {
    std::ofstream fichier(n_fichier);
    if (fichier) {
        afficherNPI(fichier); // Appel de la méthode afficherNPI de l'expression
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
    }
}

void Puissance::afficherNPI(std::ostream& os) const {
    get_eg()->afficherNPI(os);
    os << " ";
    get_ed()->afficherNPI(os);
    os << " +";
}