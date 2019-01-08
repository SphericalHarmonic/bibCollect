#ifndef CUHFREADER_H
#define CUHFREADER_H

#include <memory>

//#include <QObject>
#include <QStateMachine>
#include <QTcpSocket>
#include <CAbstractReader.h>
#include <qtimer.h>

class CUHFReader : public CAbstractReader
{
    Q_OBJECT

    static const QDateTime ultraReferenceTime;


public:
    CUHFReader(QString name, QObject *parent = nullptr);

public slots:
    void connect() override;
    void connect(QString ip, unsigned int port = 0) override;
    void disconnect() override;
    bool setClock() override;
    bool start() override;
    bool stop() override;
    void readTagHistory() override;

    QStringList availableGatingModes() override;

    QStringList availableTimingModes() override;

    bool useBackupAntenna() { return m_useBackupAntenna; }
    void setGatingMode(GatingMode gatingMode) override;
    void setTimingMode(TimingMode timingMode) override;
    void setUseBackupAntenna(bool useBackupAntenna) override;

private:
    std::unique_ptr<QTcpSocket> m_tcpSocket;
    QStateMachine m_stateMachine;
    QTimer m_testConnectionTimer;
    QTimer m_establishConnectionTimer;

private slots:
    void readMessage();
    void handleDisconnected();
    void handleConnected();
    void readerTimeout();

private:

    void processChipRead(QString message);
    void processConnectionEstablished(QString message);
    void processVoltage(QString message);
    void settingAcknowledged(QString message){}
    void settingRequested(QString message){}

};

#endif // CUHFREADER_H
