// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "calculator.h"
#include "button.h"
#include "../model/constante/Constante.h"
#include "../model/operations/addition/Addition.h"
#include "../model/operations/division/Division.h"
#include "../model/operations/multiplication/Multiplication.h"
#include "../model/operations/soustraction/Soustraction.h"
#include "../model/operations/puissance/Puissance.h"
#include "../model/operationsUnaire/absolue/Absolue.h"
#include "../model/operationsUnaire/carre/Carre.h"
#include "../model/operationsUnaire/inverse/Inverse.h"
#include "../model/operationsUnaire/logNeperien/Ln.h"
#include "../model/operationsUnaire/oppose/Oppose.h"
#include "../model/operationsUnaire/racine/Racine.h"
#include "../model/variable/Variable.h"

#include <QLineEdit>
#include <QtMath>
#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStack>

//! [0]
Calculator::Calculator(QWidget *parent)
        : QWidget(parent), sumSoFar(0.0), powerSoFar(0.0)
        , factorSoFar(0.0), waitingForOperand(true)
{

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(display, 0, 0, 1, 6);

//! [4]
    for (int i = 0; i < NumDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);

    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);

    Button *divisionButton = createButton(tr("\303\267"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);
    Button *squareRootButton = createButton(tr("Sqrt"), &Calculator::unaryOperatorClicked);
    Button *powerButton = createButton(tr("x\302\272y"), &Calculator::binaryOperatorClicked);
    Button *reciprocalButton = createButton(tr("1/x"), &Calculator::unaryOperatorClicked);
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);

    Button *absButton = createButton(tr("|x|"), &Calculator::unaryOperatorClicked);
    Button *squareButton = createButton(tr("x²"), &Calculator::unaryOperatorClicked);
    Button *lnButton = createButton(tr("ln(x)"), &Calculator::unaryOperatorClicked);
    Button *negateButton = createButton(tr("±x"), &Calculator::unaryOperatorClicked);
    Button *variableButtonx = createButton(tr("X"), &Calculator::variableClicked);
    Button *variableButtony = createButton(tr("Y"), &Calculator::variableClicked);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 3, 1, 2);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 3);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 4);

    mainLayout->addWidget(absButton, 2, 6);
    mainLayout->addWidget(squareButton, 3, 6);
    mainLayout->addWidget(lnButton, 4, 6);
    mainLayout->addWidget(negateButton, 5, 5);
    mainLayout->addWidget(variableButtonx, 1, 5);
    mainLayout->addWidget(variableButtony, 1, 6);

    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}



void Calculator::variableClicked() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Entrée de variable"),
                                         tr("Entrez le nom de la variable:"), QLineEdit::Normal,
                                         QString(), &ok);
    if (ok && !text.isEmpty()) {
        QChar variableName = text[0];
        if (!variableName.isLetter()) {
            QMessageBox::warning(this, tr("Erreur"), tr("Le nom de la variable doit être une lettre."));
            return;
        }

        qDebug() << "Nom de la variable entré:" << variableName;
        double value = QInputDialog::getDouble(this, tr("Valeur de la variable"),
                                               tr("Entrez la valeur de la variable %1:").arg(variableName),
                                               0, -2147483647, 2147483647, 2, &ok);
        if (ok) {
            qDebug() << "Construction de la variable:" << variableName << "avec la valeur:" << value;
            Variable* variable = Variable::construct(variableName.toLatin1(), value);
            handleVariableInput(variable); // Passer la variable à handleVariableInput
        } else {
            qDebug() << "L'utilisateur a annulé la saisie de la valeur de la variable.";
        }
    } else {
        qDebug() << "L'utilisateur a annulé la saisie du nom de la variable ou le nom est vide.";
    }
}

void Calculator::handleVariableInput(Variable *variable) {
    QString displayText = display->text();
    if (displayText == "0" || waitingForOperand) {
        display->clear();
    }
    display->setText(display->text() + QChar(variable->getName()));
    waitingForOperand = false;

    qDebug() << "Variable entrée dans l'affichage:" << QChar(variable->getName());
}

