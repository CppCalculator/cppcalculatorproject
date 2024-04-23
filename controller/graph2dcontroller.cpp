// graph2dcontroller.cpp

#include "graph2dcontroller.h"

Graph2dController::Graph2dController(Expression *expression, Variable *variable, Graph2dView *view, QObject *parent) : QObject(parent)
{
    this->expression = expression;
    this->variable = variable;
    this->view = view;

    connect(view->getXSlider(), &QSlider::valueChanged, this, &Graph2dController::updateSeries);
    connect(view->getYSlider(), &QSlider::valueChanged, this, &Graph2dController::updateSeries);
}

void Graph2dController::updateSeries()
{
    int minX = view->getXSlider()->minimum();
    int maxX = view->getXSlider()->maximum();
    int step = 1; // Valeur de pas

    auto series = new QLineSeries();
    for (int x = minX; x <= maxX; x += step)
    {
        variable->changeValue(x);
        series->append(x, expression->calculer());
    }
    view->setSeries(series);
}
