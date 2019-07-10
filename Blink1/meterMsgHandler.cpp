#include "meterMsgHandler.h"

meterMsgHandler::meterMsgHandler()
{

}

meterMsgHandler::~meterMsgHandler()
{

}

meterMsgHandler::splitMessageIntoLines()
{
    boost::trim(this.meterMessage);
    boost::split(this.SplitVec,this.meterMessage);
}