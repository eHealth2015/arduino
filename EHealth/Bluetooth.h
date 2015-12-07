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
    String trame;
    Memory* mem;
    
  public:
    Bluetooth();
    Bluetooth(Memory* _mem);
    void setup();
    int read();
    int process();
    
    void hello();
    void sync();
    void data_rt();
    void data_sd();
    void error();
};

#endif
