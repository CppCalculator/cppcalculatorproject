//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Constante.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <memory>

void Constante::afficherNC() {
    std::cout << m_valeur;
}

void Constante::afficherNC(std::ostream& flux) const {
    flux << m_valeur;
}

void Constante::afficherNPI() {
    std::cout << m_valeur << " ";
}

void Constante::afficherNPI(std::ostream& flux) const {
    flux << m_valeur;
}

float Constante::calculer() {
    return m_valeur;
}

Expression *Constante::simplifier() {
    return new Constante(m_valeur);
}


void Constante::sauvegardeASCII( const std::string& n_fichier) {
    std::ofstream fichier(n_fichier);
    if (fichier) {
       afficherNPI(fichier);
        fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
    }
}

