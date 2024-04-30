// graph2dview.h

#ifndef GRAPH2DVIEW_H
#define GRAPH2DVIEW_H

#include <QWidget>
#include <QtCharts>

class Graph2dView : public QWidget
{
Q_OBJECT
public:
    Graph2dView(QWidget *parent = nullptr);

    QSlider *getXSlider() const;
    QSlider *getYSlider() const;
    QChart *getChart() const;

    void setSeries(QLineSeries *series);

private:
    QChart *chart;
    QChartView *chartView;
    QSlider *xSlider;
    QSlider *ySlider;
};

#endif // GRAPH2DVIEW_H
