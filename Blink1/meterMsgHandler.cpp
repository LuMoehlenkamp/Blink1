
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
    extractInfoFromMsg();
  }
  else {
    meterMessage.append(inputString);
    //std::cout << meterMessage << std::endl;
  }
}

void meterMsgHandler::extractInfoFromMsg() {
  splitMessageIntoLines();
  int numOfLinesInMessage = splitVec.size(); // ToDo: remove after debugging
  for (auto it = splitVec.begin(); it != splitVec.end(); ++it) {
    std::vector<std::string> splitLine = splitUpLine( *it);  
  }
  
}

void meterMsgHandler::splitMessageIntoLines() {
  boost::trim(meterMessage);
  boost::split(splitVec,meterMessage,boost::is_any_of("\r\n"),boost::token_compress_on);
}

std::vector <std::string> meterMsgHandler::splitUpLine(std::string inputString) {
  std::vector <std::string> splitLine;
  boost::split(splitLine, splitVec.at(2), boost::is_any_of("*()"), boost::token_compress_on);
  return splitLine;
}

void meterMsgHandler::splitUpValueAndUnit() {
  ;
}
