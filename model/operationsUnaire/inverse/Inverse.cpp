//
// Created by antho on 23/03/2024.
//

#include "Inverse.h"

#include <iostream>

using namespace std;

void Inverse::afficherNC(){
    cout << "1 / ";
    get_e()->afficherNPI();
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