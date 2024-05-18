#ifndef IANALYZERSTRATEGY_H
#define IANALYZERSTRATEGY_H

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>
#include <QMap>

class IAnalyzerStrategy {
public:
    virtual QMap<QString, qint64> analyze(const QString &path) const = 0;
    virtual ~IAnalyzerStrategy() = default;
};

#endif // IANALYZERSTRATEGY_H
