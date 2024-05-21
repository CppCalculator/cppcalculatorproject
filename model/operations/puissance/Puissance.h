//
// Created by antho on 23/03/2024.
//

#ifndef PUISSANCE_H
#define PUISSANCE_H

#include "../Operation.h"

class Puissance final : public Operation {
public:
    Puissance(Expression *m_eg, Expression *m_ed)
        : Operation(m_eg, m_ed) {
    }

    ~Puissance() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;

    Expression* simplifier() override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};

#endif //PUISSANCE_H