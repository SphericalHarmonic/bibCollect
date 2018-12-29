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

    static const QDateTime ultraReferenceTime;

    struct ChipData {
        QString chipCode;
        QDateTime timeStamp;
        int antennaNo;
        double signalStrength;
        bool isRewind;
        int readerNo;
        int ultraID;
        QDateTime startTime;
        int logID;

        bool isValid;
        ChipData()
        {
            isValid = false;
            antennaNo = -1;
            signalStrength = 0;
            isRewind = false;
            readerNo = -1;
            ultraID = -1;
            logID = -1;
        }
    };


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

private:
    QDateTime chipTime(
        const int seconds,
        const int milliseconds) const;
    QDateTime parseChipTime(
        QString seconds,
        QString milliseconds,
        bool* timeIsValid = nullptr) const;
    ChipData parseChip(QString chip) const;
    void processChipRead(QString message);
    void processConnectionEstablished(QString message);
    void processVoltage(QString message);
    void settingAcknowledged(QString message);
    void settingRequested(QString message);

};

#endif // CUHFREADER_H
