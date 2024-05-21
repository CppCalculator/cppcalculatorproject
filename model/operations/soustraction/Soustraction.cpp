//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Soustraction.h"
#include "../../constante/Constante.h"
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

void Soustraction::afficherNC(std::ostream& os) const {
    os << "(";
    get_eg()->afficherNC(os);
    os << "-";
    get_ed()->afficherNC(os);
    os << ")\n";
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
    return get_eg()->calculer() - get_ed()->calculer();
}


Expression *Soustraction::simplifier() {
    Expression* gauche = get_eg()->simplifier();
    Expression* droite = get_ed()->simplifier();
    auto* constGauche = dynamic_cast<Constante*>(gauche);
    auto* constDroite = dynamic_cast<Constante*>(droite);

    if (constGauche && constDroite) {
        delete gauche; delete droite;
        return new Constante(calculer());
    }
    return new Soustraction(gauche->simplifier(), droite->simplifier());
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
