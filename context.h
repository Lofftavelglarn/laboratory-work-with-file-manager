#ifndef CONTEXT_H
#define CONTEXT_H

#include "ianalyzerstrategy.h"
#include "contextobserver.h"
#include <memory>

class Context {
public:
    void setStrategy(std::unique_ptr<IAnalyzerStrategy> strategy) {
        this->strategy = std::move(strategy);
    }

    QMap<QString, qint64> executeStrategy(const QString &path);

    void addObserver(ContextObserver *observer) {
        observers.push_back(observer);
    }

private:
    std::unique_ptr<IAnalyzerStrategy> strategy = nullptr;
    QMap<QString, qint64> results;
    std::vector<ContextObserver* > observers;

    void notifyObservers() {
        for (auto observer : observers) {
            observer->update(results);
        }
    }
};

#endif // CONTEXT_H
