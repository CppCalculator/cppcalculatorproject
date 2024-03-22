//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef ADDITION_H
#define ADDITION_H


#include "../Operation.h"

class Addition final : public Operation{
public:
    Addition(Expression *m_eg, Expression *m_ed)
            : Operation(m_eg, m_ed) {
    }

    ~Addition() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;
};



#endif //ADDITION_H
