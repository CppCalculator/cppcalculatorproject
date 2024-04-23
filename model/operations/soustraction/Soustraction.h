//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef SOUSTRACTION_H
#define SOUSTRACTION_H
#include "../Operation.h"


class Soustraction final : public Operation{
public:
    Soustraction(Expression *m_eg, Expression *m_ed)
            : Operation(m_eg, m_ed) {
    }

    ~Soustraction() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;
    void sauvegardeASCII(const std::string &n_fichier) override;
    void afficherNPI(std::ostream &flux) const override;
};



#endif //SOUSTRACTION_H
