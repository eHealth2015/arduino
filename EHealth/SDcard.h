#ifndef SDCARD_H
#define SDCARD_H

#include <SD.h>
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

class SDcard{
  public:
    SDcard();
    void setup();
    void readfile();
    void writefile(char type,double value);
};

#endif
