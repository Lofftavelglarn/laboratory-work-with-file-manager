#include "filetypesizestrategy.h"

QMap<QString, qint64> FileTypeSizeStrategy::analyze(const QString &path) const {
    QMap<QString, qint64> fileTypeSizes;
    qint64 totalSize = 0;
    calculateFileTypeSizes(path, fileTypeSizes, totalSize);
    fileTypeSizes.insert("totalSize", totalSize);
    return fileTypeSizes;
}

void FileTypeSizeStrategy::calculateFileTypeSizes(const QString &path, QMap<QString, qint64> &fileTypeSizes, qint64& totalSize) const {
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            calculateFileTypeSizes(entry.absoluteFilePath(), fileTypeSizes, totalSize);
        } else if (entry.isFile()) {
            QString extension = entry.suffix();
            if (fileTypeSizes.contains(extension)) {
                fileTypeSizes[extension] += entry.size();
            } else {
                fileTypeSizes[extension] = entry.size();
            }
            totalSize += entry.size();
        }
    }
}
