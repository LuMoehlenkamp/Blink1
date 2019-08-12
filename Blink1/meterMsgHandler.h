#pragma once
#include <map>
#include <string>
#include <vector>

#include "boost/algorithm/string.hpp"


class meterMsgHandler
{
private:
  enum class ObisCodes {
    utilityNumber = 10000,
    energy = 10180,
    activePowerPhaseA = 102170,
    activePowerPhaseB = 104170,
    activePowerPhaseC = 106170,
    activePowerTotal = 10170,
    statusInfo = 109655,
    serialNumber = 961255
  };
  std::string dataBuffer;
  std::string meterMessage;
  std::vector <std::string> splitVec; // meter message splitted into lines
  std::map <meterMsgHandler::ObisCodes, float> parsedMessage;
  std::string beginOfMessage;
  std::string endOfMessage;
  int messageCnt = 0;
  
public:
  meterMsgHandler();
  ~meterMsgHandler();
  void meterMessageInject(const char*);
  void extractInfoFromMsg();
  void splitMessageIntoLines();
  std::vector <std::string> splitUpLine(std::string);
  void splitUpValueAndUnit();
};