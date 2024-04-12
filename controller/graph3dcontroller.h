#ifndef GRAPH3DCONTROLLER_H
#include <QtGraphs>
#include "../model/expression/Expression.h"
#define GRAPH3DCONTROLLER_H

/**
* @brief The Graph3DController class, to control a 3D graph
* This should be used only inside a view ! Use Graph3DView !
*/
class Graph3DController
{
    private:
        Expression * _expression{};
        QSurface3DSeries * _series;
        int _borneX = 1;
        int _borneY = 1;
        float _min = 0;
        float _max = 0;
        void updateSurface();
    public:
        Graph3DController();
        void setExpression(Expression * expression);
        QSurfaceDataArray * getSurfaceFromExpression();
        QSurface3DSeries * getSeries();
        bool saveImage(QString const & filename, Q3DSurface * surface);
        // Setters
        void setBorneX(int const borneX) {
            this->_borneX = borneX;
            this->updateSurface();
        }
        void setBorneY(int const borneY) {
            this->_borneY = borneY;
            this->updateSurface();
        }
        // Getters
        int getBorneX() const {
            return this->_borneX;
        }
        int getBorneY() const {
            return this->_borneY;
        }
        float getMin() const {
            return this->_min;
        }
        float getMax() const {
            return this->_max;
        }
};

#endif // GRAPH3DCONTROLLER_H
