#ifndef CONTEXTOBSERVER_H
#define CONTEXTOBSERVER_H

#include <QObject>

class ContextObserver{
public:
    virtual ~ContextObserver() {}

    virtual void update(const QMap<QString, qint64> &data) = 0;
};

#endif // CONTEXTOBSERVER_H
