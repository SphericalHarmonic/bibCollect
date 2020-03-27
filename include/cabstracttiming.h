#ifndef CABSTRACTTIMING_H
#define CABSTRACTTIMING_H

#include <QObject>
//#include <QList>

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

private:
    std::shared_ptr<QSqlTableModel> m_table;
};

#endif // CABSTRACTTIMING_H
