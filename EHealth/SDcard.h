#ifndef SDCARD_H
#define SDCARD_H

#include <SD.h>
#include <SPI.h>

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
    void writefile(char type,double value, unsigned long timestamp_sd);
};

#endif

