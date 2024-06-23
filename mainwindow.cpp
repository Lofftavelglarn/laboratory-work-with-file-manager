#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStatusBar>
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
    treeView->hideColumn(1);

    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    analysisTableModel = new AnalysisTableModel(this);

    analysisTableView = new QTableView;
    analysisTableView->setModel(analysisTableModel);
    analysisTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    strategyComboBox = new QComboBox(this);
    strategyComboBox->addItem("Folder Size");
    strategyComboBox->addItem("File Type Size");
    connect(strategyComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_strategyChangedSlot);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(strategyComboBox);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(treeView);
    splitter->addWidget(analysisTableView);

    layout->addWidget(splitter);
    setCentralWidget(widget);

    QItemSelectionModel *selectionModel = treeView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_selectionChangedSlot);

    treeView->resizeColumnToContents(0);
    setFolderSizeStrategy();
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

        analysisTableModel->setAnalysisData(folderSizes);
    }

    treeView->resizeColumnToContents(0);
}

void MainWindow::setAnalysisStrategy(std::unique_ptr<IAnalyzerStrategy> strategy) {
    context->setStrategy(std::move(strategy));
}

void MainWindow::setFolderSizeStrategy() {
    setAnalysisStrategy(std::make_unique<FolderSizeStrategy>());
}

void MainWindow::setFileTypeSizeStrategy() {
    setAnalysisStrategy(std::make_unique<FileTypeSizeStrategy>());
}

void MainWindow::on_strategyChangedSlot(const QString &strategyName) {
    if (strategyName == "Folder Size") {
        setFolderSizeStrategy();
    } else if (strategyName == "File Type Size") {
        setFileTypeSizeStrategy();
    }
}
