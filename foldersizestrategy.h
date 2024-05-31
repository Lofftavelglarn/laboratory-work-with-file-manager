#ifndef FOLDERSIZESTRATEGY_H
#define FOLDERSIZESTRATEGY_H

#include "ianalyzerstrategy.h"

class FolderSizeStrategy : public IAnalyzerStrategy {
public:
    QMap<QString, qint64> analyze(const QString &path) const override;

private:
    qint64 calculateFolderSize(const QString &path) const;

    QMap<QString, qint64> calculateFolderSizes(const QString &path) const;
};

#endif // FOLDERSIZESTRATEGY_H
