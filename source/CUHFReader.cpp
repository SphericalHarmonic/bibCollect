#include "CUHFReader.h"

const QDateTime CUHFReader::ultraReferenceTime =
        QDateTime::fromString("1980-01-01T00:00:00 ", Qt::ISODate);


CUHFReader::CUHFReader(QString name, QObject* parent)
    :
    CAbstractReader(name, parent)
{
    m_readerType = UHF;

    m_tcpSocket = std::make_unique<QTcpSocket>(this);
    if (!QObject::connect(
            m_tcpSocket.get(), SIGNAL(connected()),
            this, SIGNAL(connected())))
    {
        throw QString("Invalid QObject connection (CUHFReader, connected())");
    }

    if (!QObject::connect(
            m_tcpSocket.get(), SIGNAL(disconnected()),
            this, SIGNAL(disconnected())))
    {
        throw QString("Invalid QObject connection (CUHFReader, disconnected())");
    }

    //QObject::connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(displayIncomingMessages()));

    /*stuff from versionchecker: Something similar to this can go into a function setUpStateMachine
     * connectState->addTransition(m_tcpSocket, SIGNAL(connected()), LOADState);
    connectState->addTransition(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), connectErrorState);
    QObject::connect(connectState, SIGNAL(entered()), this, SLOT(connect()));
    QObject::connect(connectErrorState, SIGNAL(entered()), this, SLOT(connectError()));
    machine->addState(LOADState);
    machine->addState(connectErrorState);

    LOADState->addTransition(this, SIGNAL(LOADsuccessful()), measurementState);
    LOADState->addTransition(this, SIGNAL(LOADfailed()), LOADErrorState);
    QObject::connect(LOADState, SIGNAL(entered()), this, SLOT(loadJobCommand()));
    QObject::connect(LOADErrorState, SIGNAL(entered()), this, SLOT(loadError()));
    machine->addState(measurementState);
    machine->addState(LOADErrorState);
    */

}

void CUHFReader::connect(QString ip, unsigned int port)
{
    setIp(ip);
    setPort(port);
    connect();
}

void CUHFReader::connect()
{
    disconnect();

    m_tcpSocket->connectToHost(m_ip, static_cast<qint16>(m_port));
}

void CUHFReader::disconnect()
{
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->waitForDisconnected();
}

bool CUHFReader::setClock()
{
    return false;
}

bool CUHFReader::start()
{
    return false;
}

bool CUHFReader::stop()
{
    return false;
}

void CUHFReader::readTagHistory()
{

}

QStringList CUHFReader::availableGatingModes()
{
    QStringList gatingModes;
    return gatingModes;
}

QStringList CUHFReader::availableTimingModes()
{
    QStringList timingModes;
    return timingModes;
}

void CUHFReader::setGatingMode(GatingMode gatingMode)
{
    m_gatingMode = gatingMode;
}

void CUHFReader::setTimingMode(TimingMode timingMode)
{
    m_timingMode = timingMode;
}

void CUHFReader::setUseBackupAntenna(bool useBackupAntenna)
{
    m_useBackupAntenna = useBackupAntenna;
}

void CUHFReader::readMessage(QString messageString)
{
    constexpr char LF = '\n';

    auto messages = messageString.split(LF);

    for (auto& message : messages)
    {
        //Chip read
        if (message.length() > 1
            && message[0] == '0'
            && message[1] == ',')
        {
            processChipRead(message);
        }

        //Connection established
        else if (message.contains("Connected"))
        {
            processConnectionEstablished(message);
        }

        //Voltage status
        else if(message.length() > 0
                && message[0] == 'V')
        {
            processVoltage(message);
        }

        //Setting acknowlegdement
        else if(message.length() > 0
                && message[0] == 'u')
        {
            settingAcknowledged(message);
        }

        //Receive Setting after settings query:
        else if(message.length() > 0
                && message[0] == 'U')
        {
            settingRequested(message);
        }


    }
}

void CUHFReader::processVoltage(QString message)
{
    const auto parts = message.trimmed().split('=');
    if (parts.length() < 2)
    {
        return;
    }

    bool validVoltage = false;
    const double voltage = parts[1].toDouble(&validVoltage);
    if (validVoltage)
    {
        //TODO:
        //emit the voltage value
        //refresh the reader connection timer
    }

    //TODO:
    //What should be done with invalid messages?
}



void CUHFReader::processChipRead(QString message)
{
    const auto chipData = parseChip(message);

    if (chipData.isValid)
    {
        emit tag(chipData.chipCode, chipData.timeStamp);
    }

    //TODO:
    //What should be done with invalid messages?
    //
}

CUHFReader::ChipData CUHFReader::parseChip(
    QString chip) const
{
    CUHFReader::ChipData chipData;
    const auto values = chip.trimmed().split(',');
    if (values.length() != 12)
    {
        return chipData;
    }

    bool validField;

    chipData.chipCode = values[1];
    chipData.timeStamp = parseChipTime(values[2], values[3], &validField);

    chipData.isValid = validField;

    //TODO: parse the other fields if needed.

    return chipData;
}

QDateTime CUHFReader::parseChipTime(
    QString seconds,
    QString milliseconds,
    bool* timeIsValid) const
{
    if (timeIsValid != nullptr)
    {
        *timeIsValid = false;
    }

    bool validSeconds = false;
    const int sec = seconds.toInt(&validSeconds);
    if (sec < 0)
    {
        validSeconds = false;
    }

    bool validMilliseconds;
    const int milli = milliseconds.toInt(&validMilliseconds);
    if (milli < 0 )
    {
        validMilliseconds = false;
    }

    QDateTime time;

    if (validMilliseconds && validMilliseconds)
    {
        if (timeIsValid != nullptr)
        {
            *timeIsValid = true;
        }
        time = chipTime(sec, milli);
    }

    return time;
}

QDateTime CUHFReader::chipTime(
    const int seconds,
    const int milliseconds) const
{
    return ultraReferenceTime.addMSecs(seconds*1000 + milliseconds);
}
