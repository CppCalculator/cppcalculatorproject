//
// Created by antho on 23/03/2024.
//

#include "Ln.h"

#include <iostream>
#include <cmath>
#include "../../constante/Constante.h"
#include <iostream>
#include <ostream>
#include <string>

void Ln::afficherNC(std::ostream& os) const {
    os << "ln(";
    get_e()->afficherNC(os);
    os << ") ";
}

void Ln::afficherNPI(std::ostream& os) const {
    get_e()->afficherNPI(os);
    os << " LN ";
}

Expression *Ln::simplifier() {
}

void Ln::sauvegardeASCII(const std::string& n_fichier) {
}
using namespace std;

void Ln::afficherNC() {
    cout << "ln(";
    get_e()->afficherNC();
    cout << ") ";
}

void Ln::afficherNPI() {
    get_e()->afficherNPI();
    cout << " LN ";
}

float Ln::calculer() {
    return log(get_e()->calculer());
}
