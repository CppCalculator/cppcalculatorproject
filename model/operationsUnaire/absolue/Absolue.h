//
// Created by antho on 23/03/2024.
//

#ifndef ABSOLUE_H
#define ABSOLUE_H

#include "../OperationUnaire.h"

class Absolue final : public OperationUnaire{
public:
    Absolue(Expression *m_e)
        : OperationUnaire(m_e) {
    }

    ~Absolue() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};

#endif //ABSOLUE_H