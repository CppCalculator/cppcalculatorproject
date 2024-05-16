#include <QApplication>
#include <QLineSeries>

#include "model/console/Console.h"
#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/Variable.h"

#include "view/graph3dview.h"
#include "model/fenetre/fenetre.h"

#include "view/calculator.h"
#include "view/graph2dview.h"
#include "controller/graph2dcontroller.h"
#include "model/utils/data.h"
#include "model/utils/ExampleSubscriber.h"

int main(int argc, char *argv[])
{
    /*
    Constante c1(3);
    Constante c2(4);
    Constante c3(2);
    auto v1 = Variable::construct('a', 3);
    auto v2 = Variable::construct('b', 2);

    Addition a1(&c1, &c2);
    Multiplication m1(&a1, &c3);
    Addition a2(&m1, v1);
    Division d1(&a2, v2);
    d1.simplifier()->afficherNC();
    */
    /*
    Constante c1(10);
    Constante c2(20);
    Constante c3(30);
    auto v1 = Variable::construct('x', 3);
    auto v2 = Variable::construct('y', 2);
    Addition a1(&c1, &c1);
    Addition a2(&a1, v1);
    Addition a3(&c2, &c2);
    Addition a4(&a3, v1);
    Addition a5(&a2, &a4);
    a5.simplifier()->afficherNC();
    */
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

    //gp2 :
    std::string n_fichier = "expressions.txt";
    a1.sauvegardeASCII(n_fichier);
    m1.sauvegardeASCII(n_fichier);


    Graph3DView view;
    view.show();
    view.setExpression(&a1);

    Calculator calculator;
    calculator.show();

    //gp5 test :
    Graph2dView view2;
    Graph2dController controller(&a1, v1, &view2);
    view2.show();
    view2.resize(800, 600);

    //use the Singleton data class for the expression
    Data &data = Data::getInstance();
    data.updateExpression(&a1);

    //with subscriber :
    ExampleSubscriber exampleSubscriber;
    data.updateExpression(&a1);

    int exec = QApplication::exec();

    //gp1 :
    Console console;
    console.run();

    return exec;
}
