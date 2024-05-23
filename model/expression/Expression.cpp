//
// Created by mathias.mourgues on 22/03/2024.
//

#include "Expression.h"
#include <fstream>
#include <stack>
#include <string>
#include <memory>
#include <cctype>
#include <fstream>
#include <stack>
#include <string>
#include <stdexcept>
#include "../operations/addition/Addition.h"
#include "../operations//soustraction/Soustraction.h"
#include "../operations/multiplication/Multiplication.h"
#include "../constante/Constante.h"
#include "../operations/division/Division.h"
#include "../variable/Variable.h"
#include "../operations/puissance/Puissance.h"
#include "../operationsUnaire/carre/Carre.h"

Expression* Expression::load_expression(const std::string& chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour la lecture.");
    }

    std::stack<Expression*> pile;
    std::string token;

    while (fichier >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            pile.push(new Constante(std::stof(token)));
        } else {
            if (pile.size() < 2) {
                throw std::runtime_error("Expression mal formée dans le fichier.");
            }
            Expression* droite = pile.top(); pile.pop();
            Expression* gauche = pile.top(); pile.pop();

            if (token == "+") {
                pile.push(new Addition(gauche, droite));
            } else if (token == "-") {
                pile.push(new Soustraction(gauche, droite));
            } else if (token == "*") {
                pile.push(new Multiplication(gauche, droite));
            } else if (token == "/") {
                pile.push(new Division(gauche, droite));
            } else if (token == "x") {
                pile.push(Variable::construct('x'));
            } else if (token == "y") {
                pile.push(Variable::construct('y'));
            } else if (token == "^") {
                pile.push(new Puissance(gauche, droite));
            } else if (token ==  "^2") {
                pile.push(new Carre(gauche));
            }
        }
    }

    if (pile.size() != 1) {
        throw std::runtime_error("Erreur de format ou données incomplètes dans le fichier.");
    }

    Expression* resultat = pile.top();
    pile.pop();
    return resultat;
}

