#ifndef CABSTRACTTIMING_H
#define CABSTRACTTIMING_H

#include <QObject>
#include <QDateTime>
#include <memory>


class QSqlTableModel;

class CAbstractTiming : public QObject
{
    Q_OBJECT
public:
    explicit CAbstractTiming(
        QSqlTableModel* tableModel,
        QObject *parent = nullptr);

signals:

public slots:

    virtual void start(QList<int>& ids, QDateTime time) = 0;
    virtual void triggerTag(QString& source, QString tag, QDateTime time) = 0;
    virtual void triggerId(QString& source, int id, QDateTime time) = 0;

protected:
    std::shared_ptr<QSqlTableModel> m_times;
    QString timeFormat()
    {
        return "yyyy-MM-dd hh:mm:ss.zzz";
    }
};

#endif // CABSTRACTTIMING_H
