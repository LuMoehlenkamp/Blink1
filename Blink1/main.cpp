#include <iostream>
#include <wiringPi.h>

#include "mqttWrapper.h"
#include "serial.h"
#include "influxdb-cpp/influxdb.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/version.hpp"
#include "meterMsg.h"
#include "meterMsgHandler.h"

constexpr auto LED = 0;
using namespace std;
int main(void)
{
  serial serialDevice;

  /*mqttWrapper *mqttHandler;
  mqttHandler = new mqttWrapper("mqttTest","test","192.168.178.34", 1883);
  mqttHandler->send_message("test");*/
  
  meterMsgHandler meterMsg;
  std::string meterMessage;
  std::vector < std::string > SplitVec; // move to meterMsgHandler
  
  std::string beginOfMessage;
  beginOfMessage.push_back('/');

  std::string endOfMessage;
  endOfMessage.push_back('!');

  std::string dataBuffer;

  int beginOfMessageCount = 0;

  int messageCount = 0;
  int messageCount_old = 0;
  //unsigned int testCntEnergy = 0;
  //unsigned int testCntPowerPhaseA = 0;

  influxdb_cpp::server_info serverInfo("192.168.178.38", 8086, "meter", "admin", "LuPi"); // move to meterMsgHandler

  //float energy = 0.0;
  //float activePowerPhaseA = 0.0;
  //float activePowerPhaseB = 0.0;
  //float activePowerPhaseC = 0.0;
  //float activePowerTotal = 0.0;

  while (true) {
    if (serialDevice.serialRead() > 0) {
      dataBuffer.clear();
      dataBuffer.push_back(serialDevice.getData());

      if (dataBuffer == beginOfMessage) {  // ToDo: Move to meterMsgHandler
        meterMessage.clear();
        ++beginOfMessageCount;
        std::cout << "begin of message count: " << beginOfMessageCount << std::endl;
      }
      else if (dataBuffer != endOfMessage) {
      meterMessage.append(dataBuffer.data());
      }
      if ((dataBuffer == endOfMessage)) {
        meterMsg.SetMeterMessage(meterMessage);
        std::cout << meterMessage << std::endl;
      }
 
      messageCount_old = messageCount;
      messageCount = meterMsg.getMessageCount();
      
      if (messageCount != messageCount_old) {
        auto parsedMessage = meterMsg.getParsedMessage();

        influxdb_cpp::builder() // move to meterMsgHandler
          .meas("test_1")
          .tag("test", "y")
          .field("test", messageCount)
          .field("energy", parsedMessage.find(ObisCodes::energy)->second, 10)
          .field("powerPhaseA", parsedMessage.find(ObisCodes::activePowerPhaseA)->second, 10)
          .field("powerPhaseB", parsedMessage.find(ObisCodes::activePowerPhaseB)->second, 10)
          .field("powerPhaseC", parsedMessage.find(ObisCodes::activePowerPhaseC)->second, 10)
          .field("powerTotal", parsedMessage.find(ObisCodes::activePowerTotal)->second, 10)
          .post_http(serverInfo);
       
          SplitVec.clear(); //ToDo: check if correct
        }
      }
      // if new data is available on the serial port, print it out
      // std::cout << dataBuffer;
      // mqttHandler->send_message("test");
    
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