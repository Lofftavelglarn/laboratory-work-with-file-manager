#ifndef BARCHART_H
#define BARCHART_H

#include "chart.h"
#include <QtCharts>

class BarChart : public Chart {
    Q_OBJECT

public:
    explicit BarChart(QWidget *parent = nullptr) : Chart(parent) {}

    virtual void drawChart(const QMap<QString, qint64> &data) override;

    virtual void drawLegend() override;
};

#endif // BARCHART_H
