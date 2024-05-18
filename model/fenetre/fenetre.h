#ifndef FENETREPRINCIPAL_H
#define FENETREPRINCIPAL_H

#include <QContextMenuEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <sstream>
#include "../../view/calculator.h"
#include "../expression/Expression.h"
#include "../utils/data.h"
#include "../../view/graph3dview.h"
#include "../../view/graph2dview.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class FenetrePrincipale: public QMainWindow
{
    Q_OBJECT
public:
    FenetrePrincipale();

private slots:
    /**
    void enregistrerFichier();
    */
    void chargerFichier();
    void saisirExpression();
    void afficherClassique();
    void afficherNPI();
    void afficherValeurExpression();
    void affichageGraphique2D();
    void affichageGraphique3D();
    void simplifierExpression();

private:
    void createActions();
    void createMenus();

    QWidget *widget;

    QMenu *fichierMenu;
    QMenu *editionMenu;
    QMenu *outilsMenu;
    QAction *chargerFichierAction;
    QAction *enregistrerFichierAction;
    QAction *saisirExpressionAction;
    QAction *affichageClassiqueAction;
    QAction *affichageNPIAction;
    QAction *affichageValeurExpressionAction;
    QAction *affichageGraphique2DAction;
    QAction *affichageGraphique3DAction;
    QAction *simplificationExpressionAction;
    QLabel *infoLabel;
    QVBoxLayout *layout = new QVBoxLayout;
    Calculator *calculatorView = NULL;
};

#endif // MAINWINDOW_H
