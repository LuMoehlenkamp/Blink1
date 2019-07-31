
#include "meterMsgHandler.h"
#include "boost/algorithm/string.hpp"

meterMsgHandler::meterMsgHandler() {
  beginOfMessage.push_back('/');
  endOfMessage.push_back('!');
}

meterMsgHandler::~meterMsgHandler() {

}

void meterMsgHandler::meterMessageInject(const char * inputString)
{
  if (inputString == beginOfMessage) {
    meterMessage.clear();
    //std::cout << ++messageCnt << std::endl;
  }
  else if (inputString == endOfMessage) {
    splitMessageIntoLines();
    splitLines();
  }
  else {
    meterMessage.append(inputString);
    //std::cout << meterMessage << std::endl;
  }
}

void meterMsgHandler::splitMessageIntoLines() {
    boost::trim(meterMessage);
    auto a = boost::split(SplitVec,meterMessage,boost::is_any_of("\r\n"),boost::token_compress_on);
}

void meterMsgHandler::splitLines()
{
  std::vector <std::string> splitLine;
  auto b = boost::split(splitLine, SplitVec.at(2), boost::is_any_of("*()"), boost::token_compress_on);
  ;
}
