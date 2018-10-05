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
        TagCountRole
    };

    Q_INVOKABLE
    QVariantMap getRow(int idx) const
    {
        QVariantMap map;
        const auto roleNames = this->roleNames();

        for (auto i = roleNames.begin(); i != roleNames.end(); ++i)
        {
            map[*i] = data(index(idx, 0), i.key());
        }
        return map;
    }

    QHash<int, QByteArray> roleNames() const
    {
        static QHash<int, QByteArray> roles;

        if (roles.empty())
        {
               /* roles[PathRole] = "fileName";
                roles[ClassRole] = "classIndex";
                roles[RecognizedAsRole] = "recognizedAs";
                roles[ConfidenceRole] = "confidence";
                roles[SelectedRole] = "selected";
                roles[FileNameRole] = "canonicalFileName";*/
        }
        return roles;
    }

    Q_INVOKABLE
    bool addReader(CAbstractReader::ReaderType type, QString name);

private:
    std::vector<std::unique_ptr<CAbstractReader>> m_readerList;

};






#endif // CREADERMODEL_H
