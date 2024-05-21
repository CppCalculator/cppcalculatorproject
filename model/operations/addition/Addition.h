//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef ADDITION_H
#define ADDITION_H

#include "../Operation.h"

#include <string>

class Addition final : public Operation {
public:
    Addition(Expression *m_eg, Expression *m_ed)
            : Operation(m_eg, m_ed) {
    }

    ~Addition() override = default;

    void afficherNC() override;

    void afficherNPI() override;

    float calculer() override;

    Expression* simplifier() override;

    void afficherNC(std::ostream& flux) const override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};


#endif //ADDITION_H
