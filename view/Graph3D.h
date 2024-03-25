//
// Created by devil on 25/03/2024.
//

#ifndef GRAPH3D_H
#define GRAPH3D_H

#include <QtGraphs>

#include "model/expression/Expression.h"

class Graph3D {
    private:
        Expression * _expression;
        Q3DSurface * _surface;
        QSurface3DSeries * _series;
        int _borne = 1;
        float _min = 0;
        float _max = 0;
        QSurfaceDataArray * getSurfaceFromExpression() ;
        void setupResolutionSlider(QVBoxLayout *panelLayout);
        void setupAxisRanges() const;
    public:
        Graph3D(int argc, char **argv, Expression * expression);
        void setExpression(Expression * expression);
};



#endif //GRAPH3D_H
