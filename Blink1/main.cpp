#include <iostream>
#include <wiringPi.h>

#include "mqttWrapper.h"
#include "serial.h"
#include "influxdb-cpp/influxdb.hpp"
#include "boost/algorithm/string.hpp"
#include "meterMsg.h"

#define	LED	0

int main(void)
{
  serial serialDevice;

  mqttWrapper *mqttHandler;
  mqttHandler = new mqttWrapper("mqttTest","test","192.168.178.34", 1883);
  mqttHandler->send_message("test");
  
  std::string meterMessage;

  meterMsg meterMsg;

  std::string newLine;
  newLine.push_back('\n');

  std::string beginOfMessage;
  beginOfMessage.push_back('/');

  std::string endOfMessage;
  endOfMessage.push_back('!');

  std::string dataBuffer;

  int messageCnt = 0;

  influxdb_cpp::server_info serverInfo("192.168.178.34", 8086, "meter", "admin", "LuPi");
  int testVal = 0;
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

      if (dataBuffer != endOfMessage) {
        meterMessage.append(dataBuffer.data());
      }
      else {
        std::cout << meterMessage << std::endl;
        meterMessage.clear();

        influxdb_cpp::builder()
          .meas("test_1")
          .field("test", ++testVal);
      }
      // if new data is available on the serial port, print it out
      //std::cout << dataBuffer;
      // mqttHandler->send_message("test");
    }
    else {
      std::cout << "no data\n";
    }
  }

  while (true)
  {
		digitalWrite(LED, HIGH);  // On
		delay(100); // ms
		digitalWrite(LED, LOW);	  // Off
		delay(100);
	}
	return 0;
}