#ifndef CONTEXT_H
#define CONTEXT_H

#include "ianalyzerstrategy.h"
#include <memory>

class Context {
public:
    void setStrategy(std::unique_ptr<IAnalyzerStrategy> strategy) {
        this->strategy = std::move(strategy);
    }

    QMap<QString, qint64> executeStrategy(const QString &path);

private:
    std::unique_ptr<IAnalyzerStrategy> strategy = nullptr;
};

#endif // CONTEXT_H
