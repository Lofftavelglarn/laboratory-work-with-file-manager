#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "context.h"
#include "filetypesizestrategy.h"
#include "foldersizestrategy.h"
#include <memory>
#include <QStandardItemModel>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setAnalysisStrategy(std::unique_ptr<IAnalyzerStrategy> strategy);

private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    std::unique_ptr<Context> context;
    QStandardItemModel *analysisModel;
    QTableView *analysisTableView;
};

#endif // MAINWINDOW_H
