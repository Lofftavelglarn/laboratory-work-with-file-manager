#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H

#include "context.h"
#include "piechart.h"
#include "contextobserver.h"

class PieChartAdapter : public ContextObserver {
public:
    explicit PieChartAdapter(PieChart *pieChart) : pieChart(pieChart) {}

    void update(const QMap<QString, qint64> &data) override {
        QMap<QString, qreal> dataPercent = makePercent(data);
        pieChart->createChart(dataPercent);
    }

    PieChart* getChart(){
        return pieChart;
    }

private:
    PieChart *pieChart;
};

#endif // PIECHARTADAPTER_H
