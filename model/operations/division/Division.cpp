//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Division.h"
#include "../../constante/Constante.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

void Division::afficherNC() {
    get_ed()->afficherNC();
    std::cout << " / ";
    get_eg()->afficherNC();
    std::cout << "";
}

void Division::afficherNC(std::ostream& os) const {
    os << "(";
    get_eg()->afficherNC(os);
    os << "/";
    get_ed()->afficherNC(os);
    os << ")";
}

void Division::afficherNPI() {
    get_ed()->afficherNPI();
    std::cout << " ";
    get_eg()->afficherNPI();
    std::cout << " / ";
}

void Division::afficherNPI(std::ostream& os) const {
    get_eg()->afficherNPI(os);
    os << " ";
    get_ed()->afficherNPI(os);
    os << " /";
}

float Division::calculer() {
    return get_ed()->calculer() / get_eg()->calculer();
}

Expression *Division::simplifier() {
    Expression* gauche = get_eg()->simplifier();
    Expression* droite = get_ed()->simplifier();
    auto* constGauche = dynamic_cast<Constante*>(gauche);
    auto* constDroite = dynamic_cast<Constante*>(droite);

    if (constGauche && constDroite) {
        delete gauche; delete droite;
        return new Constante(calculer());
    }
    return new Division(droite->simplifier(), gauche->simplifier());
}
void Division::sauvegardeASCII(const std::string& n_fichier) {
    std::ofstream fichier(n_fichier);
    if (fichier) {
   afficherNPI(fichier); // Appel de la méthode afficherNPI de l'expression
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
    }
}
