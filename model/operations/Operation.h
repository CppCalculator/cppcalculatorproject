//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef OPERATION_H
#define OPERATION_H
#include "../expression/Expression.h"


class Operation : public Expression {
    Expression *m_eg;
    Expression *m_ed;

public:
    Operation(Expression *m_eg, Expression *m_ed)
            : m_eg(m_eg),
              m_ed(m_ed) {
    }

    ~Operation() override = default;

protected:
    [[nodiscard]] Expression *get_eg() const;

    void set_m_eg(Expression *eg);

    [[nodiscard]] Expression *get_ed() const;

    void set_m_ed(Expression *ed);

};


#endif //OPERATION_H
