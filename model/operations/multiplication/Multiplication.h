//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "../Operation.h"

class Multiplication: public Operation{
public:
    Multiplication(Expression *m_eg, Expression *m_ed)
        : Operation(m_eg, m_ed) {
    }

    ~Multiplication() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    void afficherNPI(std::ostream &flux) const override;
    void sauvegardeASCII(const std::string &n_fichier) override;
    float calculer() override;

};



#endif //MULTIPLICATION_H
