#include "testcreaderparser.h"
#include "CReaderParser.h"

TestCReaderParser::TestCReaderParser(QObject *parent) : QObject(parent)
{

}

void TestCReaderParser::testUltraChipTime()
{
    const auto seconds = 86400;
    const auto milliseconds = 500;

    QDateTime testTime = QDateTime::fromString(
                "1980-01-02T00:00:00:500",
                "yyyy-MM-ddThh:mm:ss:zzz");

    QCOMPARE(testTime, CReaderParser::ultraChipTime(seconds, milliseconds));
}

//QTEST_MAIN(TestCReaderParser)
