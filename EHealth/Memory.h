#ifndef MEMORY_H
#define MEMORY_H

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <ArduinoJson.h>

struct measure {
  char  type;
  long  time;
  double  value;
};

class Memory{
  private:
    unsigned int size;
    measure* data;
    unsigned int nextSave;
    unsigned int nextSend;
    String doubleToString(double input,int decimalPlaces);
  
  public:
    Memory();
    Memory(unsigned int _size);
    void setup();
    void save(char type,double value);
    String getNext();
};

#endif



