//
// Created by antho on 23/03/2024.
//

#include "Racine.h"

#include <iostream>
#include <cmath>

using namespace std;
#include "../../constante/Constante.h"
#include <iostream>
#include <ostream>
#include <string>

void Racine::afficherNPI(std::ostream& os) const {
}

Expression *Racine::simplifier() {
}

void Racine::sauvegardeASCII(const std::string& n_fichier) {
}
void Racine::afficherNC(){
    cout << "sqrt" ;
    get_e()->afficherNC();
}

void Racine::afficherNPI(){
    cout << "sqrt" ;
    get_e()->afficherNC();
}

float Racine::calculer() {
    return sqrt(get_e()->calculer());
}