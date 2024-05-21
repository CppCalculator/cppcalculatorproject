//
// Created by antho on 23/03/2024.
//

#include "Oppose.h"

#include <iostream>
#include "../../constante/Constante.h"
#include <iostream>
#include <ostream>
#include <string>

void Oppose::afficherNC(std::ostream& os) const {
    os << "- ";
    get_e()->afficherNPI(os);
    os << " ";
}

void Oppose::afficherNPI(std::ostream& os) const {
    os << "- ";
    get_e()->afficherNPI(os);
    os << " ";
}

Expression *Oppose::simplifier() {
}

void Oppose::sauvegardeASCII(const std::string& n_fichier) {
}
using namespace std;

void Oppose::afficherNC(){
    cout << "- ";
    get_e()->afficherNPI();
    cout << " ";
}

void Oppose::afficherNPI(){
    cout << "- ";
    get_e()->afficherNPI();
    cout << " ";
}

float Oppose::calculer(){
    return -1 * get_e()->calculer();
}
