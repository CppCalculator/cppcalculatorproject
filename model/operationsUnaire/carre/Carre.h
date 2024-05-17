//
// Created by antho on 23/03/2024.
//

#ifndef CARRE_H
#define CARRE_H

#include "../OperationUnaire.h"

class Carre final: public OperationUnaire {
public:
    Carre(Expression *m_e)
        : OperationUnaire(m_e) {
    }

    ~Carre() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
    Expression* simplifier() override;

    void afficherNPI(std::ostream& flux) const override;

    void sauvegardeASCII(const std::string& n_fichier) override;
};

#endif //CARRE_H