//
// Created by mathias.mourgues on 22/03/2024.
//
#include "Operation.h"
class Expression;

Expression * Operation::get_eg() const {
    return m_eg;
}

void Operation::set_m_eg(Expression *eg) {
    m_eg = eg;
}

Expression * Operation::get_ed() const {
    return m_ed;
}

void Operation::set_m_ed(Expression *ed) {
    m_ed = ed;
}

