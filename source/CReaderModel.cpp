#include "CReaderModel.h"
#include "CUHFReader.h"


CReaderModel::CReaderModel()
    :
    m_currentIndex(-1)
{
    initializeReaderTypeList();
}

CReaderModel::~CReaderModel()
{
    for (auto& reader : m_readerList)
    {
        reader->disconnect();
    }
}

void CReaderModel::initializeReaderTypeList()
{
    m_readerTypeList = CAbstractReader::readerTypeList();
}

QStringList CReaderModel::readerTypes()
{
    return m_readerTypeList;
}

bool CReaderModel::addReader(
    CAbstractReader::ReaderType type,
    QString name)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    switch (type)
    {
    case CAbstractReader::UHF:
        m_readerList.push_back(std::make_unique<CUHFReader>(name, this));
        break;
    case CAbstractReader::MF: //TODO
        break;
    case CAbstractReader::LF: //TODO
        break;
    }
    endInsertRows();
    //TODO: Check for success or change return type to void
    return true;
}

bool CReaderModel::addReader(
    int type,
    QString name,
    QString address)
{
    if (type < 0)
    {
        return false;
    }

    bool added = addReader(static_cast<CAbstractReader::ReaderType>(type), name);
    if (added)
    {
        m_readerList.back()->setIp(address);
        QObject::connect(
            m_readerList.back().get(), SIGNAL(connected()),
            this, SLOT(notifyStateChange()));
        QObject::connect(
            m_readerList.back().get(), SIGNAL(readingStarted()),
            this, SLOT(notifyStateChange()));
        QObject::connect(
            m_readerList.back().get(), SIGNAL(readingStopped()),
            this, SLOT(notifyStateChange()));
        QObject::connect(
            m_readerList.back().get(), SIGNAL(disconnected()),
            this, SLOT(notifyStateChange()));
    }
    emit dataChanged(index(rowCount() -1), index(rowCount()-1));
    return added;
}

bool CReaderModel::addReader(std::unique_ptr<CAbstractReader> reader)
{
    //TODO
    return true;
}

void CReaderModel::setIp(
        const unsigned int row,
        const QString ip)
{
    if (static_cast<int>(row) >= rowCount() ||
        ip == m_readerList[row]->ip())
    {
        return;
    }

    m_readerList[row]->setIp(ip);
    emit dataChanged(index(row), index(row), {DeviceAdressRole});
}

void CReaderModel::setName(
        const unsigned int row,
        const QString name)
{
    if (static_cast<int>(row) >= rowCount() ||
        name == m_readerList[row]->name())
    {
        return;
    }

    m_readerList[row]->setName(name);
    emit dataChanged(index(row), index(row), {NameRole});
}



QHash<int, QByteArray> CReaderModel::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if (roles.empty())
    {
            roles[NameRole] = "readerName";
            roles[TypeRole] = "readerType";
            roles[TypeIndexRole] = "readerTypeIndex";
            roles[StateRole] = "readerState";
            roles[DeviceAdressRole] = "readerAddress";
            roles[BatteryRole] = "batteryCharge";
            roles[TagCountRole] = "tagCount";
            roles[GatingModeRole] = "gatingMode";
            roles[TimingModeRole] = "timingMode";
            roles[InUseRole] = "inUse";
    }
    return roles;
}

int CReaderModel::roleIndex(QString roleName)
{
    return roleNames().key(roleName.toUtf8());
}

int CReaderModel::rowCount(const QModelIndex & /*parent*/) const
{
   return static_cast<int>(m_readerList.size());
}

QVariant CReaderModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > rowCount() - 1)
    {
        return QVariant();
    }

    const auto& reader = m_readerList[static_cast<unsigned int>(index.row())];

    switch (role) {
    case NameRole:
        return reader->name();
    case TypeRole:
        switch (reader->type())
        {
        case CAbstractReader::UHF:
            return QString("UHF");
        default:
            return QString("unbekannt");
        }
    case TypeIndexRole:
        return static_cast<int>(reader->type());
    case StateRole:
        qDebug() << "readerState: " << static_cast<int>(reader->state());
        return static_cast<int>(reader->state());
    case DeviceAdressRole:
        return QString("%1:%2").arg(reader->ip()).arg(reader->port());
    case BatteryRole:
        return reader->batteryCharge();
    case TagCountRole:
        return reader->tagCount();
    case GatingModeRole:
        return reader->gatingMode();
    case TimingModeRole:
        return reader->timingMode();
    case InUseRole:
        return !reader->suspended();
    default:
        return QVariant();
    }

}

QVariant CReaderModel::data(const int row, int role)
{
    return data(index(row), role);
}

QVariantMap CReaderModel::getRow(int idx) const
{
    QVariantMap map;
    const auto roleNames = this->roleNames();

    for (auto i = roleNames.begin(); i != roleNames.end(); ++i)
    {
        map[*i] = data(index(idx, 0), i.key());
    }
    return map;
}

void CReaderModel::startReader(const unsigned int row)
{
    m_readerList[row]->start();
}

void CReaderModel::connectReader(const unsigned int row)
{
    m_readerList[row]->connect();
}

int CReaderModel::indexOfReader(CAbstractReader* readerToFind)
{
    int index = -1;
    for (size_t i = 0; i < m_readerList.size(); i++)
    {
        if (m_readerList[i]->name() == readerToFind->name()
         && m_readerList[i]->ip() == readerToFind->ip())
        {
            index = static_cast<int>(i);
            break;
        }
    }
    return index;
}

void CReaderModel::notifyStateChange()
{
    qDebug() << "notifyStateChange";
    auto sender = qobject_cast<CAbstractReader*>(QObject::sender());
    const auto row = indexOfReader(sender);
    if (row >= 0 && row < static_cast<int>(m_readerList.size()))
    {
        emit dataChanged(index(row), index(row));
    }
}
