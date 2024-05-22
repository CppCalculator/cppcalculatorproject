#include "data.h"

// Get the singleton instance
Data& Data::getInstance() {
    static Data instance;
    return instance;
}

// Subscribe a class to be notified when the expression is updated
void Data::subscribe(ISubscriber* subscriber) {
    subscribers.push_back(subscriber);
}

// Unsubscribe a class
void Data::unsubscribe(ISubscriber* subscriber) {
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

// Update the expression and notify the subscribers
void Data::updateExpression(Expression* newExpression) {
    expression = newExpression;
    for (auto& subscriber : subscribers) {
        subscriber->update();
    }
}

// Get the current expression
Expression* Data::getExpression() const {
    return expression;
}

// Private constructor for singleton
Data::Data() : expression(nullptr) {}
