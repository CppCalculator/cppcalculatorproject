// graph2dcontroller.h

#ifndef GRAPH2DCONTROLLER_H
#define GRAPH2DCONTROLLER_H

#include <QObject>
#include "../model/operations/addition/Addition.h"
#include "../model/variable/Variable.h"
#include "../view/graph2dview.h"

class Graph2dController : public QObject
{
Q_OBJECT
public:
    Graph2dController(Expression *expression, Variable *variable, Graph2dView *view, QObject *parent = nullptr);

private:
    Expression *expression;
    Variable *variable;
    Graph2dView *view;

private slots:
    void updateSeries();
};

#endif // GRAPH2DCONTROLLER_H
