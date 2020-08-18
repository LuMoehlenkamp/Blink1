#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <set>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

enum class ObisCodes {
  utilityNumber     = 10000,
  energy            = 10180,
  activePowerPhaseA = 102170,
  activePowerPhaseB = 104170,
  activePowerPhaseC = 106170,
  activePowerTotal  = 10170,
  statusInfo        = 109655,
  serialNumber      = 961255,
  invalidNum
};

class meterMsgHandler
{

private:
  std::string dataBuffer;
  std::string meterMessage;
  std::vector <std::string> splitVec; // meter message splitted into lines
  std::map <ObisCodes, double> parsedMessage;
  std::set <int> allowedObisCodes = {10000, 10180, 102170, 104170, 106170, 10170,109655,961255};
  const std::string beginOfMessage = "/";
  const std::string endOfMessage = "!";
  int messageCount = 0;

  bool extractInfoFromMsg();
  int splitMessageIntoLines();
  std::vector <std::string> splitUpLine(std::string&);
  void splitUpLineElements();
  
public:
  meterMsgHandler() = default;
  ~meterMsgHandler() = default;
  meterMsgHandler(const meterMsgHandler&) = delete; // copy ctor
  meterMsgHandler& operator=(const meterMsgHandler&) = delete; // copy assignment operator

  void SetMeterMessage(const std::string);
  std::map<ObisCodes, double> getParsedMessage();
  int getMessageCount();
};