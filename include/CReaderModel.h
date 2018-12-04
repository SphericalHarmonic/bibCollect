#ifndef CREADERMODEL_H
#define CREADERMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <CAbstractReader.h>

class CReaderModel : public QAbstractListModel
{
    Q_OBJECT

    public:
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




    CReaderModel();

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE
    QVariant data(const int row, int role = Qt::DisplayRole);

    Q_INVOKABLE
    int roleIndex(QString roleName);

    Q_INVOKABLE
    QVariantMap getRow(int idx) const;

    //Q_INVOKABLE
    bool addReader(CAbstractReader::ReaderType type, QString name);

    Q_INVOKABLE
    bool addReader(int type, QString name, QString address);


    bool addReader(std::unique_ptr<CAbstractReader> reader);

    Q_INVOKABLE
    QStringList readerTypes();


private:
    std::vector<std::unique_ptr<CAbstractReader>> m_readerList;

    QStringList m_readerTypeList;



    void initializeReaderTypeList();

    int m_currentIndex;

};






#endif // CREADERMODEL_H
