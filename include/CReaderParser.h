#ifndef CREADERPARSER_H
#define CREADERPARSER_H

#include <qstring.h>
#include <qdatetime.h>

struct UltraChipData {
    QString chipCode;
    QDateTime timeStamp;
    int antennaNo;
    double signalStrength;
    bool isRewind;
    int readerNo;
    int ultraID;
    QDateTime startTime;
    int logID;

    bool isValid;
    UltraChipData()
    {
        isValid = false;
        antennaNo = -1;
        signalStrength = 0;
        isRewind = false;
        readerNo = -1;
        ultraID = -1;
        logID = -1;
    }
};

class CReaderParser
{
    static const QDateTime ultraReferenceTime;

public:
    CReaderParser();

    static UltraChipData parseUltraChip(
            QString chip);

    static QDateTime parseUltraChipTime(
            QString seconds,
            QString milliseconds,
            bool* timeIsValid);

    static QDateTime ultraChipTime(
        const int seconds,
        const int milliseconds);
};

#endif // CREADERPARSER_H
