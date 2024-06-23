#include "barchart.h"

void BarChart::drawChart(const QMap<QString, qint64> &data) {
    QBarSeries *series = new QBarSeries();

    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QBarSet *set = new QBarSet(it.key());
        *set << it.value();
        series->append(set);
    }

    chartView->chart()->addSeries(series);

    QStringList categories;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        categories << it.key();
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Size");
    chartView->chart()->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void BarChart::drawLegend() {
    chartView->chart()->legend()->setVisible(true);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
}
