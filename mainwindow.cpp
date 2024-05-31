#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), context(std::make_unique<Context>())
{
    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Choosen Path: ");
    QString homePath = QDir::homePath();

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(homePath);

    treeView = new QTreeView();
    treeView->setModel(dirModel);
    treeView->expandAll();

    QSplitter *splitter = new QSplitter(this);
    tableView = new QTableView;
    tableView->setModel(fileModel);

    splitter->addWidget(treeView);
    splitter->addWidget(tableView);
    setCentralWidget(splitter);

    QItemSelectionModel *selectionModel = treeView->selectionModel();
    QModelIndex indexHomePath = dirModel->index(homePath);
    QFileInfo fileInfo = dirModel->fileInfo(indexHomePath);

    treeView->header()->resizeSection(0, 200);
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_selectionChangedSlot);

    QItemSelection toggleSelection;
    QModelIndex topLeft;
    topLeft = dirModel->index(homePath);
    dirModel->setRootPath(homePath);

    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);

    // Устанавливаем начальную стратегию
    setFolderSizeStrategy();
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QModelIndexList indexes = selected.indexes();
    QString filePath = "";

    if (indexes.count() >= 1) {
        QModelIndex ix = indexes.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Choosen Path: " + filePath);

        QMap<QString, qint64> folderSizes = context->executeStrategy(filePath);
        if(folderSizes.empty()){
            qWarning() << "The strategy is not set!";
        } else {
            qint64 totalSize = 0;
            qint64 otherSize = 0;
            int alpha = 0;

            for (auto it = folderSizes.begin(); it != folderSizes.end(); ++it) {
                if (it.value() < alpha) {
                    otherSize += it.value();
                    folderSizes.erase(it);
                }
                totalSize += it.value();
            }
            if(otherSize) {
                folderSizes.insert("otherSize", otherSize);
            }

            if(!totalSize){
                qWarning() << "The directory is empty or does not exist or all files are zero-sized.";
                qDebug() << "(Current Directory)" << "size:" << 0 << "bytes, percentage:" << 0 << "%";
            } else {
                for (auto it = folderSizes.begin(); it != folderSizes.end(); ++it) {
                    double percentage = 100.0 * it.value() / totalSize;
                    qDebug() << it.key() << "size:" << it.value() << "bytes, percentage:" << percentage << "%";
                }
            }
        }
    }
    int length = 200;
    int dx = 30;

    if (dirModel->fileName(index).length() * dx > length) {
        length = length + dirModel->fileName(index).length() * dx;
        qDebug() << "r = " << index.row() << "c = " << index.column() << dirModel->fileName(index) << dirModel->fileInfo(index).size();
    }

    treeView->header()->resizeSection(index.column(), length + dirModel->fileName(index).length());
    tableView->setRootIndex(fileModel->setRootPath(filePath));
}

void MainWindow::setFolderSizeStrategy() {
    context->setStrategy(std::make_unique<FolderSizeStrategy>());
}

void MainWindow::setFileTypeSizeStrategy() {
    context->setStrategy(std::make_unique<FileTypeSizeStrategy>());
}
