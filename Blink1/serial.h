#pragma once
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

class serial
{
  struct termios initialSerialConfig;
  struct termios actualSerialConfig;
  int serialIdentifier;
  int setupResult;
  char dataBuffer;
  
public:
  serial();
  ~serial();
  int serialSetup();
  int serialRead();
  int serialTearDown();
  char getData();
};

