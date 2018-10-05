#include "CAbstractReader.h"

CAbstractReader::CAbstractReader(
    QString name,
    QObject *parent)
    :
    QObject(parent),
    m_name(name),
    m_tagCount(0)
{

}

CAbstractReader::~CAbstractReader()
{

}



