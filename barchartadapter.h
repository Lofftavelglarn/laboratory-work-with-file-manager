#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H

#include "context.h"
#include "barchart.h"
#include "contextobserver.h"

class BarChartAdapter : public ContextObserver {
public:
    explicit BarChartAdapter(BarChart *barChart) : barChart(barChart) {}

    virtual void update(const QMap<QString, qint64> &data) override {
        barChart->createChart(data);
    }

private:
    BarChart *barChart;
};

#endif // BARCHARTADAPTER_H
