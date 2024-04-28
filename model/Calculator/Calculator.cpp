#include "Calculator.h"

Calculator::~Calculator() {
    clearExpressions();
}

void Calculator::run() {
    std::string input;
    std::cout << "Enter your expression in reverse Polish notation. Enter 'p' to process." << std::endl;

    while (std::cin >> input && input != "p") {
        processToken(input);
    }

    if (expressions.size() == 1) {
        Expression* result = expressions.top();
        expressions.pop();
        std::cout << "The result is: " << result->calculer() << std::endl;
        delete result;
    } else {
        std::cerr << "Error: Invalid expression." << std::endl;
    }

    clearExpressions();
}

void Calculator::processToken(const std::string& token) {
    if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
        expressions.push(new Constante(std::stof(token)));
    } else if (token.size() == 1) {
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
}

void Calculator::clearExpressions() {
    while (!expressions.empty()) {
        delete expressions.top();
        expressions.pop();
    }
}
