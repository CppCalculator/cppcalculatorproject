//
// Created by antho on 23/03/2024.
//

#include "Racine.h"

#include <iostream>
#include <cmath>

using namespace std;

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