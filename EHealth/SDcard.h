#ifndef SDCARD_H
#define SDCARD_H

#include <SdFat.h>
#include <SPI.h>
#include "Memory.h"

class SDcard{
  private:
  Memory* mem;
    
  public:
    SDcard();
    SDcard(Memory* _mem);
    void setup();
    void writefile(uint64_t timestamp_sd, int eeprom);
    void readfile();
    void removefile();
};

#endif

