#ifndef QTPROJECT_EXAMPLESUBSCRIBER_H
#define QTPROJECT_EXAMPLESUBSCRIBER_H

#include "data.h"

class ExampleSubscriber : public Subscriber {
public:
    ExampleSubscriber() {
        // init your function
    }
    void update() override {
        // Do something when the expression is updated
        printf("\nExpression updated\n");
    }
};
#endif //QTPROJECT_EXAMPLESUBSCRIBER_H
