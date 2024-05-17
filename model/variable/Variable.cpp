#include "Variable.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <limits>

// Déclaration et initialisation de la table des symboles
std::map<const char, Variable*> Variable::symbolTable;

// Constructeur
Variable::Variable(const char &name, const float &value) : name(name), value(value) {}

// Méthode pour calculer la valeur de la variable
float Variable::calculer() {
    return value;
}

// Afficher la variable en notation normale
void Variable::afficherNC() {
    std::cout << name;
}

// Afficher la variable en notation polonaise inverse
void Variable::afficherNPI() {
    std::cout << name;
}

// Constructeur statique sans valeur initiale spécifique
Variable* Variable::construct(const char &name) {
    auto it = symbolTable.find(name);
    if (it == symbolTable.end()) {
        float value;
        std::cout << "Assignez une valeur a " << name << " : ";
        std::cin >> value;
        if (!std::cin) {  // Vérifie si l'entrée n'était pas un flottant
            std::cin.clear(); // Efface le drapeau d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore le reste de la ligne
            std::cout << "Entrée invalide. Utilisation de la valeur par défaut : " << default_value << std::endl;
            value = default_value;
        }
        Variable* newVar = new Variable(name, value);
        symbolTable[name] = newVar;
    }
    return symbolTable[name];
}

// Constructeur statique avec valeur initiale spécifique
Variable* Variable::construct(const char &name, const float &value) {
    auto it = symbolTable.find(name);
    if (it == symbolTable.end()) {
        symbolTable[name] = new Variable(name, value);
    } else {
        it->second->changeValue(value); // Modifier la valeur si déjà existante
    }
    return symbolTable[name];
}

// Modifier la valeur de la variable
void Variable::changeValue(const float &val) {
    value = val;
}

// Récupérer la table des symboles
std::map<const char, Variable*> Variable::getSymbolTable() {
    return symbolTable;
}

// Méthode afficherNPI avec flux
void Variable::afficherNPI(std::ostream &flux) const {
    flux << name;
}

// Méthode pour sauvegarder la variable en format ASCII dans un fichier
void Variable::sauvegardeASCII(const std::string &n_fichier) {
    // À implémenter
}

// Simplifier l'expression (pas nécessaire pour une simple variable)
Expression* Variable::simplifier() {
    return this; // Retourner la même instance car il n'y a pas de simplification pour une variable simple
}
