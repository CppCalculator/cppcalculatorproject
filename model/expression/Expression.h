//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <ostream>
#include <string>


class Expression {
public:
    virtual ~Expression() = default;

    virtual void afficherNC() = 0;

    virtual void afficherNPI() = 0;

    virtual float calculer() = 0;

    virtual void afficherNPI(std::ostream& flux) const = 0;

    virtual void sauvegardeASCII(const std::string& n_fichier) = 0;
};


#endif //EXPRESSION_H
