#include "CReaderModel.h"
#include "CUHFReader.h"



bool CReaderModel::addReader(CAbstractReader::ReaderType type, QString name)
{

    switch (type) {
    case CAbstractReader::UHF:
        //auto newReader = std::make_unique<CUHFReader>(name, this);
        m_readerList.push_back(std::make_unique<CUHFReader>(name, this));
        break;
    case CAbstractReader::MF: //TODO
        break;
    case CAbstractReader::LF: //TODO
        break;
    default:
        break;
    }

    //TODO: Check for success or change return type to void
    return true;
}
