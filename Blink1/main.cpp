// ToDo List:
// + mqtt wrapper implementation withoud using threads
//  - reconnect if constructor fails to connect to broker
//
// + implementation of meter message interpreter
//  - identify beginnig of new message
//  - split message into individual lines
//  - parse OBIS codes and corresponding values including their units
// 
// + inject new messages into database

#include <iostream>
#include <wiringPi.h>

#include "mqttWrapper.h"
#include "serial.h"
#include "influxdb-cpp/influxdb.hpp"

#define	LED	0

int main(void)
{
  serial serialDevice;

  mqttWrapper *mqttHandler;
  mqttHandler = new mqttWrapper("mqttTest","test","192.168.178.34", 1883);
  mqttHandler->send_message("test");
  
  std::string meterMsgLine;

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
      if (dataBuffer != newLine) {
        meterMsgLine.operator+=(dataBuffer);
      }
      // if new data is available on the serial port, print it out
      std::cout << dataBuffer;
      // mqttHandler->send_message("test");
    }
    else 
    {
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