// console.h

#include <iostream>
#include <stack>
#include <string>
#include "../operations/Operation.h"
#include "../constante/Constante.h"
#include "../operations/addition/Addition.h"
#include "../operations/soustraction/Soustraction.h"
#include "../operations/multiplication/Multiplication.h"
#include "../operations/division/Division.h"
#include "../expression/Expression.h"

class Console {
public:
    Console() = default;
    ~Console();
    void run();

private:
    std::stack<Expression*> expressions;
    void processToken(const std::string& token);
    void clearExpressions();
};
