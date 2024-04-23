//
// Created by mathias.mourgues on 22/03/2024.
//

#ifndef DIVISION_H
#define DIVISION_H

#include "../Operation.h"

class Division: public Operation{
public:
    Division(Expression *m_eg, Expression *m_ed)
        : Operation(m_eg, m_ed) {
    }

    ~Division() override = default;

    void afficherNC() override;
    void afficherNPI() override;
    void afficherNPI(std::ostream &flux) const override;
    void sauvegardeASCII( const std::string &n_fichier) override;
    float calculer() override;
};



#endif //DIVISION_H
