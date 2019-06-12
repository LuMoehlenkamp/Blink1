#include <iostream>
#include <wiringPi.h>

#include "mqttWrapper.h"
#include "serial.h"
#include "influxdb-cpp/influxdb.hpp"
#include "boost/algorithm/string.hpp"

#define	LED	0

int main(void)
{
  serial serialDevice;

  mqttWrapper *mqttHandler;
  mqttHandler = new mqttWrapper("mqttTest","test","192.168.178.34", 1883);
  mqttHandler->send_message("test");
  
  std::string meterMsg;

  std::string newLine;
  newLine.push_back('\n');

  std::string endOfMessage;
  endOfMessage.push_back('!');

  std::string dataBuffer;

  while (true) 
  {
    if (serialDevice.serialRead() > 0)
    {
      dataBuffer.clear();
      dataBuffer.push_back(serialDevice.getData());

      if (dataBuffer != endOfMessage) {
        meterMsg.append(dataBuffer.data());
      }
      else {
        std::cout << meterMsg << std::endl;
        meterMsg.clear();
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