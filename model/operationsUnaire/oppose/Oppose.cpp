//
// Created by antho on 23/03/2024.
//

#include "Oppose.h"

#include <iostream>

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