#include <iostream>
#include <QApplication>

#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "view/calculator.h"

int main(int argc, char *argv[])
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

    QApplication a(argc, argv);

    Calculator calculator;
    calculator.show();

    return QApplication::exec();
}
