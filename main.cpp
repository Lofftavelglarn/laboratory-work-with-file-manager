#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::unique_ptr<IAnalyzerStrategy> strategy;
    strategy = std::make_unique<FolderSizeStrategy>();
    MainWindow w;
    w.setAnalysisStrategy(std::move(strategy));
    w.show();
    return a.exec();
}
