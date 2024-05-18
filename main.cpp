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

    context.setStrategy(&folderSizeStrategy);
    context.executeStrategy(path);

    context.setStrategy(&fileTypeSizeStrategy);
    context.executeStrategy(path);

    return a.exec();
}
