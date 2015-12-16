#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "Memory.h"


#define SNUMBER "00112233445566778899AABBCCDDEEFF"
#define FIRMWARE "0.1a"

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

class Bluetooth{
  private:
    Memory* mem;
    
  public:
    Bluetooth();
    Bluetooth(Memory* _mem);
    void setup();
    String read();
    void data_rt(uint64_t timestamp, int eeprom);
    void data_alert(int nb_alert,uint64_t timestamp, int eeprom);
    void data_sd();
};

#endif
