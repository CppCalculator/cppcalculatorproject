//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef CONSTANTE_H
#define CONSTANTE_H
#include "../expression/Expression.h"
#include <iostream>
#include <string>

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
    void afficherNPI(std::ostream &flux) const override;
    void sauvegardeASCII(const std::string &n_fichier) override;
};


#endif //CONSTANTE_H
