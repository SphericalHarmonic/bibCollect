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
        Disconnected = 0,
        Connected,
        Running
    };

    enum GatingMode //??
    {
        None = 0,
        FirstTimeSeen
    };

    enum TimingMode //??
    {
        TimingOnStart = 0,
        TimingOnFinish
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
    QString name() const
    {
        return m_name;
    }
    ReaderState state() const
    {
        return m_state;
    }
    ReaderType type() const
    {
        return m_readerType;
    }
    virtual int batteryCharge() const
    {
        return 0;
    }

    virtual QStringList availableGatingModes() = 0;
    virtual int gatingMode() const
    {
        return m_gatingMode;
    }

    virtual QStringList availableTimingModes() = 0;
    virtual int timingMode() const
    {
        return m_timingMode;
    }

    virtual bool useBackupAntenna() const
    {
        return m_useBackupAntenna;
    }

    //virtual QStringList availableAntennas() = 0;
    //virtual QStringList timingMode() = 0;



public:
    virtual void connect() = 0;
    virtual void connect(QString ip, unsigned int port = 0) = 0;
    virtual void disconnect() = 0;
    virtual bool setClock() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual void readTagHistory() = 0;
    void setName(QString name) { m_name = name; }


    void setIp(QString ip) { m_ip = ip; }
    QString ip() const
    {
        return m_ip;
    }


    void setPort(unsigned int port) { m_port = port; }
    unsigned int port() const
    {
        return m_port;
    }

    virtual void setGatingMode(GatingMode gatingMode) = 0;
    virtual void setTimingMode(TimingMode timingMode) = 0;
    virtual void setUseBackupAntenna(bool useBackupAntenna) = 0;

    unsigned int tagCount() const
    {
        return m_tagCount;
    }

protected:

    ReaderType m_readerType;
    ReaderState m_state;

    QString m_ip;
    unsigned int m_port;

    void increaseTagCount(const unsigned int tags)
    {
        m_tagCount += tags;
    }

    GatingMode m_gatingMode;
    TimingMode m_timingMode;
    bool m_useBackupAntenna;

private:
    QString m_name;
    unsigned int m_tagCount;
};

#endif // CABSTRACTTRIGGER_H
