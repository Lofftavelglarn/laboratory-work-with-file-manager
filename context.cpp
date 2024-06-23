#include "context.h"

QMap<QString, qint64> Context::executeStrategy(const QString &path) {
    if (strategy) {
        results = strategy->analyze(path);
    } else {
        qWarning() << "The strategy is not set!";
    }

    notifyObservers();
    return results;
}
