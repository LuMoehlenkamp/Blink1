#include <wiringPi.h>
#include <wiringSerial.h>
#include <debug/debug.h>
#include <errno.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>

#include "mqttWrapper.h"
#include "serial.h"

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

  while (true) 
  {
    if (serialDevice.serialRead() > 0)
    {
      std::string dataBuffer;
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