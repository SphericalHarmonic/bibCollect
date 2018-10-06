#ifndef CREADERMODEL_H
#define CREADERMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <CAbstractReader.h>

class CReaderModel : public QAbstractListModel
{
    Q_OBJECT

    enum ReaderRoles
    {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        StateRole,
        DeviceAdressRole,
        BatteryRole,
        TagCountRole,
        GatingModeRole,
        TimingModeRole,
        InUseRole
    };

public:

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE
    QVariantMap getRow(int idx) const;

    Q_INVOKABLE
    bool addReader(CAbstractReader::ReaderType type, QString name);

private:
    std::vector<std::unique_ptr<CAbstractReader>> m_readerList;

};






#endif // CREADERMODEL_H
