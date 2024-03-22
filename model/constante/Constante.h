//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef CONSTANTE_H
#define CONSTANTE_H
#include "../expression/Expression.h"


class Constante final : public Expression {
    float m_valeur;

public:
    explicit Constante(const float m_valeur)
            : m_valeur(m_valeur) {
    }

    ~Constante() override = default;

    float calculer() override;
    void afficherNC() override;
    void afficherNPI() override;
    Expression* simplifier() override;

};


#endif //CONSTANTE_H
