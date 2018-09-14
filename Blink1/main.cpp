#include <wiringPi.h>
#include <wiringSerial.h>
#include <termios.h>
#include <debug/debug.h>
#include <cstdio>
#include <stdio.h>

#define	LED	17

int main(void){
	auto i = wiringPiSetupSys();
	pinMode(LED, OUTPUT);
	// stdout << i << std::endl;
	int fd = 0;
	termios options;
	tcgetattr(fd, &options);
	options.c_cflag = B9600|CS7|PARENB|CSTOPB;
	auto j = tcsetattr(fd, 0,&options);
	
	while (true){
		digitalWrite(LED, HIGH);  // On
		delay(100); // ms
		digitalWrite(LED, LOW);	  // Off
		delay(100);
	}
	return 0;
}