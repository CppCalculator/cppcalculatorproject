#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QGridLayout>
#include <QWidget>
#include <iostream>
#include <vector>
#include "../model/Expression/Expression.h"
#include "../model/variable/Variable.h"


QT_BEGIN_NAMESPACE

class QLineEdit;

QT_END_NAMESPACE

class Button;

class Calculator : public QWidget {

Q_OBJECT



public:
    Calculator(QWidget *parent = nullptr);
    QGridLayout *getLayout();
    void editDisplay(float expression);
    void editDisplay(std::string expression);

private slots:

    void digitClicked();
    void binaryOperatorClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void variableClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void spaceClicked();


private:
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    void abortOperation();
    void updateDisplay();
    bool calculate(float rightOperand, const QString &pendingOperator);
    void handleVariableInput(Variable *variable);
    std::unique_ptr<Expression> parseExpression(const std::vector<QString> &tokens);

    std::vector<QString> expression; // Store the full expression
    QString currentNumber; // Store the current number being entered
    double evaluateExpression(const QString &expression);
    float sumSoFar;
    float factorSoFar;
    float powerSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    QString pendingPowerOperator;
    bool waitingForOperand;
    QLineEdit *display;
    QGridLayout *mainLayout = new QGridLayout;
    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
};

#endif