void Calculator::digitClicked() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedText = clickedButton->text();

    if (clickedText.at(0).isDigit()) {
        int digitValue = clickedText.toInt();
        Constante c1(digitValue);
        if (display->text() == "0" && c1.calculer() == 0.0)
            return;

        if (waitingForOperand) {
            display->clear();
            waitingForOperand = false;
        }
        display->setText(display->text() + QString::number(c1.calculer()));
    } else {
        //handleVariableInput(clickedText.at(0));
    }
}



void Calculator::binaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!pendingPowerOperator.isEmpty()) {
        if (!calculate(operand, pendingPowerOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(powerSoFar));
    } else {
        powerSoFar = operand;
    }
    pendingPowerOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::unaryOperatorClicked() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;

    QString clickedOperator = clickedButton->text();
    QString displayText = display->text();
    double operand = displayText.toDouble();
    QString result;

    QRegularExpression regex("[a-zA-Z]");

    if (clickedOperator == tr("|x|")) {
        if (displayText.contains(regex)) {
            result = "|" + displayText + "|";
        } else {
            Constante c1(operand);
            Absolue a1(&c1);
            result = QString::number(a1.calculer());
        }
    } else if (clickedOperator == tr("x²")) {
        if (displayText.contains(regex)) {
            result = "(" + displayText + ")²";
        } else {
            Constante c1(operand);
            Carre ca1(&c1);
            result = QString::number(ca1.calculer());
        }
    } else if (clickedOperator == tr("ln(x)")) {
        if (displayText.contains(regex)) {
            result = "ln(" + displayText + ")";
        } else {
            Constante c1(operand);
            Ln ln1(&c1);
            result = QString::number(ln1.calculer());
        }
    } else if (clickedOperator == tr("1/x")) {
        if (displayText.contains(regex)) {
            result = "1/(" + displayText + ")";
        } else {
            Constante c1(operand);
            Inverse in1(&c1);
            result = QString::number(in1.calculer());
        }
    } else if (clickedOperator == tr("Sqrt")) {
        if (displayText.contains(regex)) {
            result = "sqrt(" + displayText + ")";
        } else {
            Constante c1(operand);
            Racine ra1(&c1);
            result = QString::number(ra1.calculer());
        }
    } else if (clickedOperator == tr("±x")) {
        if (displayText.contains(regex)) {
            result = "-(" + displayText + ")";
        } else {
            Constante c1(operand);
            Oppose op1(&c1);
            result = QString::number(op1.calculer());
        }
    }

    display->setText(result);
    waitingForOperand = true;
}



void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}



void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}



bool Calculator::calculate(float rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        Constante c3(sumSoFar);
        Constante c4(rightOperand);
        Addition a1(&c3, &c4);
        sumSoFar = a1.calculer();
    } else if (pendingOperator == tr("-")) {
        Constante c3(sumSoFar);
        Constante c4(rightOperand);
        Soustraction s1(&c3, &c4);
        sumSoFar = s1.calculer();
    } else if (pendingOperator == tr("\303\227")) {
        Constante c3(factorSoFar);
        Constante c4(rightOperand);
        Multiplication m1(&c3, &c4);
        factorSoFar = m1.calculer();
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        Constante c3(factorSoFar);
        Constante c4(rightOperand);
        Division d1(&c4, &c3);
        factorSoFar = d1.calculer();
    }
    else if (pendingOperator == tr("x\302\272y")){
        Constante c3(powerSoFar);
        Constante c4(rightOperand);
        Puissance p1(&c3, &c4);
        powerSoFar = p1.calculer();
    }
    return true;
}



void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    if (!pendingPowerOperator.isEmpty()) {
        if (!calculate(operand, pendingPowerOperator)) {
            abortOperation();
            return;
        }
        operand = powerSoFar;
        powerSoFar = 0.0;
        pendingPowerOperator.clear();
    }

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}



void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}



void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}



void Calculator::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}



void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    powerSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    pendingPowerOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}



template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}



void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}




QGridLayout *Calculator::getLayout() {
    return mainLayout;
}
