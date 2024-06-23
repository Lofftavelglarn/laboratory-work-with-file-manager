#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), context(std::make_unique<Context>()),
      analysisTableModel(new AnalysisTableModel(this)), splitter(new QSplitter(this)),
      barChart(new BarChart(this)), pieChart(new PieChart(this)), barChartAdapter(new BarChartAdapter(barChart)), pieChartAdapter(new PieChartAdapter(pieChart)), currentView(nullptr)
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

    analysisTableView = new QTableView;
    analysisTableView->setModel(analysisTableModel);
    analysisTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    strategyComboBox = new QComboBox(this);
    strategyComboBox->addItem("Folder Size");
    strategyComboBox->addItem("File Type Size");
    connect(strategyComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_strategyChangedSlot);

    viewModeComboBox = new QComboBox(this);
    viewModeComboBox->addItem("Table");
    viewModeComboBox->addItem("Bar Chart");
    viewModeComboBox->addItem("Pie Chart");
    connect(viewModeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_viewModeChangedSlot);

    context->addObserver(barChartAdapter);
    context->addObserver(pieChartAdapter);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(strategyComboBox);
    layout->addWidget(viewModeComboBox);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);

    splitter->addWidget(treeView);
    splitter->addWidget(analysisTableView);

    layout->addWidget(splitter);

    setCentralWidget(widget);

    QItemSelectionModel *selectionModel = treeView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_selectionChangedSlot);

    treeView->resizeColumnToContents(0);
    setFolderSizeStrategy();
    on_viewModeChangedSlot("Table");
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);
    QModelIndexList indexes = selected.indexes();
    QString filePath = "";

    if (indexes.count() >= 1) {
        QModelIndex ix = indexes.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Chosen Path: " + filePath);

        QMap<QString, qint64> analysisResults = context->executeStrategy(filePath);
        //updateView(analysisResults);
        analysisTableModel->setAnalysisData(analysisResults);
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

void MainWindow::on_viewModeChangedSlot(const QString &viewMode) {
    QWidget *newView = nullptr;

    if (viewMode == "Table") {
        newView = analysisTableView;
        if (currentView != analysisTableView) {
            analysisTableView->show();
            barChart->hide();
            pieChart->hide();
        }
    } else if (viewMode == "Bar Chart") {
        newView = barChart;
        if (currentView != barChart) {
            analysisTableView->hide();
            barChart->show();
            pieChart->hide();
        }
    } else if (viewMode == "Pie Chart") {
        newView = pieChart;
        if (currentView != pieChart) {
            analysisTableView->hide();
            barChart->hide();
            pieChart->show();
        }
    }

    if (newView && newView != currentView) {
        splitter->replaceWidget(1, newView);
        currentView = newView;
    }
}

/*void MainWindow::updateView(const QMap<QString, qint64> &data) {
    if (currentView == analysisTableView) {
        analysisTableModel->setAnalysisData(data);
    } else if (currentView == barChart) {
        barChartAdapter->update(data);
    } else if (currentView == pieChart) {
        pieChartAdapter->update(data);
    }
}*/
