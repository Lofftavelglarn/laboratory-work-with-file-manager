#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

qint64 calculateFolderSize(const QString &path) {
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

QMap<QString, qint64> calculateFolderSizes(const QString &path) {
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

void calculateFileTypeSizes(const QString &path, QMap<QString, qint64> &fileTypeSizes, qint64& totalSize) {
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

QMap<QString, qint64> calculateFileTypeSizes(const QString &path) {
    QMap<QString, qint64> fileTypeSizes;
    qint64 totalSize = 0;
    calculateFileTypeSizes(path, fileTypeSizes, totalSize);
    fileTypeSizes.insert("totalSize", totalSize);
    return fileTypeSizes;
}

enum Strategy {
    FolderSize,
    FileTypeSize
};

void executeStrategy(const QString &path, Strategy strategy) {
    switch (strategy) {
        case FolderSize: {
            QMap<QString, qint64> folderSizes = calculateFolderSizes(path);
            qint64 totalSize = folderSizes.value("totalSize");

            if (totalSize == 0) {
                qWarning() << "The directory is empty or does not exist or all files are zero-sized.";
                qDebug() << "(Current Directory)" << "size:" << 0 << "bytes, percentage:" << 0 << "%";
                return;
            }

            for (auto it = folderSizes.begin(); it != folderSizes.end(); ++it) {
                if (it.key() != "totalSize") {
                    double percentage = 100.0 * it.value() / totalSize;
                    qDebug() << it.key() << "size:" << it.value() << "bytes, percentage:" << percentage << "%";
                }
            }
            break;
        }
        case FileTypeSize: {
            QMap<QString, qint64> fileTypeSizes = calculateFileTypeSizes(path);
            qint64 totalSize = fileTypeSizes.value("totalSize");

            if (totalSize == 0) {
                qWarning() << "The directory is empty or does not exist or all files are zero-sized.";
                return;
            }

            for (auto it = fileTypeSizes.begin(); it != fileTypeSizes.end(); ++it) {
                if (it.key() != "totalSize") {
                    double percentage = 100.0 * it.value() / totalSize;
                    qDebug() <<  it.key() << "percentage:" << percentage << "%";
                }
            }
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString path = R"(D:\xd)";
    Strategy strategy = FolderSize;  // Выберите стратегию: FolderSize
                                     // или FileTypeSize

    executeStrategy(path, strategy);

    return a.exec();
}
