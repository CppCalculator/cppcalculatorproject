#include <QApplication>
#include <QLineSeries>

#include "model/console/Console.h"
#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/Variable.h"
#include "model/operations/puissance/Puissance.h"
#include "model/operationsUnaire/absolue/Absolue.h"
#include "model/operationsUnaire/carre/Carre.h"
#include "model/operationsUnaire/inverse/Inverse.h"
#include "model/operationsUnaire/logNeperien/Ln.h"
#include "model/operationsUnaire/oppose/Oppose.h"
#include "model/operationsUnaire/racine/Racine.h"

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

    Constante c1(8);
    auto v1 = Variable::construct('x',0);

    Constante c2(0);
    auto v2 = Variable::construct('y',2);

    Puissance p1(&c1,&c2);

    std::cout << "\n";
    std::cout << "\n";
    p1.calculer();
    p1.afficherNC();
    std::cout << "\n";
    std::cout << "\n";
    Multiplication m1(&c1, v1);
    m1.afficherNC();
    std::cout << "\n";
    m1.afficherNPI();
    std::cout << "\n";
    Multiplication m2(&c2, v2);
    m2.afficherNC();
    std::cout << "\n";
    m2.afficherNPI();
    std::cout << "\n";
    Addition a1(&m1, &m2);
    a1.afficherNC();
    std::cout << "\n";
    a1.afficherNPI();
    std::cout << "\n";
    //gp2 :
    std::string n_fichier = "expressions.txt";
    a1.sauvegardeASCII(n_fichier);
    m1.sauvegardeASCII(n_fichier);

    //gp9 test:
    Graph3DView view;
    view.show();
    view.setExpression(&a1);

    //gp4 test:
    /*
    Calculator calculator;
    calculator.show();
*/
    //gp5 test :
    //Graph2dView view2;
    //Graph2dController controller(&a1, v1, &view2);
    //view2.show();
    //view2.resize(800, 600);

    //use the Singleton data class for the expression
    Data &data = Data::getInstance();
    data.updateExpression(&a1);

    //with subscriber :
    //ExampleSubscriber exampleSubscriber;
    //data.updateExpression(&a1);

    int exec = QApplication::exec();

    //gp1 test:
    /*
    Console console;
    console.run();
*/

    return exec;
}
