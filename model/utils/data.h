#ifndef QTPROJECT_DATA_H
#define QTPROJECT_DATA_H

#include <functional>
#include <vector>
#include "../expression/Expression.h"

class ISubscriber {
public:
    virtual ~ISubscriber() = default;
    virtual void update() = 0;
};

class Data {
public:
    static Data& getInstance();

    void subscribe(ISubscriber* subscriber);
    void unsubscribe(ISubscriber* subscriber);
    void updateExpression(Expression* newExpression);
    Expression* getExpression() const;

private:
    Data();
    Data(const Data&) = delete;
    Data& operator=(const Data&) = delete;

    Expression* expression;
    std::vector<ISubscriber*> subscribers;
};

class Subscriber : public ISubscriber{
public:
    Subscriber() {
        Data::getInstance().subscribe(this);
    }

    ~Subscriber() override {
        Data::getInstance().unsubscribe(this);
        //make log on destruction
        std::cout << "Subscriber destroyed" << std::endl;
    }

    virtual void update() = 0;

protected:
    void subscribe() {
        Data::getInstance().subscribe(this);
    }

    void unsubscribe() {
        Data::getInstance().unsubscribe(this);
    }
};

#endif //QTPROJECT_DATA_H