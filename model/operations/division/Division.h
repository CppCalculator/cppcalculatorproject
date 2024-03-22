//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef DIVISION_H
#define DIVISION_H

#include "../Operation.h"

class Division: public Operation{
public:
    Division(Expression *m_eg, Expression *m_ed)
            : Operation(m_eg, m_ed) {
    }

    ~Division() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;
};



#endif //DIVISION_H
