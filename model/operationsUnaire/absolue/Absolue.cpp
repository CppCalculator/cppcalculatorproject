//
// Created by antho on 23/03/2024.
//

#include "Absolue.h"

#include <iostream>

using namespace std;

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