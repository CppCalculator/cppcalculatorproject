//
// Created by antho on 23/03/2024.
//

#ifndef OPPOSE_H
#define OPPOSE_H

#include "../OperationUnaire.h"

class Oppose final : public OperationUnaire{
public:
    Oppose(Expression *m_e)
        : OperationUnaire(m_e) {
    }

    ~Oppose() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};

#endif //OPPOSE_H