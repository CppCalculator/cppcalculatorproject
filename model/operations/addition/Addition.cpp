//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Addition.h"
#include "../../constante/Constante.h"
#include "../../variable/Variable.h"

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
    std::cout << ")";
}

void Addition::afficherNC(std::ostream& os) const {
    os << "(";
    get_eg()->afficherNC(os);
    os << " +";
    get_ed()->afficherNC(os);
    os << ")";
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
    Expression* gauche = get_eg()->simplifier();
    Expression* droite = get_ed()->simplifier();
    auto* constGauche = dynamic_cast<Constante*>(gauche);
    auto* constDroite = dynamic_cast<Constante*>(droite);

    if (constGauche && constDroite) {
        delete gauche; delete droite;
        return new Constante(calculer());
    }
    return new Addition(gauche->simplifier(), droite->simplifier());
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
