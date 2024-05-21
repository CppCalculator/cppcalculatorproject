#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QGridLayout>
#include <QWidget>
#include "../model/variable/Variable.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    QGridLayout *getLayout();

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


private:
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    void abortOperation();
    bool calculate(float rightOperand, const QString &pendingOperator);
    void handleVariableInput(Variable *variable);
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
