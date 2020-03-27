#ifndef CCLASSICTIMING_H
#define CCLASSICTIMING_H

#include "cabstracttiming.h"

class CClassicTiming : public CAbstractTiming
{
public:
    explicit CClassicTiming(
        QSqlTableModel* tableModel,
        QObject *parent = nullptr);

//inherited slots:
    void start(QList<int>& ids, QDateTime time) override;
    void triggerTag(QString& source, QString tag, QDateTime time) override;
    void triggerId(QString& source, int id, QDateTime time) override;
};

#endif // CCLASSICTIMING_H
