#pragma once

#include <string>

class meterMsg
{
private:
 std::string Line1;
 std::string Line2;
public:
  meterMsg();
  ~meterMsg();
  void splitMeterMsg();
};

