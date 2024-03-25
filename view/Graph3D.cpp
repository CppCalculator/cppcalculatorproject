//
// Created by devil on 25/03/2024.
//

#include "Graph3D.h"
#include <QtWidgets/QApplication>

Graph3D::Graph3D(int argc, char **argv) {
    QApplication app(argc, argv);

    // Scatter Graph
    _scatter = new Q3DScatter();
    _scatter->setMinimumSize(QSize(256, 256));
    _scatter->setResizeMode(QQuickWidget::SizeRootObjectToView);
    auto *series = new QScatter3DSeries;
    _data = test();
    series->dataProxy()->addItems(_data);
    _scatter->addSeries(series);

    // Set the title of each axis
    _scatter->axisX()->setTitle("X Axis");
    _scatter->axisY()->setTitle("Y Axis");
    _scatter->axisZ()->setTitle("Z Axis");

    // Set the range of each axis
    _scatter->axisX()->setRange(-10, 10);
    _scatter->axisY()->setRange(-10, 10);

    // Widget and layouts
    QWidget *widget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *scatterLayout = new QVBoxLayout;
    QVBoxLayout *panelLayout = new QVBoxLayout;
    panelLayout->setSizeConstraint(QLayout::SetFixedSize);
    scatterLayout->setContentsMargins(0, 0, 5, 0);
    panelLayout->setContentsMargins(5, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Add the scatter plot to the left layout and set its size policy to expand
    scatterLayout->addWidget(_scatter);
    _scatter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scatterLayout->setAlignment(Qt::AlignTop); // Align the scatter plot to the top

    // Add a slider to control the range of the X axis
    QValue3DAxis *xAxis = _scatter->axisX();
    QSlider *xSlider = new QSlider(Qt::Horizontal);
    xSlider->setRange(-10, 10);
    xSlider->setValue(10);
    _scatter->axisX()->setMin(-10);
    _scatter->axisX()->setMax(10);
    QObject::connect(xSlider, &QSlider::valueChanged, xAxis, &QValue3DAxis::setMax);
    QLabel *xLabel = new QLabel("X Axis Range");
    panelLayout->addWidget(xLabel);
    panelLayout->addWidget(xSlider);
    xSlider->setFixedWidth(200);

    // Add a slider to control the range of the Y axis
    QValue3DAxis *yAxis = _scatter->axisY();
    QSlider *ySlider = new QSlider(Qt::Horizontal);
    ySlider->setRange(-10, 10);
    ySlider->setValue(10);
    _scatter->axisY()->setMin(-10);
    _scatter->axisY()->setMax(10);
    QObject::connect(ySlider, &QSlider::valueChanged, yAxis, &QValue3DAxis::setMax);
    QLabel *yLabel = new QLabel("Y Axis Range");
    panelLayout->addWidget(yLabel);
    panelLayout->addWidget(ySlider);
    ySlider->setFixedWidth(200);

    // Add a slider to control the range of the Z axis
    QValue3DAxis *zAxis = _scatter->axisZ();
    QSlider *zSlider = new QSlider(Qt::Horizontal);
    zSlider->setRange(_min, _max);
    zSlider->setValue(_max);
    _scatter->axisZ()->setMin(_min);
    _scatter->axisZ()->setMax(_max);
    QObject::connect(zSlider, &QSlider::valueChanged, zAxis, &QValue3DAxis::setMax);
    panelLayout->setAlignment(Qt::AlignTop);
    QLabel *zLabel = new QLabel("Z Axis Range");
    panelLayout->addWidget(zLabel);
    panelLayout->addWidget(zSlider);
    zSlider->setFixedWidth(200);

    // Add the layouts to the main layout
    mainLayout->addLayout(scatterLayout);
    mainLayout->addLayout(panelLayout);
    widget->setLayout(mainLayout);

    // Show the widget
    widget->show();
    app.exec();
}

QScatterDataArray Graph3D::test() {
    QScatterDataArray data;
    for (int x = -10; x < 10; x++) {
        for (int y = -10; y < 10; y++) {
            float xFloat = x;
            float yFloat = y;
            float z = 12*cosf((xFloat * xFloat + yFloat * yFloat)/4)/3 + xFloat * xFloat + yFloat * yFloat;
            if (z < _min) {
                _min = z;
            }
            if (z > _max) {
                _max = z;
            }
            data << QVector3D(xFloat, yFloat, z);
        }
    }
    return data;
}

