#include "cclassictiming.h"
#include "qsqltablemodel.h"

CClassicTiming::CClassicTiming(
    QSqlTableModel* tableModel,
    QObject *parent)
    :
    CAbstractTiming(tableModel, parent)
{

}

void CClassicTiming::start(QList<int>& ids, QDateTime time)
{

}

void CClassicTiming::triggerTag(QString& source, QString tag, QDateTime time)
{

}

void CClassicTiming::triggerId(QString& source, int id, QDateTime time)
{

}
