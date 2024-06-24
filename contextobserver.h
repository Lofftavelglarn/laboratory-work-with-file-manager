#ifndef CONTEXTOBSERVER_H
#define CONTEXTOBSERVER_H

#include <QObject>
#include <QMap>

class ContextObserver{
public:
    virtual ~ContextObserver() {}

    virtual void update(const QMap<QString, qint64> &data) = 0;

    virtual QMap<QString, qreal> makePercent(const QMap<QString, qint64> &data) {
        QMap<QString, qreal> result;
        qint64 totalSize = 0;

        for (auto it = data.begin(); it != data.end(); ++it) {
            totalSize += it.value();
        }

        qreal otherSize = 0;
        bool otherExist = false;

        if(totalSize > 0){
            for (auto it = data.begin(); it != data.end(); ++it) {
                qreal percent = (static_cast<qreal>(it.value()) / totalSize) * 100;

                if (percent < 1.0) {
                    otherSize += it.value();
                    otherExist = true;
                } else {
                    result.insert(it.key(), percent);
                }
            }
        } else return result;

        if (otherExist) {
            result.insert("others", (otherSize / totalSize) * 100);
        }
        return result;
    }
};

#endif // CONTEXTOBSERVER_H
