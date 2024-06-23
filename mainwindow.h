#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QComboBox>
#include <QItemSelectionModel>
#include <memory>

#include "analysistablemodel.h"
#include "context.h"
#include "filetypesizestrategy.h"
#include "foldersizestrategy.h"
#include "barchart.h"
#include "piechart.h"
#include "barchartadapter.h"
#include "piechartadapter.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void on_strategyChangedSlot(const QString &strategyName);
    void on_viewModeChangedSlot(const QString &viewMode);

private:
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    std::unique_ptr<Context> context;
    AnalysisTableModel *analysisTableModel;
    QTableView *analysisTableView;
    QComboBox *strategyComboBox;
    QComboBox *viewModeComboBox;
    QSplitter *splitter;

    BarChart *barChart;
    PieChart *pieChart;
    BarChartAdapter *barChartAdapter;
    PieChartAdapter *pieChartAdapter;

    void setFolderSizeStrategy();
    void setFileTypeSizeStrategy();
    void setAnalysisStrategy(std::unique_ptr<IAnalyzerStrategy> strategy);

    void updateView(const QMap<QString, qint64> &data);
    QWidget *currentView;
};

#endif // MAINWINDOW_H
