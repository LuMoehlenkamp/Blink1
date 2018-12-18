#pragma once
#include <termios.h>
#include <string.h>
#include <fcntl.h>

class serial
{
  struct termios initialSerialConfig;
  struct termios actualSerialConfig;
  int serialIdentifier;
  int setupResult;
  
public:
  serial();
  ~serial();
  int serialSetup(int &serialIdentifier,termios &initialSerialConfig, termios &actualSerialConfig);

};

