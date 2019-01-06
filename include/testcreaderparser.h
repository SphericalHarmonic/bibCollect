#ifndef TESTCREADERPARSER_H
#define TESTCREADERPARSER_H

#include <QtTest/QtTest>

class TestCReaderParser : public QObject
{
    Q_OBJECT
public:
    explicit TestCReaderParser(QObject *parent = nullptr);

signals:

private slots:
    void testUltraChipTime();
};

#endif // TESTCREADERPARSER_H
