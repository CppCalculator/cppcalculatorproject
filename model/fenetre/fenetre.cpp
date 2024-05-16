#include "fenetre.h"


FenetrePrincipale::FenetrePrincipale() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->setContentsMargins(5,5,5,5);
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Expression - Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

void FenetrePrincipale::createActions() {
    chargerFichierAction = new QAction(tr("&Ouvrir"), this);
    chargerFichierAction->setShortcut(QKeySequence::Open);
    chargerFichierAction->setStatusTip(tr("&Charger un fichier"));

    enregistrerFichierAction = new QAction(tr("&Enregistrer"), this);
    enregistrerFichierAction->setShortcut(QKeySequence::Save);
    enregistrerFichierAction->setStatusTip(tr("&Enregistrer dans un fichier"));

    saisirExpressionAction = new QAction(tr("&Saisir une expression"), this);
    saisirExpressionAction->setStatusTip(tr("&Saisir une expression"));
    connect(saisirExpressionAction, &QAction::triggered, this, &FenetrePrincipale::saisirExpression);

    affichageClassiqueAction = new QAction(tr("&Afficher l'expression"));
    affichageClassiqueAction->setStatusTip(tr("&Afficher l'expression"));

    affichageNPIAction = new QAction(tr("&Afficher l'expresion en NPI"));
    affichageNPIAction->setStatusTip(tr("&Afficher de l'expression en notation Polonaise inversée"));

    affichageValeurExpressionAction = new QAction(tr("&Afficher la valeur de l'expression"));
    affichageValeurExpressionAction->setStatusTip(tr("&Afficher la valeur de l'expression"));

    affichageGraphique2DAction = new QAction(tr("&Afficher le graphique 2D"));
    affichageGraphique2DAction->setStatusTip(tr("&Afficher le graphique 2D de l'expression"));

    affichageGraphique3DAction = new QAction(tr("&Affichager le graphique 3D"));
    affichageGraphique3DAction->setStatusTip(tr("&Afficher le graphique 3D de l'expression"));

    simplificationExpressionAction = new QAction(tr("&Simplier l'expression"));
    simplificationExpressionAction->setStatusTip(tr("&Simplifier l'expression"));
}

void FenetrePrincipale::createMenus() {
    fichierMenu = menuBar()->addMenu(tr("&Fichier"));
    fichierMenu->addAction(chargerFichierAction);
    fichierMenu->addAction(enregistrerFichierAction);

    editionMenu = menuBar()->addMenu("&Edition");
    editionMenu->addAction(saisirExpressionAction);
    editionMenu->addAction(affichageClassiqueAction);
    editionMenu->addAction(affichageNPIAction);
    editionMenu->addAction(affichageValeurExpressionAction);
    editionMenu->addAction(affichageGraphique2DAction);
    editionMenu->addAction(affichageGraphique3DAction);

    outilsMenu = menuBar()->addMenu("&Outils");
    outilsMenu->addAction(simplificationExpressionAction);
}

void FenetrePrincipale::saisirExpression() {
    Calculator c;
    layout->addLayout(c.getLayout());
}
