#include "CUHFReader.h"

CUHFReader::CUHFReader(QString name, QObject* parent)
    :
    CAbstractReader(name, parent)
{
    m_readerType = UHF;

    m_tcpSocket = new QTcpSocket(this);
    if (!QObject::connect(
            m_tcpSocket, SIGNAL(connected()),
            this, SIGNAL(connected())))
    {
        throw QString("Invalid QObject connection (CUHFReader, connected())");
    }

    if (!QObject::connect(
            m_tcpSocket, SIGNAL(disconnected()),
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
