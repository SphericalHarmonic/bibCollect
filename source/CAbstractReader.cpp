#include "CAbstractReader.h"

CAbstractReader::CAbstractReader(
    QString name,
    QObject *parent)
    :
    QObject(parent),
    m_ip(""),
    m_port(0),
    m_gatingMode(None),
    m_timingMode(TimingOnFinish),
    m_useBackupAntenna(false),
    m_name(name),
    m_tagCount(0),
    m_suspended(false)
{

}

CAbstractReader::~CAbstractReader()
{

}



