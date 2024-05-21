#include "Variable.h"

std::map<const char, Variable *> Variable::symbolTable;

Variable::Variable(const char &name, const float &value) : name(name), value(value) {}

float Variable::calculer() {
    return value;
}

void Variable::afficherNC() {
    std::cout << name;
}

void Variable::afficherNPI() {
    std::cout << name;
}

Variable *Variable::construct(const char &name) {
    if (symbolTable.find(name) == symbolTable.end()) {
        float value;
        std::cout << "Assign " << name << " a value:";
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cout << "Invalid input. Using the default value: " << default_value << std::endl;
            value = default_value;
        }

        symbolTable[name] = new Variable(name, value);
    }

    return symbolTable[name];
}

Variable *Variable::construct(const char &name, const float &value) {
    if (symbolTable.find(name) == symbolTable.end()) {
        symbolTable[name] = new Variable(name, value);
    }

    return symbolTable[name];
}

void Variable::changeValue(const float &val) {
    this->value = val;
    symbolTable[name]->value = val;
}

std::map<const char, Variable *> Variable::getSymbolTable() {
    return symbolTable;
}

void Variable::afficherNC(std::ostream &flux) const {
    //TODO implement GP2
}

const char& Variable::getName() const {
    return name;
}

void Variable::afficherNPI(std::ostream &flux) const {
    //TODO implement GP2
}

void Variable::sauvegardeASCII(const std::string &n_fichier) {
    //TODO implement GP2
}

Expression *Variable::simplifier() {
    //TODO implement GP7
    return nullptr;
}

QString Variable::toSymbol() const {
    return QString(name);
}
