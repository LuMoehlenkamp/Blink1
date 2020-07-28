
#include "meterMsgHandler.h"

//meterMsgHandler::meterMsgHandler() {
//  //beginOfMessage.push_back('/');
//  endOfMessage.push_back('!');
//}

void meterMsgHandler::SetMeterMessage(const std::string inputString) {
  //if (inputString == beginOfMessage) {
  meterMessage.clear();
  //  ++messageCnt;
  //}
  //else if (inputString == endOfMessage) {
  //  extractInfoFromMsg();
  //}
  //else {
  //  meterMessage.append(inputString);
  // }
  meterMessage.append(inputString);
  extractInfoFromMsg();
  ++messageCnt;
}

std::map<ObisCodes, double> meterMsgHandler::getParsedMessage() {
  return this->parsedMessage;
}

int meterMsgHandler::getMessageCount() {
  return messageCnt;
}

void meterMsgHandler::extractInfoFromMsg() {
  parsedMessage.clear();
  int numOfElementsInLine = 0;
  int obisCodeAsInt = 0;
  std::vector <std::string> lineSplittedIntoElementsVec;

  int numOfLinesInMessage = splitMessageIntoLines(); // ToDo: check if number of lines is 9 (0-9)

  if (numOfLinesInMessage != 9) {
    return;
  }

  for (auto splitVecIt : splitVec) {
    lineSplittedIntoElementsVec = splitUpLine(splitVecIt);
    numOfElementsInLine = lineSplittedIntoElementsVec.size();
    ObisCodes obisCode;
    double value = 0.0;

    if (numOfElementsInLine > 1) {
      boost::erase_all(lineSplittedIntoElementsVec.at(0),".");
      boost::erase_all(lineSplittedIntoElementsVec.at(0),"-");
      boost::erase_all(lineSplittedIntoElementsVec.at(0),":");

      obisCodeAsInt = std::stoi(lineSplittedIntoElementsVec.at(0));
      obisCode = static_cast<ObisCodes>(obisCodeAsInt);

      value = 0.0;
      if (splitVecIt != "0-0:96.1.255*255(1ESY1314002995)") {
        try {
          value = boost::lexical_cast<double>(lineSplittedIntoElementsVec.at(2));
        }
        catch (const boost::bad_lexical_cast &) {
          value = 0.0;  // ToDo: use break instead
        }
        catch (...) {
          value = 0.0;
        }
      parsedMessage.insert(std::make_pair(obisCode, value));
      }
    }
  }
}

int meterMsgHandler::splitMessageIntoLines() {
  int numOfLinesInMessage = 0;
  boost::trim(meterMessage);
  boost::split(splitVec, meterMessage, boost::is_any_of("\r\n"), boost::token_compress_on);
  numOfLinesInMessage = splitVec.size();
  return numOfLinesInMessage;
}

std::vector <std::string> meterMsgHandler::splitUpLine(std::string& inputString) {
  std::vector <std::string> splitLine;
  boost::split(splitLine, inputString, boost::is_any_of("*()"), boost::token_compress_on);
  return splitLine;
}

void meterMsgHandler::splitUpLineElements() {
  ;
}
