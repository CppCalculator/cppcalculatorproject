#include <iostream>

#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/operations/soustraction/Soustraction.h"
int main()
{
    string n_fichier = "expressions.txt";
    Constante c1(5);
    Constante c2(3);
    Addition a1(&c1, &c2);
    a1.afficherNPI();
    a1.sauvegardeASCII( n_fichier);
    std::cout <<"\n";
    Soustraction s1(&c1, &c2);
    s1.afficherNPI();
    std::cout <<"\n";
    Constante c3(2);
    Multiplication m1(&a1, &c3);
    m1.afficherNPI();
    m1.sauvegardeASCII(n_fichier);
  // s1.sauvegardeASCII(n_fichier);
    Constante r2 (m1.calculer());
    std::cout << "\n" ;
    r2.afficherNPI();

    return 0;
}
