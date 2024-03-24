////
//// Created by Sofia Boldeskul on 22.03.2024.
////
//
//#ifndef PROJET_VARIABLE_H
//#define PROJET_VARIABLE_H
//
//#include "../expression/Expression.h"
//
//class Variable final : public Expression {
//    float m_value;
//    // we ask user
//    // user replies _> we use user reply
//    // user doesnt reply -> we use default
//    char m_name;
//
//public:
//    explicit Variable(const char &name);
//
//
//    Variable(const float &m_value, const char &m_name)
//            : m_value(m_value), m_name(m_name) {
//
//    }
//
//    ~Variable() override = default;
//
//    void setValue(const float &value);
//
//    float calculer() override;
//
//    void afficherNC() override;
//
//    void afficherNPI() override;
//};
//
//#endif //PROJET_VARIABLE_H


#ifndef PROJET_VARIABLE_H
#define PROJET_VARIABLE_H

#include "../expression/Expression.h"
#include <string>
#include "SymbolTable.h"

class Variable final : public Expression {
    std::string m_name;
    SymbolTable& symbolTable;

public:
    Variable(const std::string& m_name, SymbolTable& symbolTable);

    ~Variable() override = default;

    float calculer() override;

    void afficherNC() override;

    void afficherNPI() override;
};

#endif //PROJET_VARIABLE_H
