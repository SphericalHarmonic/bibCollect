#include "CEvent.h"
#include "CReaderModel.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qdebug.h"
#include "cclassictiming.h"
#include <qfile.h>
#include <QXmlStreamWriter>

CEvent::CEvent(
    QQmlApplicationEngine* engine,
    CReaderModel* readerModel,
    QObject *parent)
    :
    QObject(parent),
    m_hasFixedRounds(true),
    m_engine(engine),
    m_readerModel(readerModel)
{
    //TODO: For all of the following steps, single functions should be written. Also, every step has to be checked before the next one!

    m_timedb = QSqlDatabase::addDatabase("QSQLITE");
    m_timedb.setHostName("localhost");
    m_timedb.setDatabaseName("C:/temp/demo.sqlite"); //this should be a property of the Event

    if (m_engine)
    {
        m_engine->rootContext()->setContextProperty("demosqlmodel", &m_resultModel);
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

    m_timeTableModel = std::make_shared<QSqlTableModel>(this, m_timedb);
    m_timing = std::make_shared<CClassicTiming>(m_timeTableModel.get());
}

bool CEvent::save()
{
    //TODO: implement saving to file
    qDebug() << "save() not completely implemented";

    QFile file(m_fileName);
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();

            stream.writeTextElement("eventname", m_name);
            stream.writeTextElement("fixedRounds", QString("%1").arg(m_hasFixedRounds));

        stream.writeEndDocument();

        return true;
    }
    else
    {
        return false;
    }
}
