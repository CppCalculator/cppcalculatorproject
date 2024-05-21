#ifndef PROJET_VARIABLE_H
#define PROJET_VARIABLE_H

#include <iostream>
#include <map>
#include <QString>
#include "../expression/Expression.h"

class Variable : public Expression {
public:
    ~Variable() override = default;

    float calculer() override;

    void afficherNC() override;

    void afficherNPI() override;

    static Variable *construct(const char &name);

    static Variable *construct(const char &name, const float &value);

    void changeValue(const float &val);

    static std::map<const char, Variable *> getSymbolTable();

    void afficherNC(std::ostream& flux) const override;

    const char& getName() const;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;

    Expression* simplifier() override;

    QString toSymbol() const;

private:
    Variable(const char &name, const float &value);

    static constexpr float default_value = 1;

    const char name;
    float value;

    static std::map<const char, Variable *> symbolTable;
};

#endif //PROJET_VARIABLE_H
