// graph2dview.cpp

#include "graph2dview.h"
#include <QVBoxLayout>
#include <QValueAxis> // Ajout de cette ligne

Graph2dView::Graph2dView(QWidget *parent) : QWidget(parent)
{
    chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("2D Chart");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    xSlider = new QSlider(Qt::Horizontal);
    xSlider->setRange(0, 200); // Plage du slider pour l'échelle X
    xSlider->setValue(100);    // Valeur par défaut pour centrer l'échelle

    ySlider = new QSlider(Qt::Vertical);
    ySlider->setRange(0, 200); // Plage du slider pour l'échelle Y
    ySlider->setValue(100);    // Valeur par défaut pour centrer l'échelle

    auto *mainLayout = new QVBoxLayout;
    auto *sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(chartView);
    sliderLayout->addWidget(ySlider);

    mainLayout->addLayout(sliderLayout);
    mainLayout->addWidget(xSlider);

    setLayout(mainLayout);

    auto *axisX = new QValueAxis;
    auto *axisY = new QValueAxis;

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Connecter les sliders pour mettre à jour les axes
    connect(xSlider, &QSlider::valueChanged, [=](int value) {
        double range = value * 1.0; // Convertir en double pour obtenir une précision décimale
        double min = -range / 2.0;
        double max = range / 2.0;
        axisX->setRange(min, max);
    });

    connect(ySlider, &QSlider::valueChanged, [=](int value) {
        double range = value * 1.0; // Convertir en double pour obtenir une précision décimale
        double min = -range / 2.0;
        double max = range / 2.0;
        axisY->setRange(min, max);
    });
}

void Graph2dView::setSeries(QLineSeries *series)
{
    chart->removeAllSeries();
    chart->addSeries(series);

    // Ajouter les axes
    auto *axisX = chart->axes(Qt::Horizontal).first();
    auto *axisY = chart->axes(Qt::Vertical).first();

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

QSlider *Graph2dView::getXSlider() const
{
    return xSlider;
}

QSlider *Graph2dView::getYSlider() const
{
    return ySlider;
}

QChart *Graph2dView::getChart() const
{
    return chart;
}