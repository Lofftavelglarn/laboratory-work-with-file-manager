#include "piechart.h"

void PieChart::drawChart(const QMap<QString, qint64> &data) {
    QPieSeries *series = new QPieSeries();

    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        series->append(it.key(), it.value());
    }

    chartView->chart()->addSeries(series);
}

void PieChart::drawLegend()  {
    chartView->chart()->legend()->setVisible(true);
    chartView->chart()->legend()->setAlignment(Qt::AlignRight);
}
