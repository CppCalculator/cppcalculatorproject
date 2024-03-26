//
// Created by Mathias CITRINI and William Der Krikorian on 25/03/2024.
//

#include "Graph3D.h"
#include <QtWidgets/QApplication>
#include <cmath>

/**
 * @brief Constructor of the Graph3D class
 * @param argc - The number of arguments
 * @param argv - The arguments
 */
Graph3D::Graph3D(int argc, char **argv, Expression * expression) {
    _expression = expression;
    QApplication app(argc, argv);

    // Surface Graph
    _surface = new Q3DSurface();
    _surface->setMinimumSize(QSize(256, 256));
    _surface->setResizeMode(QQuickWidget::SizeRootObjectToView);
    _surface->activeTheme()->setType(Q3DTheme::ThemePrimaryColors);
    _surface->activeTheme()->setLabelBackgroundEnabled(false);
    _surface->activeTheme()->setLabelBorderEnabled(false);
    _surface->activeTheme()->setGridEnabled(false);
    _series = new QSurface3DSeries;
    _series->dataProxy()->resetArray(getSurfaceFromExpression());
    _surface->addSeries(_series);
    setupAxisRanges();

    // Widget and layouts
    auto *widget = new QWidget;
    auto *mainLayout = new QHBoxLayout;
    auto *surfaceLayout = new QVBoxLayout;
    auto *panelLayout = new QVBoxLayout;
    panelLayout->setSizeConstraint(QLayout::SetFixedSize);
    panelLayout->setAlignment(Qt::AlignTop);
    surfaceLayout->setContentsMargins(0, 0, 5, 0);
    panelLayout->setContentsMargins(5, 0, 0, 0);
    mainLayout->setSpacing(0);

    auto *graphLabel = new QLabel("Graph 3D of the expression");
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setMargin(10);
    panelLayout->addWidget(graphLabel);

    setupResolutionSlider(panelLayout);

    // Add the scatter plot to the left layout and set its size policy to expand
    surfaceLayout->addWidget(_surface);
    _surface->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    surfaceLayout->setAlignment(Qt::AlignTop); // Align the scatter plot to the top

    // Add the layouts to the main layout
    mainLayout->addLayout(surfaceLayout);
    mainLayout->addLayout(panelLayout);
    widget->setLayout(mainLayout);

    // Show the widget
    widget->show();
    QApplication::exec();
}

void Graph3D::setupAxisRanges() const {
    auto const borneFloat = static_cast<float>(_borne);
    _surface->axisX()->setRange(-borneFloat - 1, borneFloat +1);
    _surface->axisY()->setRange(-borneFloat - 1, borneFloat +1);
    _surface->axisZ()->setRange(_min - 1, _max + 1);
}

/**
 * @brief Setup the resolution slider
 * @param panelLayout - The layout of the panel
 * @param series - The series of the graph
 */
void Graph3D::setupResolutionSlider(QVBoxLayout *panelLayout)
{
    // Slider for range x of the graph
    auto *resolutionSlider = new QSlider(Qt::Horizontal);
    resolutionSlider->setMinimum(1);
    resolutionSlider->setMaximum(20);
    resolutionSlider->setValue(_borne);
    resolutionSlider->setTickInterval(1);
    resolutionSlider->setSingleStep(1);
    resolutionSlider->setTickPosition(QSlider::TicksBelow);
    QObject::connect(resolutionSlider, &QSlider::valueChanged, [this](int const value) {
        _borne = value;
        _series->dataProxy()->resetArray(getSurfaceFromExpression());
        setupAxisRanges();
    });
    auto *xLabel = new QLabel("Resolution");
    panelLayout->addWidget(xLabel);
    panelLayout->addWidget(resolutionSlider);
    resolutionSlider->setFixedWidth(200);
}

/**
 * @brief Get the surface from the Expression object. It calculates the value of the expression for each point of the graph between -_borne and _borne
 * @return QSurfaceDataArray* - The surface data array
 */
QSurfaceDataArray* Graph3D::getSurfaceFromExpression() {
    auto *data = new QSurfaceDataArray;

    for (int x = -_borne; x <= _borne; x++) {
        auto *row = new QSurfaceDataRow;

        for (int y = -_borne; y <= _borne; y++) {
            auto const xFloat = static_cast<float>(x);
            auto const yFloat = static_cast<float>(y);
            float const z = std::sin(std::sqrt(xFloat * xFloat + yFloat * yFloat));
            if (x== -_borne && y == -_borne) {
                _min = z;
                _max = z;
            } else {
                if (z < _min) {
                    _min = z;
                }
                if (z > _max) {
                    _max = z;
                }
            }
            *row << QVector3D(xFloat, yFloat, z);
        }
        *data << row;
    }
    return data;
}

/**
 * @brief Set the expression of the graph
 * @param expression - The expression to set
 */
void Graph3D::setExpression(Expression * expression) {
    _expression = expression;
    _series->dataProxy()->resetArray(getSurfaceFromExpression());
    setupAxisRanges();
}


