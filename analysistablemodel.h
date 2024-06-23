#ifndef ANALYSISTABLEMODEL_H
#define ANALYSISTABLEMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QVariant>
#include <QList>

class AnalysisTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    AnalysisTableModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    void setAnalysisData(const QMap<QString, qint64> &data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QMap<QString, qint64> analysisData;
    qint64 totalSize = 0;
    bool otherExist = false;
    qint64 otherSize = 0;

    void calculateTotalSize();

    void calculateOthers();
};

#endif // ANALYSISTABLEMODEL_H
