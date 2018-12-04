#include "CReaderModel.h"
#include "CUHFReader.h"


CReaderModel::CReaderModel()
    :
    m_currentIndex(-1)
{
    initializeReaderTypeList();
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
    beginResetModel();

    switch (type)
    {
    case CAbstractReader::UHF:
        //auto newReader = std::make_unique<CUHFReader>(name, this);
        m_readerList.push_back(std::make_unique<CUHFReader>(name, this));
        break;
    case CAbstractReader::MF: //TODO
        break;
    case CAbstractReader::LF: //TODO
        break;
    }
    endResetModel();
    //TODO: Check for success or change return type to void
    return true;
}

bool CReaderModel::addReader(
    int type,
    QString name,
    QString address)
{
    bool added = addReader(static_cast<CAbstractReader::ReaderType>(type), name);
    if (added)
    {
        m_readerList.back()->setIp(address);
    }
    return added;
}

bool CReaderModel::addReader(std::unique_ptr<CAbstractReader> reader)
{
    //TODO
    return true;
}




QHash<int, QByteArray> CReaderModel::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if (roles.empty())
    {
            roles[NameRole] = "readerName";
            roles[TypeRole] = "readerType";
            roles[StateRole] = "readerState";
            roles[DeviceAdressRole] = "readerAdress";
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
    case StateRole:
        return reader->state();
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
