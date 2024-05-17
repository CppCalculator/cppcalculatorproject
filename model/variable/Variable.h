#ifndef PROJET_VARIABLE_H
#define PROJET_VARIABLE_H

#include <iostream>
#include <map>
#include "../expression/Expression.h"

class Variable : public Expression {
public:
    ~Variable() override = default;

    float calculer() override;

    void afficherNC() override;

    void afficherNPI() override;

    /**
     * Method that acts as a constructor for the Variable class.
     * It creates a new Variable object if it doesn't exist in the symbolTable.
     * It returns the Variable object from the symbolTable as a pointer.
     *
     * @param name: the name of the variable
     * @return Pointer to the Variable object
     */
    static Variable *construct(const char &name);

    /**
     * Method that acts as a constructor for the Variable class.
     * It creates a new Variable object if it doesn't exist in the symbolTable.
     * It returns the Variable object from the symbolTable as a pointer.
     *
     * @param name: the name of the variable
     * @param value: the value of the variable
     * @return Pointer to the Variable object
     */
    static Variable *construct(const char &name, const float &value);

    /**
     * Method that changes the value of the variable.
     *
     * @param val: the new value of the variable
     */
    void changeValue(const float &val);

    /**
     * Method that returns the symbolTable.
     *
     * @return The symbol table
     */
    static std::map<const char, Variable *> getSymbolTable();

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;

    Expression* simplifier() override;

private:
    Variable(const char &name, const float &value);

    static constexpr float default_value = 1;
    const char name;
    float value;

    static std::map<const char, Variable *> symbolTable;
};

#endif //PROJET_VARIABLE_H
