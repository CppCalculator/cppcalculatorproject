//
// Created by antho on 23/03/2024.
//

#ifndef INVERSE_H
#define INVERSE_H

#include "../OperationUnaire.h"

class Inverse final : public OperationUnaire{
public:
    Inverse(Expression *m_e)
        : OperationUnaire(m_e) {
    }

    ~Inverse() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;

    void afficherNC(std::ostream& flux) const override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};

#endif //INVERSE_H
