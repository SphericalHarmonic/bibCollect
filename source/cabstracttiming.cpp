#include "cabstracttiming.h"
#include "qsqltablemodel.h"

CAbstractTiming::CAbstractTiming(
    QSqlTableModel* tableModel,
    QObject *parent)
    :
    QObject(parent),
    m_table(tableModel)
{

}
