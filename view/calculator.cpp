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
#include "../model/utils/Data.h"
#include <QLineEdit>
#include <QtMath>
#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStack>
#include <stack>
#include <memory>
//! [0]

Calculator::Calculator(QWidget *parent)

        : QWidget(parent), sumSoFar(0.0), powerSoFar(0.0), factorSoFar(0.0), waitingForOperand(true) {

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    mainLayout = new QGridLayout(this);
    for (int i = 0; i < NumDigitButtons; ++i)

        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);
    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);
    Button *divisionButton = createButton(tr("÷"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("×"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);
    Button *squareRootButton = createButton(tr("Sqrt"), &Calculator::unaryOperatorClicked);
    Button *powerButton = createButton(tr("x^y"), &Calculator::binaryOperatorClicked);
    Button *reciprocalButton = createButton(tr("1/x"), &Calculator::unaryOperatorClicked);
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);
    Button *absButton = createButton(tr("|x|"), &Calculator::unaryOperatorClicked);
    Button *squareButton = createButton(tr("x²"), &Calculator::unaryOperatorClicked);
    Button *lnButton = createButton(tr("ln(x)"), &Calculator::unaryOperatorClicked);
    Button *negateButton = createButton(tr("±x"), &Calculator::unaryOperatorClicked);
    Button *variableButtonx = createButton(tr("X"), &Calculator::variableClicked);
    Button *variableButtony = createButton(tr("Y"), &Calculator::variableClicked);
    Button *spaceButton = createButton(tr(" "), &Calculator::spaceClicked);
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
    mainLayout->addWidget(spaceButton, 5, 0); // Add space button

}
void Calculator::updateDisplay() {

    QString displayText;
    for (const auto &token: expression) {

        displayText += token + " ";
    }

    display->setText(displayText.trimmed());
}
void Calculator::variableClicked() {

    bool ok;
    QString text = QInputDialog::getText(this, tr("Entrée de variable"), tr("Entrez le nom de la variable:"),
                                         QLineEdit::Normal, QString(), &ok);
    if (ok && !text.isEmpty()) {

        QChar variableName = text[0];
        if (!variableName.isLetter()) {

            QMessageBox::warning(this, tr("Erreur"), tr("Le nom de la variable doit être une lettre."));
            return;
        }

        qDebug() << "Nom de la variable entré:" << variableName;
        double value = QInputDialog::getDouble(this, tr("Valeur de la variable"),
                                               tr("Entrez la valeur de la variable %1:").arg(variableName), 0,
                                               -2147483647, 2147483647, 2, &ok);
        if (ok) {

            qDebug() << "Construction de la variable:" << variableName << "avec la valeur:" << value;
            Variable *variable = Variable::construct(variableName.toLatin1(), value);
            handleVariableInput(variable); // Passer la variable à handleVariableInput

        } else {

            qDebug() << "L'utilisateur a annulé la saisie de la valeur de la variable.";
        }

    } else {

        qDebug() << "L'utilisateur a annulé la saisie du nom de la variable ou le nom est vide.";
    }

}
void Calculator::handleVariableInput(Variable *variable) {

    expression.push_back(QChar(variable->getName()));
    updateDisplay();
    waitingForOperand = false;
    qDebug() << "Variable entrée dans l'affichage:" << QChar(variable->getName());
}
void Calculator::digitClicked() {

    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedText = clickedButton->text();
    if (clickedText.at(0).isDigit()) {

        if (waitingForOperand) {

            currentNumber.clear();
            waitingForOperand = false;
        }

        currentNumber += clickedText;
        display->setText(currentNumber);
    }

}
void Calculator::binaryOperatorClicked() {

    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)

        return;
    QString clickedOperator = clickedButton->text();
    if (!currentNumber.isEmpty()) {

        expression.push_back(currentNumber);
        currentNumber.clear();
    }

    expression.push_back(clickedOperator);
    updateDisplay();
    waitingForOperand = true;
}
void Calculator::unaryOperatorClicked() {

    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)

        return;
    QString clickedOperator = clickedButton->text();
    if (!currentNumber.isEmpty()) {

        expression.push_back(currentNumber);
        currentNumber.clear();
    }

    expression.push_back(clickedOperator);
    updateDisplay();
    waitingForOperand = true;
}
void Calculator::multiplicativeOperatorClicked() {

    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)

        return;
    QString clickedOperator = clickedButton->text();
    if (!currentNumber.isEmpty()) {

        expression.push_back(currentNumber);
        currentNumber.clear();
    }

    expression.push_back(clickedOperator);
    updateDisplay();
    waitingForOperand = true;
}
void Calculator::additiveOperatorClicked() {

    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)

        return;
    QString clickedOperator = clickedButton->text();
    if (!currentNumber.isEmpty()) {

        expression.push_back(currentNumber);
        currentNumber.clear();
    }

    expression.push_back(clickedOperator);
    updateDisplay();
    waitingForOperand = true;
}
void Calculator::spaceClicked() {

    if (!currentNumber.isEmpty()) {

        expression.push_back(currentNumber);
        currentNumber.clear();
    }

    expression.push_back(" ");
    updateDisplay();
}
std::unique_ptr<Expression> Calculator::parseExpression(const std::vector<QString> &tokens) {

    std::stack<std::unique_ptr<Expression>> stack;
    for (const auto &token: tokens) {

        if (token.trimmed().isEmpty()) {

            continue; // Skip spaces

        }
        qDebug() << "Processing token:" << token;
        if (token == "+") {

            if (stack.size() < 2) {

                qDebug() << "Error: Not enough operands for addition";
                return nullptr;
            }

            auto right = std::move(stack.top());
            stack.pop();
            auto left = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Addition>(left.release(), right.release()));
        } else if (token == "-") {

            if (stack.size() < 2) {

                qDebug() << "Error: Not enough operands for subtraction";
                return nullptr;
            }

            auto right = std::move(stack.top());
            stack.pop();
            auto left = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Soustraction>(left.release(), right.release()));
        } else if (token == "×") {

            if (stack.size() < 2) {

                qDebug() << "Error: Not enough operands for multiplication";
                return nullptr;
            }

            auto right = std::move(stack.top());
            stack.pop();
            auto left = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Multiplication>(left.release(), right.release()));
        } else if (token == "÷") {

            if (stack.size() < 2) {

                qDebug() << "Error: Not enough operands for division";
                return nullptr;
            }

            auto right = std::move(stack.top());
            stack.pop();
            auto left = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Division>(left.release(), right.release()));
        } else if (token == "x^y") {

            if (stack.size() < 2) {

                qDebug() << "Error: Not enough operands for power";
                return nullptr;
            }

            auto right = std::move(stack.top());
            stack.pop();
            auto left = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Puissance>(left.release(), right.release()));
        } else if (token == "|x|") {

            if (stack.empty()) {

                qDebug() << "Error: Not enough operands for absolute";
                return nullptr;
            }

            auto operand = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Absolue>(operand.release()));
        } else if (token == "x²") {

            if (stack.empty()) {
                qDebug() << "Error: Not enough operands for square";
                return nullptr;
            }

            auto operand = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Carre>(operand.release()));
        } else if (token == "ln(x)") {
            if (stack.empty()) {
                qDebug() << "Error: Not enough operands for natural log";
                return nullptr;
            }

            auto operand = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Ln>(operand.release()));
        } else if (token == "1/x") {

            if (stack.empty()) {

                qDebug() << "Error: Not enough operands for reciprocal";
                return nullptr;
            }

            auto operand = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Inverse>(operand.release()));
        } else if (token == "Sqrt") {

            if (stack.empty()) {

                qDebug() << "Error: Not enough operands for square root";
                return nullptr;
            }

            auto operand = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Racine>(operand.release()));
        } else if (token == "±x") {

            if (stack.empty()) {

                qDebug() << "Error: Not enough operands for negate";
                return nullptr;
            }

            auto operand = std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<Oppose>(operand.release()));
        } else if (token.at(0).isDigit()) {

            stack.push(std::make_unique<Constante>(token.toFloat()));
        } else if (token.at(0).isLetter()) {

            stack.push(
                    std::unique_ptr<Variable>(Variable::construct(token.at(0).toLatin1()))); // Use Variable::construct

        }

    }
    if (stack.size() != 1) {

        qDebug() << "Error: Invalid expression";
        return nullptr;
    }
    return std::move(stack.top());
}
void Calculator::equalClicked() {
    if (!currentNumber.isEmpty()) {
        expression.push_back(currentNumber);
        currentNumber.clear();
    }
    auto expressionObject = parseExpression(expression);
    if (expressionObject) {
        Data::getInstance().updateExpression(expressionObject.release());
        updateDisplay();
    } else {
        qDebug() << "Error: Failed to parse expression";
        display->setText("Error");
    }
}

void Calculator::pointClicked() {
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}
void Calculator::backspaceClicked() {
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
void Calculator::clear() {
    if (waitingForOperand)
        return;
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll() {
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    powerSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    pendingPowerOperator.clear();
    expression.clear();
    currentNumber.clear();
    display->setText("0");
    waitingForOperand = true;
}

template<typename PointerToMemberFunction>

Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member) {
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

void Calculator::abortOperation() {
    clearAll();
    display->setText(tr("####"));
}

QGridLayout *Calculator::getLayout() {
    return mainLayout;
}

void Calculator::editDisplay(float expression) {
    std::cout << "Inside editDisplay with float const as parameter" << std::endl;
    char buffer[64];
    int ret = snprintf(buffer, sizeof buffer, "%f", expression);
    std::cout << ret << std::endl;
    std::cout << sizeof(buffer) << std::endl;
    if (ret == sizeof(buffer)) {
        display->setText(tr(buffer));
    }
}

void Calculator::editDisplay(std::string expression) {
    std::cout << "Inside editDisplay with string const as parameter" << std::endl;
    display->setText(expression.c_str());
}