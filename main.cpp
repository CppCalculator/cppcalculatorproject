<<<<<<< HEAD
#include <iostream>
=======
#include <QApplication>
#include <QLineSeries>
>>>>>>> 486ce0ab2543b47060300c5af550c93eb78db3ce

#include "model/console/Console.h"
#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/multiplication/Multiplication.h"
<<<<<<< HEAD
#include "model/operations/soustraction/Soustraction.h"
int main()
{
    const string n_fichier = "expressions.txt";
=======
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
>>>>>>> 486ce0ab2543b47060300c5af550c93eb78db3ce

    Constante c1(5);
    Constante c2(3);

    Addition a1(&c1, &c2);
    a1.afficherNPI();
    //a1.sauvegardeASCII( n_fichier);

    std::cout <<"\n";

    Soustraction s1(&c1, &c2);
    s1.afficherNPI();

    std::cout <<"\n";

    Constante c3(2);
    Multiplication m1(&a1, &c3);
    m1.afficherNPI();
    m1.sauvegardeASCII(n_fichier);

  //s1.sauvegardeASCII(n_fichier);
    Constante r2 (m1.calculer());

    std::cout << "\n" ;
    r2.afficherNPI();


<<<<<<< HEAD
    std::cout << "\n" ;
    Expression* loaded_expr = Expression::load_expression(n_fichier);
    std::cout << "Expression chargee: ";
    loaded_expr->afficherNPI();
    std::cout << "\nAffichage classique : " ;
    loaded_expr->afficherNC();
    std::cout << "Calcul de l'expression chargee: " << loaded_expr->calculer() << std::endl;

    delete loaded_expr;

    return 0;
=======
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
>>>>>>> 486ce0ab2543b47060300c5af550c93eb78db3ce
}
