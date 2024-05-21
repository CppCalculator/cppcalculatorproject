//
// Created by antho on 23/03/2024.
//

#include "Carre.h"

#include <iostream>

using namespace std;
#include "../../constante/Constante.h"
#include <iostream>
#include <ostream>
#include <string>

void Carre::afficherNPI(std::ostream& os) const {
}

Expression *Carre::simplifier() {
}

void Carre::sauvegardeASCII(const std::string& n_fichier) {
}


void Carre::afficherNC(){
    get_e()->afficherNC();
    cout << "^2" ;
}

void Carre::afficherNPI(){
    get_e()->afficherNC();
    cout << "^2" ;
}

float Carre::calculer() {
    return get_e()->calculer() * get_e()->calculer();
}