// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "calculator.h"
#include "button.h"
#include "../model/constante/Constante.h"
#include "../model/operations/addition/Addition.h"
//#include "operations/Operation.h"
#include "../model/operations/division/Division.h"
#include "../model/operations/multiplication/Multiplication.h"
#include "../model/operations/soustraction/Soustraction.h"
//#include "expression/Expression.h"

#include <QLineEdit>
#include <QtMath>

//! [0]
Calculator::Calculator(QWidget *parent)
    : QWidget(parent), sumInMemory(0.0), sumSoFar(0.0)
    , factorSoFar(0.0), waitingForOperand(true)
{
//! [0]

//! [1]
    display = new QLineEdit("0");
//! [1] //! [2]
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
//! [2]

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(display, 0, 0, 1, 6);

//! [4]
    for (int i = 0; i < NumDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);

    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
    Button *changeSignButton = createButton(tr("\302\261"), &Calculator::changeSignClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);

    Button *divisionButton = createButton(tr("\303\267"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);
//! [4]

//! [6]
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);
    mainLayout->addWidget(equalButton, 5, 5);
}
//! [6]

//! [7]
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    Constante c1(digitValue);
    if (display->text() == "0" && c1.calculer() == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(c1.calculer()));
}
//! [7]

//! [8]
void Calculator::unaryOperatorClicked()
//! [8] //! [9]
{
    /*Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;*/
}
//! [9]

//! [10]
void Calculator::additiveOperatorClicked()
//! [10] //! [11]
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
      return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();


//! [11] //! [12]
    if (!pendingMultiplicativeOperator.isEmpty()) {
//! [12] //! [13]
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

//! [13] //! [14]
    if (!pendingAdditiveOperator.isEmpty()) {
//! [14] //! [15]
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

//! [15] //! [16]
    pendingAdditiveOperator = clickedOperator;
//! [16] //! [17]
    waitingForOperand = true;
}
//! [17]

//! [18]
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
//! [18]

//! [20]
void Calculator::equalClicked()
{
    double operand = display->text().toDouble();

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
//! [20]

//! [22]
void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}
//! [22]

//! [24]
void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}
//! [24]

//! [26]
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
//! [26]

//! [28]
void Calculator::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}
//! [28]

//! [30]
void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}
//! [30]

//! [32]
void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}
//! [32]
//! [34]
template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}
//! [34]

//! [36]
void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}
//! [36]

//! [38]
bool Calculator::calculate(float rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        Constante c3(sumSoFar);
        Constante c4(rightOperand);
        Addition a1(&c3, &c4);
        sumSoFar = a1.calculer();
        //sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        Constante c3(sumSoFar);
        Constante c4(rightOperand);
        Soustraction s1(&c3, &c4);
        sumSoFar = s1.calculer();
        //sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        Constante c3(factorSoFar);
        Constante c4(rightOperand);
        Multiplication m1(&c3, &c4);
        factorSoFar = m1.calculer();
        //factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        Constante c3(factorSoFar);
        Constante c4(rightOperand);
        Division d1(&c4, &c3);
        factorSoFar = d1.calculer();
        //factorSoFar /= rightOperand;
    }
    return true;
}
//! [38]

QGridLayout *Calculator::getLayout() {
    return mainLayout;
}
