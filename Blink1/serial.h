#pragma once
#include <termios.h>

class serial
{
  struct termios initialSerialConfig;
  struct termios actualSerialConfig;
  int serialIdentifier;
  
public:
  serial();
  ~serial();
  int serialSetup(int &serialIdentifier,termios &initialSerialConfig, termios &actualSerialConfig);
  void serialConnect();
};

