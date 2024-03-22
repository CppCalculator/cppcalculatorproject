//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Constante.h"

#include <iostream>
#include <memory>

void Constante::afficherNC() {
    std::cout << m_valeur;
}

void Constante::afficherNPI() {
    std::cout << m_valeur << " ";
}

float Constante::calculer() {
    return m_valeur;
}

Expression *Constante::simplifier() {
    return new Constante(m_valeur);
}
