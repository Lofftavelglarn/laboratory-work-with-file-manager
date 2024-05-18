#include "context.h"

QMap<QString, qint64> Context::executeStrategy(const QString &path) {
    QMap<QString, qint64> results;

    if (strategy == nullptr) {
        return results;
    }

    results = strategy->analyze(path);

    return results;
}
