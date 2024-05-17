//
// Created by antho on 23/03/2024.
//

#include "Puissance.h"

#include <iostream>
#include <cmath>

using namespace std;

void Puissance::afficherNC() {
    get_eg()->afficherNC();
    cout << "^" ;
    get_ed()->afficherNC();
}

void Puissance::afficherNPI() {
    get_eg()->afficherNC();
    cout << "^" ;
    get_ed()->afficherNC();
}

float Puissance::calculer() {
    return pow(get_eg()->calculer(), get_ed()->calculer());
}