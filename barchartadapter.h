#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H

#include "context.h"
#include "barchart.h"
#include "contextobserver.h"

class BarChartAdapter : public ContextObserver {
public:
    explicit BarChartAdapter(BarChart *barChart) : barChart(barChart) {}

    void update(const QMap<QString, qint64> &data) override {
        QMap<QString, qreal> dataPercent = makePercent(data);
        barChart->createChart(dataPercent);
    }

    BarChart* getChart(){
        return barChart;
    }

private:
    BarChart *barChart;
};

#endif // BARCHARTADAPTER_H
