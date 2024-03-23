//
// Created by antho on 23/03/2024.
//

#ifndef OPERATIONUNAIRE_H
#define OPERATIONUNAIRE_H

#include "../expression/Expression.h"

class OperationUnaire : public Expression {
    Expression *m_e;

public:
    OperationUnaire(Expression *m_e):
        m_e(m_e) {
    }

    ~OperationUnaire() override = default;

protected:
    Expression *get_e() const;
    void set_m_e(Expression *e);
};

#endif //OPERATIONUNAIRE_H