#include <iostream>

#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/Variable.h"

int main()
{
    Constante c1(5);
    Constante c2(3);
    Addition a1(&c1, &c2);

    // Instanciation de la variable x
    auto v1 = Variable::construct('x');

    //Constante c3(2);
    Multiplication a2(&a1, v1);
    a2.afficherNC();
    a2.afficherNPI();
    Constante r2 (a2.calculer());
    std::cout << "\n";
    r2.afficherNPI();

    // Libération de la memoire
    // À faire obligatoirement pour éviter les fuites de mémoire
    delete v1;

    return 0;
}
