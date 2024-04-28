#include <iostream>
#include <stack>
#include <string>
#include "model/expression/Expression.h"
#include "model/operations/Operation.h"
#include "model/constante/Constante.h"
#include "model/operations/addition/Addition.h"
#include "model/operations/soustraction/Soustraction.h"
#include "model/operations/multiplication/Multiplication.h"
#include "model/operations/division/Division.h"

int main() {
    std::stack<Expression*> expressions;
    std::string input;

    std::cout << "Enter your expression in reverse Polish notation. Enter 'p' to process." << std::endl;

    while (true) {
        std::cin >> input;

        if (input == "p") {
            break;
        } else if (isdigit(input[0]) || (input[0] == '-' && input.size() > 1 && isdigit(input[1]))) {

            expressions.push(new Constante(std::stof(input)));
        } else if (input.size() == 1) {
            char op = input[0];

            if (expressions.size() < 2) {
                std::cerr << "Error: Not enough operands for the operation." << std::endl;
                return 1;
            }
            Expression* left = expressions.top(); expressions.pop();
            Expression* right = expressions.top(); expressions.pop();

            Operation* operation;
            switch (op) {
                case '+': operation = new Addition(left, right); break;
                case '-': operation = new Soustraction(left, right); break;
                case '*': operation = new Multiplication(left, right); break;
                case '/': operation = new Division(left, right); break;
                default:
                    std::cerr << "Error: Invalid operation." << std::endl;
                    return 1;
            }
            expressions.push(operation);
        }
    }


    if (expressions.size() != 1) {
        std::cerr << "Error: Invalid expression." << std::endl;
        return 1;
    }

    Expression* result = expressions.top();
    expressions.pop();
    std::cout << "The result is: " << result->calculer() << std::endl;


    delete result;

    
    while (!expressions.empty()) {
        delete expressions.top();
        expressions.pop();
    }

    return 0;
}

