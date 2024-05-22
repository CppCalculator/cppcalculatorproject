#include "graph3dcontroller.h"
#include "../model/variable/Variable.h"

Graph3DController::Graph3DController() {
    this->_series = new QSurface3DSeries;
}

/**
 * @brief Set the expression of the graph
 * @param expression - The expression to set
 */
void Graph3DController::setExpression(Expression * expression) {
    this->_expression = expression;
    expression->afficherNPI();
    this->_series->dataProxy()->resetArray(getSurfaceFromExpression());
}

/**
 * @brief Get the surface from the Expression object. It calculates the value of the expression for each point of the graph between -_borne and _borne
 * @return QSurfaceDataArray* - The surface data array
 */
QSurfaceDataArray* Graph3DController::getSurfaceFromExpression() {
    if (Variable::getSymbolTable().size() != 2) {
        std::cerr << "You must have exactly 2 variables in the symbol table to display a 3D graph" << std::endl;
        return nullptr;
    }
    auto *data = new QSurfaceDataArray;
    _min = _expression->calculer();
    _max = _min;
    auto * xVar = Variable::construct('x');
    auto * yVar = Variable::construct('y');

    for (int x = -_borneX; x <= _borneX; x++) {
        auto *row = new QSurfaceDataRow;
        for (int y = -_borneY; y <= _borneY; y++) {
            auto const xFloat = static_cast<float>(x);
            auto const yFloat = static_cast<float>(y);
            xVar->changeValue(xFloat);
            yVar->changeValue(yFloat);
            auto const z = _expression->calculer();
            if (z < _min) {
                _min = z;
            }
            if (z > _max) {
                _max = z;
            }
            *row << QVector3D(xFloat, yFloat, z);
        }
        *data << row;
    }
    return data;
}

/**
 * @brief Update the surface of the graph
 */
void Graph3DController::updateSurface() {
    this->_series->dataProxy()->resetArray(getSurfaceFromExpression());
}

/**
 * @brief Get the series (values) of the graph
 * @return QSurface3DSeries* - The series of the graph
 */
QSurface3DSeries * Graph3DController::getSeries() {
    return _series;
}

/**
 * @brief Export the graph view
 * @return bool - True if the export was successful, false otherwise
 */
bool Graph3DController::saveImage(QString const & filename, Q3DSurface * surface) {
    QImage image(surface->size(), QImage::Format_ARGB32);
    surface->render(&image);
    return image.save(filename);
}

