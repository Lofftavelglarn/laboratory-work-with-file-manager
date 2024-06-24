#include "barchart.h"

void BarChart::drawChart(const QMap<QString, qreal> &data) {
    QBarSeries *series = new QBarSeries();

    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QBarSet *set = new QBarSet(it.key() + QString("\n") + QString::number(it.value(), 'f', 2) + QString("%"));
        *set << it.value();
        series->append(set);
    }

    chartView->chart()->addSeries(series);
}


void BarChart::drawLegend() {
    chartView->chart()->legend()->setVisible(true);
    chartView->chart()->legend()->setAlignment(Qt::AlignRight);
}
