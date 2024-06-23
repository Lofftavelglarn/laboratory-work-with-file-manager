#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H

#include "context.h"
#include "piechart.h"
#include "contextobserver.h"

class PieChartAdapter : public ContextObserver {
public:
    explicit PieChartAdapter(PieChart *pieChart) : pieChart(pieChart) {}

    virtual void update(const QMap<QString, qint64> &data) override {
        pieChart->createChart(data);
    }

private:
    PieChart *pieChart;
};

#endif // PIECHARTADAPTER_H