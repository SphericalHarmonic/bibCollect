#ifndef CABSTRACTREADER_H
#define CABSTRACTREADER_H

#include <QObject>
#include <QTime>

class CAbstractReader : public QObject
{
    Q_OBJECT

    enum ReaderType
    {
        UHF,
        R134kHz,
        LF
    };

    enum ReaderStatus
    {
        Disconnected,
        Connected,
        Running
    };


public:
    explicit CAbstractReader(QObject *parent = nullptr);
    ~CAbstractReader();

signals:
    void tag(QString, QTime);
    void statusMessage(QString);
    void connected(QString ip);
    void disconnected();
    void timeOut();

public:
    QString name() { return m_name; };


public slots:
    virtual bool connect() = 0;
    virtual bool connect(QString ip, unsigned int port = 0) = 0;
    virtual bool disconnect() = 0;
    virtual bool setClock() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

private:
    QString m_name;
    ReaderType m_readerType;
    ReaderStatus m_status;
};

#endif // CABSTRACTREADER_H
