#include "foldersizestrategy.h"

QMap<QString, qint64> FolderSizeStrategy::analyze(const QString &path) const  {
    return calculateFolderSizes(path);
}

qint64 FolderSizeStrategy::calculateFolderSize(const QString &path) const {
    qint64 size = 0;
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            size += calculateFolderSize(entry.absoluteFilePath());
        } else if (entry.isFile()) {
            size += entry.size();
        }
    }

    return size;
}

QMap<QString, qint64> FolderSizeStrategy::calculateFolderSizes(const QString &path) const {
    QMap<QString, qint64> folderSizes;
    qint64 currentDirectorySize = 0;
    qint64 totalSize = 0;

    QDir dir(path);

    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            qint64 subfolderSize = calculateFolderSize(entry.absoluteFilePath());
            if(subfolderSize){
                folderSizes.insert(entry.fileName(), subfolderSize);
                totalSize += subfolderSize;
            }
        } else if (entry.isFile()) {
            currentDirectorySize += entry.size();
            totalSize += entry.size();
        }
    }

    if(currentDirectorySize){
        folderSizes.insert("(CurrentDirectory)", currentDirectorySize);
    }
    folderSizes.insert("totalSize", totalSize);
    return folderSizes;
}
