//
// Created by antho on 23/03/2024.
//

#include "Ln.h"

#include <iostream>
#include <cmath>

using namespace std;

void Ln::afficherNC() {
    cout << "ln(";
    get_e()->afficherNPI();
    cout << ") ";
}

void Ln::afficherNPI() {
    get_e()->afficherNPI();
    cout << " LN ";
}

float Ln::calculer() {
    return log(get_e()->calculer());
}