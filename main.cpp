#include <iostream>

#include <QApplication>

#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/Variable.h"

#include "view/graph3dview.h"
#include "model/fenetre/fenetre.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenetrePrincipale w;
    w.show();

    Constante c1(2);
    auto v1 = Variable::construct('x',0);

    Constante c2(3);
    auto v2 = Variable::construct('y',0);

    Multiplication m1(&c1, v1);

    Multiplication m2(&c2, v2);

    Addition a1(&m1, &m2);

    Graph3DView view;
    view.show();
    view.setExpression(&a1);

    return QApplication::exec();
}
