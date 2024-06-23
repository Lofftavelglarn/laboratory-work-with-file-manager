#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "analysistablemodel.h"
#include "context.h"
#include "filetypesizestrategy.h"
#include "foldersizestrategy.h"
#include <QComboBox>
#include <memory>
#include <QStandardItemModel>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void on_strategyChangedSlot(const QString &strategyName);

private:
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    std::unique_ptr<Context> context;
    AnalysisTableModel *analysisTableModel;
    QTableView *analysisTableView;
    QComboBox *strategyComboBox;

    void setFolderSizeStrategy();
    void setFileTypeSizeStrategy();
    void setAnalysisStrategy(std::unique_ptr<IAnalyzerStrategy> strategy);
};

#endif // MAINWINDOW_H
