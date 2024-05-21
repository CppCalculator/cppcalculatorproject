//
// Created by antho on 23/03/2024.
//

#include "Inverse.h"

#include <iostream>
#include "../../constante/Constante.h"
#include <iostream>
#include <ostream>
#include <string>

void Inverse::afficherNC(std::ostream& os) const {
    os << "1 / ";
    get_e()->afficherNC(os);
    os << " ";
}

void Inverse::afficherNPI(std::ostream& os) const {
    os << "1 ";
    get_e()->afficherNPI(os);
    os << " / ";
}

Expression *Inverse::simplifier() {
}

void Inverse::sauvegardeASCII(const std::string& n_fichier) {
}
using namespace std;

void Inverse::afficherNC(){
    cout << "1 / ";
    get_e()->afficherNC();
    cout << " ";
}

void Inverse::afficherNPI(){
    cout << "1 ";
    get_e()->afficherNPI();
    cout << " / ";
}

float Inverse::calculer(){
    return 1 / get_e()->calculer();
}
