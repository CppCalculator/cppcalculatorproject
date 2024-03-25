//
// Created by devil on 25/03/2024.
//

#ifndef GRAPH3D_H
#define GRAPH3D_H

#include <QtGraphs>

class Graph3D {
    private:
        Q3DScatter * _scatter;
        QScatterDataArray _data;
        float _min = 0;
        float _max = 0;
    public:
        Graph3D(int argc, char **argv);
        QScatterDataArray test();
};



#endif //GRAPH3D_H
