#include "CEvent.h"
#include "CReaderModel.h"
#include <QQmlApplicationEngine>

CEvent::CEvent(
    QQmlApplicationEngine* engine,
    CReaderModel* readerModel,
    QObject *parent)
    :
    m_engine(engine),
    m_readerModel(readerModel),
    QObject(parent)
{
    m_timedb = QSqlDatabase::addDatabase("QSQLITE");
    m_timedb.setHostName("localhost");
    m_timedb.setDatabaseName("C:/temp/demo.sqlite"); //this should be a property of the Event

    if (m_engine)
    {
        m_engine.rootContext()->setContextProperty("demosqlmodel", &m_resultModel);
    }
    if (m_timedb.open())
    {
        qDebug() << "Database open.";
        m_resultModel.setQuery("SELECT id, FirstName, LastName, YearOfBirth, strftime('%H:%M:%f', StartTime) as startTime, strftime('%H:%M:%f', NetStartTime) as netStartTime, strftime('%H:%M:%f', Time1) as time1, strftime('%H:%M:%f', Time2) as time2  FROM times");
    }
    else
    {
        qDebug() << "Unable to open database!";
    }
}
