#include <QApplication>


#include "model/console/Console.h"
#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/variable/Variable.h"
#include "model/operations/puissance/Puissance.h"

#include "view/graph3dview.h"
#include "model/fenetre/fenetre.h"

#include "model/utils/data.h"
#include "model/operationsUnaire/carre/Carre.h"

int main(int argc, char *argv[])
{

    Constante c1(8);
    auto v1 = Variable::construct('x',0);

    Constante c2(0);
    auto v2 = Variable::construct('y',2);
    auto exp = new Carre(v1);

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
    Addition a1(&m1, exp);
    a1.afficherNC();
    std::cout << "\n";
    a1.afficherNPI();
    std::cout << "\n";
    //gp2 :
    std::string n_fichier = "expressions.txt";
    a1.sauvegardeASCII(n_fichier);
    m1.sauvegardeASCII(n_fichier);

    //use the Singleton data class for the expression
    Data &data = Data::getInstance();
    data.updateExpression(&a1);

    QApplication a(argc, argv);
    FenetrePrincipale w;
    w.show();

    bool runConsole = false;
    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "console") {
            runConsole = true;
            break;
        }
    }

    if (runConsole) {
        Console console;
        console.run();
    }

    return QApplication::exec();
}
