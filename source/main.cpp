#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include <CReaderModel.h>
#include "QtSql/QSqlDatabase"
#include "resultsqlmodel.h"
#include <qdebug.h>

static bool createConnection()
{

    //database test
    QSqlDatabase timedb = QSqlDatabase::addDatabase("QSQLITE");
       timedb.setHostName("localhost");
       timedb.setDatabaseName("C:/temp/demo.sqlite");
       //timedb.setUserName("");
       //timedb.setPassword("");
    if (timedb.open())
    {
        qDebug() << "Database opened!";
        return true;
    }
    else
    {
        qDebug() << "Database not opened!";
        return false;
    }


    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    CReaderModel readerModel;
    engine.rootContext()->setContextProperty("readerModel", &readerModel);



    createConnection();
    ResultSqlModel qmodel;
    qmodel.setQuery("SELECT id, FirstName, LastName, YearOfBirth, strftime('%H:%M:%f', StartTime) as startTime, strftime('%H:%M:%f', NetStartTime) as netStartTime, strftime('%H:%M:%f', Time1) as time1, strftime('%H:%M:%f', Time2) as time2  FROM times");
    engine.rootContext()->setContextProperty("demosqlmodel", &qmodel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
