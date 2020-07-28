#pragma once

#include <string>
#include <cstddef>
class meterMsg
{
private:
 std::string manufacturerID;
 std::string utilityID;
 double importetEnergy_01mWh;
 double exportetEnergy_01mWh;
 float actualPower_L1_W;
 float actualPower_L2_W;
 float actualPower_L3_W;
 float actualPower_total_W;
 unsigned char statusInfo;
 std::string factoryNumber;

 public:
  meterMsg();
  ~meterMsg() = default;
  void splitMeterMsg();
};

