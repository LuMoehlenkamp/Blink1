#include "meterMsgHandler.h"

meterMsgHandler::meterMsgHandler()
{

}

meterMsgHandler::~meterMsgHandler()
{

}

void meterMsgHandler::splitMessageIntoLines()
{
    boost::trim(this->meterMessage);
    boost::split(this->SplitVec,this->meterMessage,boost::is_any_of("\r\n"),boost::token_compress_on);
}