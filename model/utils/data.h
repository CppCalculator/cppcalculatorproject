#ifndef QTPROJECT_DATA_H
#define QTPROJECT_DATA_H

#include <functional>
#include <vector>
#include "../expression/Expression.h"

class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void update() = 0;
};

class Data {
public:
    static Data& getInstance();

    void subscribe(Subscriber* subscriber);
    void unsubscribe(Subscriber* subscriber);
    void updateExpression(Expression* newExpression);
    Expression* getExpression() const;

private:
    Data();
    Data(const Data&) = delete;
    Data& operator=(const Data&) = delete;

    Expression* expression;
    std::vector<Subscriber*> subscribers;
};

#endif //QTPROJECT_DATA_H