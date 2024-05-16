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
#include "../../view/calculator.h"

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
    void chargerFichier();
    void enregistrerFichier();
    */
    void saisirExpression();
    /*
    void affichageClassique();
    void affichageNPI();
    void afficherValeurExpression();
    void affichageGraphique2D();
    void affichageGraphique3D();
    void simplificationExpression();
    */

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
};

#endif // MAINWINDOW_H
