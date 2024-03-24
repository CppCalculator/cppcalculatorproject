//
// Created by Sofia Boldeskul on 23.03.2024.
//

#include "SymbolTable.h"

void SymbolTable::setValue(const std::string &name, float value) {
    variables[name] = value;
}

bool SymbolTable::getValue(const std::string &name, float &value) const {
    auto it = variables.find(name);
    if (it != variables.end()){
        value = it -> second;
        return true;
    }
    return false;
}