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


    auto * view = new Graph3DView(nullptr, 512, 512);
    view->show();

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
