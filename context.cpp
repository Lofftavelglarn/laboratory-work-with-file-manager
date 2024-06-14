#include "context.h"

QMap<QString, qint64> Context::executeStrategy(const QString &path) {
    QMap<QString, qint64> results;

    if (strategy) {
        results = strategy->analyze(path);
    } else {
        qWarning() << "The strategy is not set!";
    }

    return results;
}
