#ifndef GRAPH3DVIEW_H
#include "../controller/graph3dcontroller.h"
#define GRAPH3DVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QtGraphs>

/**
* @brief The Graph3DView class, to display a 3D graph
*/
class Graph3DView : public QWidget
{
    Q_OBJECT
private:
    Graph3DController * _controller;
    Q3DSurface * _surface;
    bool _gridEnabled = false;
    bool _labelEnabled = true;
    bool _labelBorderEnabled = false;
    void addTitle(const QString &title, QVBoxLayout *panelLayout);
    void setupXSlider(QVBoxLayout *panelLayout);
    void setupYSlider(QVBoxLayout *panelLayout);
    void setupThemeComboBox(QVBoxLayout *panelLayout);
    void setToggleGridButton(QVBoxLayout *panelLayout);
    void setupAxisRanges() const;
    void setExportButton(QVBoxLayout *panelLayout) const;
    void exportGraph();
    void setLabelRadioButtons(QVBoxLayout *panelLayout);
public:
    explicit Graph3DView(QWidget *parent = nullptr);
    void setExpression(Expression * expression) const;
signals:
};

#endif // GRAPH3DVIEW_H