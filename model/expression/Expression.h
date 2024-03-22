//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H


class Expression {
public:
    virtual ~Expression() = default;
    virtual void afficherNC() = 0;
    virtual void afficherNPI() = 0;
    virtual float calculer() = 0;
    virtual Expression* simplifier() = 0;
};



#endif //EXPRESSION_H
