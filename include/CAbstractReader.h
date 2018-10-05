#ifndef CABSTRACTREADER_H
#define CABSTRACTREADER_H

#include <QObject>
#include <QTime>

class CAbstractReader : public QObject
{
    Q_OBJECT

public:

    enum ReaderType
    {
        UHF,
        MF,
        LF
    };

    enum ReaderState
    {
        Disconnected,
        Connected,
        Running
    };


public:
    explicit CAbstractReader(QString name, QObject *parent = nullptr);
    ~CAbstractReader();

signals:
    void tag(QString, QTime);
    void statusMessage(QString);
    void connected(QString ip);
    void disconnected();
    void timeOut();
    void nameChanged(QString);

public:
    QString name() { return m_name; }
    ReaderState state() { return m_state; }
    ReaderType type() { return m_readerType; }
    virtual int batteryCharge() { return 0; }



public slots:
    virtual void connect() = 0;
    virtual void connect(QString ip, unsigned int port = 0) = 0;
    virtual void disconnect() = 0;
    virtual bool setClock() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual void readTagHistory() = 0;
    void setName(QString name) { m_name = name; }
    void setIp(QString ip) { m_ip = ip; }
    void setPort(unsigned int port) { m_port = port; }

protected:

    ReaderType m_readerType;
    ReaderState m_state;

    QString m_ip;
    unsigned int m_port;

    void increaseTagCount(const int tags)
    {
        m_tagCount += tags;
    }

private:
    QString m_name;
    unsigned int m_tagCount;
};

#endif // CABSTRACTTRIGGER_H
