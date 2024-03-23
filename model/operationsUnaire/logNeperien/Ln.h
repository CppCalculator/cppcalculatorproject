//
// Created by antho on 23/03/2024.
//

#ifndef LN_H
#define LN_H

#include "../OperationUnaire.h"

class Ln final : public OperationUnaire{
public:
    Ln(Expression *m_e)
        : OperationUnaire(m_e) {
    }

    ~Ln() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    float calculer() override;
};

#endif //LN_H