//
// Created by antho on 23/03/2024.
//

#include "OperationUnaire.h"
class Expression;

Expression *OperationUnaire::get_e() const {
    return m_e;
}

void OperationUnaire::set_m_e(Expression *e) {
    m_e = e;
}