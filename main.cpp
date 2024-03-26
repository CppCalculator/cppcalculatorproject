#include <iostream>

#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/Variable.h"
#include "view/Graph3D.h"

int main()
{
    /*Constante c1(5);
    Constante c2(3);
    Addition a1(&c1, &c2);*/

    // Instanciation de la variable x
    Constante c1(2);
    auto v1 = Variable::construct('x');

    Constante c2(3);
    auto v2 = Variable::construct('y');

    Multiplication m1(&c1, v1);

    Multiplication m2(&c2, v2);

    Addition a1(&m1, &m2);

    a1.afficherNPI();
    std::cout << "\n";
    Graph3D b(0, nullptr, &a1);

    // Libération de la memoire
    // À faire obligatoirement pour éviter les fuites de mémoire
    delete v1;
    delete v2;

    return 0;
}
