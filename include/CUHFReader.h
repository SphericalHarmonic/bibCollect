#ifndef CUHFREADER_H
#define CUHFREADER_H

#include <memory>

//#include <QObject>
#include <QStateMachine>
#include <QTcpSocket>
#include <CAbstractReader.h>

class CUHFReader : public CAbstractReader
{
    Q_OBJECT

signals:
    void tag(QString, QTime);
    void statusMessage(QString);
   // void connected();
   // void disconnected();
    void timeOut();
    void nameChanged(QString);

public:
    CUHFReader(QString name, QObject *parent = nullptr);

public slots:
    void connect();
    void connect(QString ip, unsigned int port = 0);
    void disconnect();
    bool setClock();
    bool start();
    bool stop();
    void readTagHistory();

    virtual QStringList availableGatingModes();

    virtual QStringList availableTimingModes();

    virtual bool useBackupAntenna() { return m_useBackupAntenna; }

    virtual void setGatingMode(GatingMode gatingMode);

    virtual void setTimingMode(TimingMode timingMode);

    virtual void setUseBackupAntenna(bool useBackupAntenna);

private:
    std::unique_ptr<QTcpSocket> m_tcpSocket;
    QStateMachine m_stateMachine;

private slots:
    void readMessage(QString message);



};

#endif // CUHFREADER_H
