#include "CReaderParser.h"

const QDateTime CReaderParser::ultraReferenceTime =
        QDateTime::fromString("1980-01-01T00:00:00 ", Qt::ISODate);

CReaderParser::CReaderParser()
{

}


UltraChipData CReaderParser::parseUltraChip(
    QString chip)
{
    UltraChipData chipData;
    const auto values = chip.trimmed().split(',');
    if (values.length() != 12)
    {
        return chipData;
    }

    bool validField;

    chipData.chipCode = values[1];
    chipData.timeStamp = parseUltraChipTime(values[2], values[3], &validField);

    chipData.isValid = validField;

    //TODO: parse the other fields if needed.

    return chipData;
}


QDateTime CReaderParser::parseUltraChipTime(
    QString seconds,
    QString milliseconds,
    bool* timeIsValid)
{
    if (timeIsValid != nullptr)
    {
        *timeIsValid = false;
    }

    bool validSeconds = false;
    const int sec = seconds.toInt(&validSeconds);
    if (sec < 0)
    {
        validSeconds = false;
    }

    bool validMilliseconds;
    const int milli = milliseconds.toInt(&validMilliseconds);
    if (milli < 0 )
    {
        validMilliseconds = false;
    }

    QDateTime time;

    if (validMilliseconds && validMilliseconds)
    {
        if (timeIsValid != nullptr)
        {
            *timeIsValid = true;
        }
        time = ultraChipTime(sec, milli);
    }

    return time;
}

QDateTime CReaderParser::ultraChipTime(
    const int seconds,
    const int milliseconds)
{
    return ultraReferenceTime.addMSecs(seconds*1000 + milliseconds);
}
