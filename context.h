#ifndef CONTEXT_H
#define CONTEXT_H

#include "ianalyzerstrategy.h"
class Context {
public:
    void setStrategy(IAnalyzerStrategy* strategy) {
        this->strategy = strategy;
    }

    void executeStrategy(const QString &path);

private:
    IAnalyzerStrategy* strategy = nullptr;
};

#endif // CONTEXT_H
