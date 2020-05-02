#ifndef CPROJECT_H
#define CPROJECT_H

#include <QObject>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlTableModel"
#include "resultsqlmodel.h"
#include "cabstracttiming.h"
#include <qdebug.h>
#include <qfileinfo.h>

class CReaderModel;
class QQmlApplicationEngine;

class CEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString eventName READ name WRITE setName NOTIFY eventNameChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString path READ path NOTIFY pathChanged)

public:
    explicit CEvent(
        QQmlApplicationEngine* engine,
        CReaderModel* readerModel,
        QObject *parent = nullptr);

    QString name()
    {
        return m_name;
    }
    void setName(QString name)
    {
        if (name != m_name)
        {
            m_name = name;
            emit eventNameChanged(m_name);
        }
    }

    QString fileName()
    {
        return m_fileName;
    }
    void setFileName(QString fileName)
    {
        if (fileName != m_fileName)
        {
            m_fileName = fileName;
            emit fileNameChanged(m_fileName);

            QFileInfo dir(m_fileName);
            setPath(dir.path());
        }
    }

    QString path()
    {
        return m_path;
    }
    void setPath(QString path)
    {
        if (path != m_path)
        {
            m_path = path;
            emit pathChanged(m_path);
        }
    }

    Q_INVOKABLE
    bool loadFromFile(const QString& fileName)
    {
        //TODO: implement loading from file
        qDebug() << "loadFromFile() not implemented";
        m_fileName = fileName;
        return false;
    }

    Q_INVOKABLE
    bool save();

    Q_INVOKABLE
    bool saveToFile(const QString& fileName)
    {
        setFileName(fileName);

        if (m_name.isEmpty())
        {
            QFileInfo file(fileName);
            const auto name = file.baseName();
            setName(name);
        }

        return save();
    }

signals:
    void eventNameChanged(const QString& newName);
    void fileNameChanged(const QString& newName);
    void pathChanged(const QString& newPath);

private:
    //members which are saved to file
    QString m_name;
    QString m_fileName;
    QString m_path;
    QString m_timeDatabaseName;
    QString m_tagDatabaseName;

    //Database components
    QSqlDatabase m_timedb;
    ResultSqlModel m_resultModel;
    std::shared_ptr<QSqlTableModel> m_timeTableModel;
    std::shared_ptr<CAbstractTiming> m_timing;

    //other application modules
    QQmlApplicationEngine* m_engine;
    CReaderModel* m_readerModel;

};

#endif // CPROJECT_H
