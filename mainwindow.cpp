#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), context(std::make_unique<Context>())
{
    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Chosen Path: ");
    QString homePath = QDir::homePath();

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    treeView = new QTreeView();
    treeView->setModel(dirModel);
    treeView->expandAll();

    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    analysisModel = new QStandardItemModel(this);
    analysisModel->setHorizontalHeaderLabels(QStringList() << "Name" << "Size" << "Percentage");

    analysisTableView = new QTableView;
    analysisTableView->setModel(analysisModel);
    analysisTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(treeView);
    splitter->addWidget(analysisTableView);

    setCentralWidget(splitter);

    QItemSelectionModel *selectionModel = treeView->selectionModel();

    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_selectionChangedSlot);

    treeView->resizeColumnToContents(0);
}

void MainWindow::setAnalysisStrategy(std::unique_ptr<IAnalyzerStrategy> strategy) {
    context->setStrategy(std::move(strategy));
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);
    QModelIndexList indexes = selected.indexes();
    QString filePath = "";

    if (indexes.count() >= 1) {
        QModelIndex ix = indexes.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Chosen Path: " + filePath);

        QMap<QString, qint64> folderSizes = context->executeStrategy(filePath);
        if (folderSizes.empty()) {
            qWarning() << "The strategy is not set!";
        } else {
            analysisModel->clear();

            qint64 totalSize = 0;

            for (auto it = folderSizes.begin(); it != folderSizes.end(); ++it) {
                totalSize += it.value();
            }

            bool otherExist = false;
            qint64 otherSize = 0;
            const double alpha = 1.0;

            QList<QString> otherFolders;

            if(totalSize){
                for (auto it = folderSizes.begin(); it != folderSizes.end(); ++it) {
                    if(it.key() != "(CurrentDirectory)"){
                        double percentage = 100.0 * it.value() / totalSize;
                        if (percentage < alpha) {
                            otherFolders.append(it.key());
                            otherSize += it.value();
                            otherExist = true;
                        }
                    }
                }
            }

            if (otherExist) {
                folderSizes.insert("Other dirs", otherSize);
                for (const QString &key : otherFolders) {
                    folderSizes.remove(key);
                }
            }

            for (auto it = folderSizes.begin(); it != folderSizes.end(); ++it) {
                QList<QStandardItem *> rowItems;
                double percentage = (totalSize == 0) ? 0.0 : (100.0 * it.value() / totalSize);
                rowItems << new QStandardItem(it.key())
                         << new QStandardItem(QString::number(it.value()))
                         << new QStandardItem(QString::number(percentage, 'f', 2) + "%");
                analysisModel->appendRow(rowItems);
            }
        }
    }

    treeView->resizeColumnToContents(0);
}
