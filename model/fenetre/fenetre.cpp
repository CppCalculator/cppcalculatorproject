#include "fenetre.h"


FenetrePrincipale::FenetrePrincipale() {
    widget = new QWidget;
    setCentralWidget(widget);

    layout = new QVBoxLayout(widget);

    topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->setMenuBar(topFiller);

    createActions();
    createMenus();

    setWindowTitle(tr("Expression"));
    setMinimumSize(160, 160);
    resize(1200, 800);
}

void FenetrePrincipale::createActions() {
    chargerFichierAction = new QAction(tr("&Ouvrir"), this);
    chargerFichierAction->setShortcut(QKeySequence::Open);
    chargerFichierAction->setStatusTip(tr("&Charger un fichier"));
    connect(chargerFichierAction, &QAction::triggered, this, &FenetrePrincipale::chargerFichier);

    enregistrerFichierAction = new QAction(tr("&Enregistrer"), this);
    enregistrerFichierAction->setShortcut(QKeySequence::Save);
    enregistrerFichierAction->setStatusTip(tr("&Enregistrer dans un fichier"));

    saisirExpressionAction = new QAction(tr("&Saisir une expression"), this);
    saisirExpressionAction->setStatusTip(tr("&Saisir une expression"));
    connect(saisirExpressionAction, &QAction::triggered, this, &FenetrePrincipale::saisirExpression);

    affichageClassiqueAction = new QAction(tr("&Afficher l'expression"));
    affichageClassiqueAction->setStatusTip(tr("&Afficher l'expression"));
    connect(affichageClassiqueAction, &QAction::triggered, this, &FenetrePrincipale::afficherClassique);

    affichageNPIAction = new QAction(tr("&Afficher l'expresion en NPI"));
    affichageNPIAction->setStatusTip(tr("&Afficher de l'expression en notation Polonaise inversée"));
    connect(affichageNPIAction, &QAction::triggered, this, &FenetrePrincipale::afficherNPI);

    affichageValeurExpressionAction = new QAction(tr("&Afficher la valeur de l'expression"));
    affichageValeurExpressionAction->setStatusTip(tr("&Afficher la valeur de l'expression"));
    connect(affichageValeurExpressionAction, &QAction::triggered, this, &FenetrePrincipale::afficherValeurExpression);

    affichageGraphique2DAction = new QAction(tr("&Afficher le graphique 2D"));
    affichageGraphique2DAction->setStatusTip(tr("&Afficher le graphique 2D de l'expression"));
    connect(affichageGraphique2DAction, &QAction::triggered, this, &FenetrePrincipale::affichageGraphique2D);

    affichageGraphique3DAction = new QAction(tr("&Affichager le graphique 3D"));
    affichageGraphique3DAction->setStatusTip(tr("&Afficher le graphique 3D de l'expression"));
    connect(affichageGraphique3DAction, &QAction::triggered, this, &FenetrePrincipale::affichageGraphique3D);

    simplificationExpressionAction = new QAction(tr("&Simplier l'expression"));
    simplificationExpressionAction->setStatusTip(tr("&Simplifier l'expression"));
    connect(simplificationExpressionAction, &QAction::triggered, this, &FenetrePrincipale::simplifierExpression);
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

void FenetrePrincipale::removeWidgetsFromLayout() {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}

void FenetrePrincipale::saisirExpression() {
    removeWidgetsFromLayout();
    calculatorView = new Calculator(widget);
    layout->addWidget(calculatorView);
    layout->update();
}

void FenetrePrincipale::afficherClassique() {
    removeWidgetsFromLayout();
    calculatorView = new Calculator(widget);
    layout->addWidget(calculatorView);
    layout->update();

    Data &data = Data::getInstance();
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    data.getExpression()->afficherNC();
    std::cout.rdbuf(prevcoutbuf);
    std::string result = buffer.str();
    calculatorView->editDisplay(result);
}

void FenetrePrincipale::afficherNPI() {
    removeWidgetsFromLayout();
    calculatorView = new Calculator(widget);
    layout->addWidget(calculatorView);
    layout->update();

    Data &data = Data::getInstance();
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    data.getExpression()->afficherNPI();
    std::cout.rdbuf(prevcoutbuf);
    std::string result = buffer.str();
    calculatorView->editDisplay(result);
}

void FenetrePrincipale::afficherValeurExpression() {
    removeWidgetsFromLayout();
    calculatorView = new Calculator(widget);
    layout->addWidget(calculatorView);
    layout->update();

    Data &data = Data::getInstance();
    calculatorView->editDisplay(data.getExpression()->calculer());
}

void FenetrePrincipale::simplifierExpression() {
    removeWidgetsFromLayout();
    calculatorView = new Calculator(widget);
    layout->addWidget(calculatorView);
    layout->update();

    Data &data = Data::getInstance();
    data.updateExpression(data.getExpression()->simplifier());
}


void FenetrePrincipale::affichageGraphique3D() {
    removeWidgetsFromLayout();
    graph3D = new Graph3DView(widget);
    layout->addWidget(graph3D);
    layout->update();
}

void FenetrePrincipale::chargerFichier() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir Fichier"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        // Afficher le chemin absolu du fichier sélectionné
        QMessageBox::information(this, tr("Chemin du fichier"), fileName);
    }
}
void FenetrePrincipale::affichageGraphique2D(){
    removeWidgetsFromLayout();
    g = new Graph2dView(widget);
    Graph2dController gController(Data::getInstance().getExpression(), Variable::construct('x',0), g);
    layout->addWidget(g);
    g->resize(800, 600);
    layout->update();
}
