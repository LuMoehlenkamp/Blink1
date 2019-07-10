#pragma once
#include "boost/algorithm/string.hpp"

class meterMsgHandler
{
private:
  std::string meterMessage
  std::vector < std::string > SplitVec; // meter message splitted into lines
public:
  meterMsgHandler();
  ~meterMsgHandler();

  void splitMessageIntoLines();
};