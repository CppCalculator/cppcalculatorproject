#include <sstream>
#include "Console.h"

Console::~Console() {
    clearExpressions();
}

void Console::run() {
    std::string line;
    std::cout << "Enter your expression in reverse Polish notation. Enter 'p' to process." << std::endl;

    while (true) {
        std::getline(std::cin, line);
        if (line == "p") {

            if (expressions.size() == 1) {
                Expression* result = expressions.top();
                expressions.pop();
                std::cout << "The result is: " << result->calculer() << std::endl;
                delete result;
            } else {
                std::cerr << "Error: Invalid expression. Please check the input." << std::endl;
            }
            break;
        } else {

            std::istringstream iss(line);
            std::string token;
            while (iss >> token) {
                processToken(token);
            }
        }
    }
    clearExpressions();
}


void Console::processToken(const std::string& token) {

    if (token == "p"){
        return;
    }
    // Vérifier si le token est un nombre (possiblement négatif)
    if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
        expressions.push(new Constante(std::stof(token)));
    }
        // Vérifier si le token est une variable (assumer que les variables sont de simples lettres pour la simplicité)
    else if (isalpha(token[0]) && token.size() == 1) {  // Supposer que les noms de variables sont de simples caractères pour l'instant
        Variable* var = Variable::construct(token[0]);
        if (var != nullptr) {
            expressions.push(var);
        } else {
            std::cerr << "Undefined variable: " << token << std::endl;
        }
    }
    else if (token.size() == 1) {
        // Gestion des opérateurs comme auparavant
        if (expressions.size() < 2) {
            std::cerr << "Error: Not enough operands for the operation." << std::endl;
            return;
        }
        Expression* left = expressions.top(); expressions.pop();
        Expression* right = expressions.top(); expressions.pop();

        Operation* operation = nullptr;
        switch (token[0]) {
            case '+': operation = new Addition(left, right); break;
            case '-': operation = new Soustraction(left, right); break;
            case '*': operation = new Multiplication(left, right); break;
            case '/': operation = new Division(left, right); break;
            default:
                std::cerr << "Error: Invalid operation." << std::endl;
                return;
        }
        expressions.push(operation);
    }
    else {
        std::cerr << "Error: Invalid input '" << token << "'." << std::endl;
    }
}

void Console::clearExpressions() {
    while (!expressions.empty()) {
        delete expressions.top();
        expressions.pop();
    }
}
