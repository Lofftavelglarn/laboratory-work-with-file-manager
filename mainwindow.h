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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QTreeView *treeView;
    QTableView *tableView;
    std::unique_ptr<Context> context; // Используем умный указатель

    // Методы для выбора стратегии
    void setFolderSizeStrategy();
    void setFileTypeSizeStrategy();
};

#endif // MAINWINDOW_H
