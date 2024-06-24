#ifndef PIECHART_H
#define PIECHART_H

#include "chart.h"
#include <QtCharts>

class PieChart : public Chart {
    Q_OBJECT

public:
    explicit PieChart(QWidget *parent = nullptr) : Chart(parent) {}

    virtual void drawChart(const QMap<QString, qreal> &data) override;
    virtual void drawLegend() override;
};

#endif // PIECHART_H
