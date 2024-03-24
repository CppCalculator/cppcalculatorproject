//
// Created by Sofia Boldeskul on 23.03.2024.
//
#include <iostream>
#include <string>
#include <unordered_map>
#ifndef PROJET_SYMBOLTABLE_H
#define PROJET_SYMBOLTABLE_H

class SymbolTable {
private:
    // hash table for storing the key-value pairs of the variable name and associated value
    std::unordered_map<std::string, float> variables;
public:
    void setValue(const std::string& name, float value);
    bool getValue(const std::string& name, float& value) const;

};

#endif //PROJET_SYMBOLTABLE_H
