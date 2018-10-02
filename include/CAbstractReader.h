#ifndef CABSTRACTREADER_H
#define CABSTRACTREADER_H

#include <QObject>

class CAbstractReader : public QObject
{
    Q_OBJECT

    /*enum ReaderType
    {
        R134kHz
    };*/


public:
    /*explicit */CAbstractReader(QObject *parent = nullptr);


signals:
    void tagReceived();
    void statusMessage();
    void connected();
    void disconnected();
    void error(QString);

public:
    //QString readerName()


public slots:
    /*virtual bool connect();
    virtual bool connect(QString ip, unsigned int port = 0);
    virtual bool disconnect();
    virtual bool setClock() = 0;*/

private:
    //std::shared_ptr<QThread> m_readerThread;
    QString m_readerName;
    //ReaderType m_readerType;
};

#endif // CABSTRACTREADER_H
