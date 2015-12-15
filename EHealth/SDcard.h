#ifndef SDCARD_H
#define SDCARD_H

//#include <SD.h>
#include <SdFat.h>
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
    void writefile(double value, uint64_t timestamp_sd, int eeprom);
    void readfile();
    void removefile();
};

#endif

