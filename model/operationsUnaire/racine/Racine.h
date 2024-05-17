//
// Created by antho on 23/03/2024.
//

#ifndef RACINE_H
#define RACINE_H

#include "../OperationUnaire.h"

class Racine final : public OperationUnaire{
public:
    Racine(Expression *m_e)
        : OperationUnaire(m_e) {
    }

    ~Racine() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};

#endif //RACINE_H