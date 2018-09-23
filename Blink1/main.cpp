#include <wiringPi.h>
#include <wiringSerial.h>
#include <termios.h>
#include <debug/debug.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <cstdio>

#define	LED	17

int main(void){
	auto i = wiringPiSetupSys();
	pinMode(LED, OUTPUT);

	int fd = 0;
	if ((fd = serialOpen("/dev/ttyAMA0", 9600)) < 0){
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		return 1;
	}

	termios options;
  termios optionsReadOut;
	tcgetattr(fd, &options);
	options.c_cflag = B9600|CS7|PARENB|CSTOPB;
	auto j = tcsetattr(fd, 0,&options);
  tcgetattr(fd, &optionsReadOut);

  /*for (int count = 0; count < 100; ++count) {
    serialPutchar(fd, count);
  }*/
  serialPuts(fd, "MoinMoin");
	
	delay(3);
  auto x = serialDataAvail(fd);
	while (serialDataAvail(fd)){
		printf(" -> %3d", serialGetchar(fd));
		fflush(stdout);
	}
	
	while (true){
		digitalWrite(LED, HIGH);  // On
		delay(100); // ms
		digitalWrite(LED, LOW);	  // Off
		delay(100);
	}
	return 0;
}