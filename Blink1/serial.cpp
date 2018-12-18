#include "serial.h"
#include <string.h>
#include <fcntl.h>

serial::serial()
{
}


serial::~serial()
{
}

int serial::serialSetup(int &serialIdentifier, termios &initialSerialConfig, termios &actualSerialConfig)
{
  serialIdentifier = open("/dev/ttyAMA0", O_RDWR);
  tcgetattr(serialIdentifier, &initialSerialConfig);
  
  memset(&actualSerialConfig, 0, sizeof(actualSerialConfig));
  actualSerialConfig.c_iflag = 0;
  actualSerialConfig.c_oflag = 0;
  actualSerialConfig.c_cflag = CS7 | CREAD | CLOCAL;
  actualSerialConfig.c_lflag = 0;
  actualSerialConfig.c_cc[VMIN] = 1;
  actualSerialConfig.c_cc[VTIME] = 5;

  cfsetospeed(&actualSerialConfig, B9600);
  cfsetispeed(&actualSerialConfig, B9600);

  return tcsetattr(serialIdentifier, TCSANOW, &actualSerialConfig);
}

void serial::serialConnect()
{
}
