#include "analysistablemodel.h"

void AnalysisTableModel::setAnalysisData(const QMap<QString, qint64> &data) {
    beginResetModel();
    analysisData = data;
    calculateTotalSize();
    calculateOthers();
    endResetModel();
}

int AnalysisTableModel::rowCount(const QModelIndex &parent) const  {
    Q_UNUSED(parent);
    return analysisData.size() + (otherExist ? 1 : 0);
}

int AnalysisTableModel::columnCount(const QModelIndex &parent) const  {
    Q_UNUSED(parent);
    return 3;
}

QVariant AnalysisTableModel::data(const QModelIndex &index, int role) const  {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    auto it = analysisData.constBegin();
    std::advance(it, index.row());

    if (otherExist && index.row() == analysisData.size()) {
        switch (index.column()) {
            case 0:
                return "others";
            case 1:
                return otherSize;
            case 2:
                if (totalSize > 0) {
                    double percentage = 100.0 * otherSize / totalSize;
                    return QString::number(percentage, 'f', 2) + "%";
                }
                return QString("0.00%");
            default:
                return QVariant();
        }
    }

    switch (index.column()) {
        case 0:
            return it.key();
        case 1:
            return it.value();
        case 2:
            if (totalSize > 0) {
                double percentage = 100.0 * it.value() / totalSize;
                return QString::number(percentage, 'f', 2) + "%";
            }
            return QString("0.00%");
        default:
            return QVariant();
    }
}

QVariant AnalysisTableModel::headerData(int section, Qt::Orientation orientation, int role) const  {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
        case 0:
            return QString("Name");
        case 1:
            return QString("Size");
        case 2:
            return QString("Percentage");
        default:
            return QVariant();
    }
}

void AnalysisTableModel::calculateTotalSize() {
    totalSize = 0;
    for (auto it = analysisData.begin(); it != analysisData.end(); ++it) {
        totalSize += it.value();
    }
}

void AnalysisTableModel::calculateOthers() {
    otherExist = false;
    otherSize = 0;

    const double alpha = 1.0;
    if (totalSize > 0) {
        for (auto it = analysisData.begin(); it != analysisData.end();) {
            double percentage = 100.0 * it.value() / totalSize;
            if (percentage < alpha) {
                otherSize += it.value();
                otherExist = true;
                it = analysisData.erase(it);
            } else {
                ++it;
            }
        }
    }
}
