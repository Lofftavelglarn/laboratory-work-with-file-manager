#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QtCharts>

class Chart : public QWidget {
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr) : QWidget(parent), chartView(new QChartView(this)) {
        chartView->setRenderHint(QPainter::Antialiasing);
        auto layout = new QVBoxLayout(this);
        layout->addWidget(chartView);
        setLayout(layout);
    }

    virtual ~Chart() = default;

    void createChart(const QMap<QString, qreal> &data) {
        chartView->chart()->removeAllSeries();
        drawChart(data);
        drawLegend();
    }

protected:
    QChartView *chartView;

    virtual void drawChart(const QMap<QString, qreal> &data) = 0;
    virtual void drawLegend() = 0;
};

#endif // CHART_H
