#ifndef FILETYPESIZESTRATEGY_H
#define FILETYPESIZESTRATEGY_H

#include "ianalyzerstrategy.h"

class FileTypeSizeStrategy : public IAnalyzerStrategy {
public:
    QMap<QString, qint64> analyze(const QString &path) const override;

private:
    void calculateFileTypeSizes(const QString &path, QMap<QString, qint64> &fileTypeSizes, qint64& totalSize) const;
};

#endif // FILETYPESIZESTRATEGY_H
