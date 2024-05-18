#include "context.h"

void Context::executeStrategy(const QString &path) {
    if (strategy == nullptr) {
        qWarning() << "Strategy not set.";
        return;
    }

    QMap<QString, qint64> results = strategy->analyze(path);
    qint64 totalSize = results.value("totalSize");

    if (totalSize == 0) {
        qWarning() << "The directory is empty or does not exist or all files are zero-sized.";
        return;
    }

    for (auto it = results.begin(); it != results.end(); ++it) {
        if (it.key() != "totalSize") {
            double percentage = 100.0 * it.value() / totalSize;
            qDebug() << it.key() << "size:" << it.value() << "bytes, percentage:" << percentage << "%";
        }
    }
}
