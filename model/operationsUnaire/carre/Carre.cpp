//
// Created by antho on 23/03/2024.
//

#include "Carre.h"

#include <iostream>

using namespace std;

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