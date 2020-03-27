#include "cclassictiming.h"
#include "qsqltablemodel.h"
#include "qsqlrecord.h"

#include "qdebug.h"


CClassicTiming::CClassicTiming(
    QSqlTableModel* tableModel,
    QObject *parent)
    :
    CAbstractTiming(tableModel, parent)
{
    m_times->setTable("times");
    m_times->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void CClassicTiming::start(QList<int>& ids, QDateTime time)
{
    for (const auto& id : ids)
    {
        m_times->setFilter(QString("ID=%1").arg(id));
        m_times->select();
        if (m_times->rowCount() == 1)
        {
            auto record = m_times->record(0);
            if (record.value("StartTime").toString() == "")
            {
                record.setValue("StartTime", time.toString(timeFormat()));
                m_times->setRecord(0, record);
            }
        }
        else
        {
            //TODO: invalid ID (Phantom)
        }
    }
    m_times->submitAll();
}

void CClassicTiming::triggerTag(QString& source, QString tag, QDateTime time)
{

}

void CClassicTiming::triggerId(QString& source, int id, QDateTime time)
{

}
