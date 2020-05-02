#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include <CReaderModel.h>
#include "QtSql/QSqlDatabase"
#include "QtSql/qsqltablemodel.h"
#include "resultsqlmodel.h"
#include <qdebug.h>
#include "cclassictiming.h"
#include <QSettings>
#include "CEvent.h"

static bool createConnection()
{




    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("SpringerSport");
    QCoreApplication::setOrganizationDomain("springer-sport.de");
    QCoreApplication::setApplicationName("bibCollect");

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    QSettings settings;
    {

    }

    CReaderModel readerModel;
    engine.rootContext()->setContextProperty("readerModel", &readerModel);

    CEvent eventManager(&engine, &readerModel);
    engine.rootContext()->setContextProperty("event", &eventManager);

    //createConnection();
    //database test
    /*QSqlDatabase timedb = QSqlDatabase::addDatabase("QSQLITE");
       timedb.setHostName("localhost");
       timedb.setDatabaseName("C:/temp/demo.sqlite"); //this should be a property of the Event
       //timedb.setUserName("");
       //timedb.setPassword("");
    if (timedb.open())
    {
        qDebug() << "Database open.";
    }
    else
    {
        qDebug() << "Unable to open database!";
    }*/

    /*ResultSqlModel qmodel;
    qmodel.setQuery("SELECT id, FirstName, LastName, YearOfBirth, strftime('%H:%M:%f', StartTime) as startTime, strftime('%H:%M:%f', NetStartTime) as netStartTime, strftime('%H:%M:%f', Time1) as time1, strftime('%H:%M:%f', Time2) as time2  FROM times");
    engine.rootContext()->setContextProperty("demosqlmodel", &qmodel);*/

    /*QSqlTableModel timeTableModel(nullptr, timedb); //-> this should be a property of the Event
    CClassicTiming timing(&timeTableModel); //-> this should be a property of the Event
    QList<int> testIds{1004};
    timing.start(testIds, QDateTime::currentDateTimeUtc());*/
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
