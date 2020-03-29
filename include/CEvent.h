#ifndef CPROJECT_H
#define CPROJECT_H

#include <QObject>

class CEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString eventName READ name WRITE setName NOTIFY eventNameChanged)

public:
    explicit CEvent(QObject *parent = nullptr);

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

    Q_INVOKABLE
    bool loadFromFile(const QString& fileName)
    {
        //TODO: implement loading from file
        Q_UNUSED(fileName)
        return false;
    }

signals:
    void eventNameChanged(const QString& newName);

private:
    QString m_name;

};

#endif // CPROJECT_H
