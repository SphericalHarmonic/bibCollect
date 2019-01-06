#include "CUHFReader.h"
#include "CReaderParser.h"

const int connectionTestTime = 11000; //11 seconds


CUHFReader::CUHFReader(QString name, QObject* parent)
    :
    CAbstractReader(name, parent)
{
    m_readerType = UHF;

    m_tcpSocket = std::make_unique<QTcpSocket>(this);
    /*if (!QObject::connect(
            m_tcpSocket.get(), SIGNAL(connected()),
            this, SLOT(handleConnected())))
    {
        throw QString("Invalid QObject connection (CUHFReader, connected())");
    }*/

    if (!QObject::connect(
            m_tcpSocket.get(), SIGNAL(disconnected()),
            this, SLOT(handleDisconnected())))
    {
        throw QString("Invalid QObject connection (CUHFReader, handleDisconnected())");
    }

    m_connectionTimer.setInterval(connectionTestTime);
    if (!QObject::connect(
            &m_connectionTimer, SIGNAL(timeout()),
            this, SLOT(readerTimeout())))
    {
        throw QString("Invalid QObject connection (CUHFReader, readerTimeout())");
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
    if (m_tcpSocket->state() != QAbstractSocket::UnconnectedState)
    {
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->waitForDisconnected(); //might fail under windows sometimes
    }
    m_tcpSocket->connectToHost(m_ip, static_cast<qint16>(m_port));
}




void CUHFReader::disconnect()
{
    if (m_state == Running)
    {
        stop();
    }
    m_tcpSocket->disconnectFromHost();
    //m_tcpSocket->waitForDisconnected();
}

void CUHFReader::handleDisconnected()
{
    m_state = Disconnected;
    emit disconnected();
}

void CUHFReader::readerTimeout()
{
    emit timeOut();
    //TODO: change state, reset connection...
}

bool CUHFReader::setClock()
{
    return false;
}

bool CUHFReader::start()
{
    m_tcpSocket->write("R");
    m_state = Running;
    emit readingStarted();
    return true;
}

bool CUHFReader::stop()
{
    m_tcpSocket->write("S");
    m_state = Connected;
    emit readingStopped();
    return true;
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

        emit batteryVoltage(voltage);
        //refresh the reader connection timer
        m_connectionTimer.
    }

    //TODO:
    //What should be done with invalid messages?
}



void CUHFReader::processChipRead(QString message)
{
    const auto chipData = CReaderParser::parseUltraChip(message);

    if (chipData.isValid)
    {
        emit tag(chipData.chipCode, chipData.timeStamp);
    }

    //TODO:
    //What should be done with invalid messages?
    //
}

void CUHFReader::processConnectionEstablished(QString message)
{
    Q_UNUSED(message)

    //do some state change
    m_state = Connected;

    emit connected();
}

