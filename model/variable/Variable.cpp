#include "Variable.h"
#include <iostream>

void Variable::afficherNC() {
    std::cout << m_name;
}

void Variable::afficherNPI() {
    std::cout << m_name << " ";
}

float Variable::calculer() {
    float value = 0.0;
    if (symbolTable.getValue(m_name, value)) {
        return value;
    }
    return 0.0;
}

Variable::Variable(const std::string& name, SymbolTable& symbolTable)
        : m_name(name), symbolTable(symbolTable) {
    float existingValue;
    if (!symbolTable.getValue(name, existingValue)) {
        symbolTable.setValue(name, 0.0);
    }
}
