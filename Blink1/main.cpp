#include <iostream>
#include <wiringPi.h>

#include "mqttWrapper.h"
#include "serial.h"
#include "influxdb-cpp/influxdb.hpp"
#include "boost/algorithm/string.hpp"
#include "meterMsg.h"

#define	LED	0
using namespace std;
int main(void)
{
  serial serialDevice;

  /*mqttWrapper *mqttHandler;
  mqttHandler = new mqttWrapper("mqttTest","test","192.168.178.34", 1883);
  mqttHandler->send_message("test");*/
  
  std::string meterMessage;
  std::vector < std::string > SplitVec; // move to meterMsgHandler
  
  std::string beginOfMessage;
  beginOfMessage.push_back('/');

  std::string endOfMessage;
  endOfMessage.push_back('!');

  std::string dataBuffer;

  int messageCnt = 0;

  unsigned int testCnt = 0;

  influxdb_cpp::server_info serverInfo("192.168.178.34", 8086, "meter", "admin", "LuPi"); // move to meterMsgHandler

  while (true) 
  {
    if (serialDevice.serialRead() > 0)
    {
      dataBuffer.clear();
      dataBuffer.push_back(serialDevice.getData());

      if (dataBuffer == beginOfMessage) {
        ++messageCnt;
        std::cout << messageCnt << std::endl;
      }
      meterMessage.append(dataBuffer.data());

      if ((dataBuffer == endOfMessage)) {
        std::cout << meterMessage << std::endl;
        boost::trim(meterMessage);
        boost::split(SplitVec, meterMessage, boost::is_any_of("\r\n"), boost::token_compress_on); // move to meterMsgHandler
        auto a = SplitVec.at(2).find("(");
        auto b = SplitVec.at(2).rfind("*");
        auto energy = stof(SplitVec.at(2).substr(a+1, b-a+1), nullptr);
        
        a = SplitVec.at(3).find("(") + 1;
        b = SplitVec.at(3).find("*");
        auto activePowerPhaseA = stof(SplitVec.at(3).substr(a, b - a), nullptr);
        
        if (activePowerPhaseA > 15000.0) {
          ++testCnt;
        }

        a = SplitVec.at(4).find("(") + 1;
        b = SplitVec.at(4).find("*");
        auto activePowerPhaseB = stof(SplitVec.at(4).substr(a, b - a), nullptr);

        a = SplitVec.at(5).find("(") + 1;
        b = SplitVec.at(5).find("*");
        auto activePowerPhaseC = stof(SplitVec.at(5).substr(a, b - a), nullptr);

        a = SplitVec.at(6).find("(") + 1;
        b = SplitVec.at(6).find("*");
        auto activePowerTotal = stof(SplitVec.at(6).substr(a, b - a), nullptr);
        
        influxdb_cpp::builder() // move to meterMsgHandler
          .meas("test_1")
          .tag("test","y")
          .field("test", messageCnt)
          .field("energy", energy,3)
          .field("powerPhaseA",activePowerPhaseA,2)
          .field("powerPhaseB",activePowerPhaseB,2)
          .field("powerPhaseC",activePowerPhaseC,2)
          .field("powerTotal",activePowerTotal,2)
          .post_http(serverInfo);

        meterMessage.clear();
      }
      // if new data is available on the serial port, print it out
      //std::cout << dataBuffer;
      // mqttHandler->send_message("test");
    }
    else {
      std::cout << "no data\n";
    }
  }

 // while (true)
 // {
	//	digitalWrite(LED, HIGH);  // On
	//	delay(100); // ms
	//	digitalWrite(LED, LOW);	  // Off
	//	delay(100);
	//}
	return 0;
}