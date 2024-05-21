//
// Created by antho on 23/03/2024.
//

#include "Absolue.h"
using namespace std;
#include "../../constante/Constante.h"
#include <iostream>
#include <ostream>
#include <string>

void Absolue::afficherNPI(std::ostream& os) const {
}

Expression *Absolue::simplifier() {
}

void Absolue::sauvegardeASCII(const std::string& n_fichier) {
}


void Absolue::afficherNC() {
    cout << "|";
    get_e()->afficherNPI();
    cout << "| ";
}

void Absolue::afficherNPI() {
    get_e()->afficherNPI();
    cout << " ABS ";
}

float Absolue::calculer() {
    return abs(get_e()->calculer());
}

