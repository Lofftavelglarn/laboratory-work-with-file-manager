#include "context.h"
#include "filetypesizestrategy.h"
#include "foldersizestrategy.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString path = R"(C:\Users\makar\repos\laboratory-work-with-file-manager\test)";

    FolderSizeStrategy folderSizeStrategy;
    FileTypeSizeStrategy fileTypeSizeStrategy;

    Context context;

    context.setStrategy(&folderSizeStrategy); //folderSizeStrategy или fileTypeSizeStrategy
    QMap<QString, qint64> results = context.executeStrategy(path);
    if(results.empty()){
        qWarning() << "The strategy is not set!";
    } else {
        qint64 totalSize = 0;
        qint64 otherSize = 0;
        int alpha = 0;

        for (auto it = results.begin(); it != results.end(); ++it) {
            if (it.value() < alpha) {
                otherSize += it.value();
                results.erase(it);
            }
            totalSize += it.value();
        }
        if(otherSize) {
            results.insert("otherSize", otherSize);
        }

        if(!totalSize){
            qWarning() << "The directory is empty or does not exist or all files are zero-sized.";
            qDebug() << "(Current Directory)" << "size:" << 0 << "bytes, percentage:" << 0 << "%";
        } else {
            for (auto it = results.begin(); it != results.end(); ++it) {
                double percentage = 100.0 * it.value() / totalSize;
                qDebug() << it.key() << "size:" << it.value() << "bytes, percentage:" << percentage << "%";
            }
        }
    }
    return a.exec();
}
