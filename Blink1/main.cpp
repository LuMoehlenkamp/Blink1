#include <wiringPi.h>
#include <wiringSerial.h>
#include <termios.h>
#include <debug/debug.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstdio>

#define	LED	0

int main(void){
  int res = 0;
  res = wiringPiSetup();
  int uart0_filestream = -1;
  uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (uart0_filestream == -1) {
    printf("[ERROR] UART open()\n");
  }

  struct termios options;
  tcgetattr(uart0_filestream, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);


  // Bytes senden
  unsigned char BUF_TX[20];
  unsigned char *TX;

  TX = &BUF_TX[0];
  *TX++ = 'R';
  *TX++ = 'a';
  *TX++ = 's';
  *TX++ = 'p';
  *TX++ = 'b';
  *TX++ = 'e';
  *TX++ = 'r';
  *TX++ = 'r';
  *TX++ = 'y';
  *TX++ = ' ';
  *TX++ = 'P';
  *TX++ = 'i';

  if (uart0_filestream != -1) {
    int out = write(uart0_filestream, &BUF_TX[0], (TX - &BUF_TX[0])); // 
    if (out < 0) {
      printf("[ERROR] UART TX\n");
    }
    else {
      printf("[STATUS: TX %i Bytes] %s\n", out, BUF_TX);
    }
  } // if uart0

  sleep(1);

  // Bytes empfangen
  if (uart0_filestream != -1) {
    unsigned char BUF_RX[50];
    int rx_length = read(uart0_filestream, (void*)BUF_RX, 50);

    if (rx_length < 0) {
      printf("[ERROR] UART RX\n");
    }
    else if (rx_length == 0) {
      printf("[ERROR] UART RX - no data\n");
    }
    else {
      BUF_RX[rx_length] = '\0';
      printf("[STATUS: RX %i Bytes] %s\n", rx_length, BUF_RX);
    } //rx_length check
  } //if uart0

  close(uart0_filestream);




	//int fd = 0;

	//if ((fd = serialOpen("/dev/serial0", 9600)) < 0){
	//	fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
	//	return 1;
	//}

	//termios options;
 // termios optionsReadOut;
	//tcgetattr(fd, &options);
	//options.c_cflag = B9600|CS7|PARENB|CSTOPB;
	//auto j = tcsetattr(fd, 0,&options);
 // tcgetattr(fd, &optionsReadOut);

 // auto i = wiringPiSetupSys();
 // pinMode(LED, OUTPUT);

 // /*for (int count = 0; count < 100; ++count) {
 //   serialPutchar(fd, count);
 // }*/
 // serialPuts(fd, "MoinMoin");
	//
	//delay(3);
 // auto x = serialDataAvail(fd);
	//while (serialDataAvail(fd)){
	//	printf(" -> %3d", serialGetchar(fd));
	//	fflush(stdout);
	//}
	
	while (true){
		digitalWrite(LED, HIGH);  // On
		delay(100); // ms
		digitalWrite(LED, LOW);	  // Off
		delay(100);
	}
	return 0;
}