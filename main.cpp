#include <iostream>

#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/SymbolTable.h"
#include "model/variable/Variable.h"
int main()
{
    Constante c1(5);
    Constante c2(3);
    Addition a1(&c1, &c2);
    Constante c3(2);
    Multiplication a2(&a1, &c3);
    a2.afficherNPI();
    Constante r2 (a2.calculer());
    std::cout << "\n" ;
    r2.afficherNPI();


    SymbolTable symbolTable;

    Variable x("x", symbolTable);
    Variable y("y", symbolTable);

    symbolTable.setValue("x", 10);
    symbolTable.setValue("y", 20);

    std::cout << "Initial values:" << std::endl;
    std::cout << "x = " << x.calculer() << std::endl;
    std::cout << "y = " << y.calculer() << std::endl;


    symbolTable.setValue("x", 15);
    symbolTable.setValue("y", 25);

    std::cout << "After modification:" << std::endl;
    std::cout << "x = " << x.calculer() << std::endl;
    std::cout << "y = " << y.calculer() << std::endl;
    return 0;
}
