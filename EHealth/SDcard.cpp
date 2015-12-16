#include "SDcard.h"

SdFat SD;
File myfile;

SDcard::SDcard(){}
SDcard::SDcard(Memory* _mem){
  this->mem = _mem;
}

void SDcard::setup(){
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.print("Initializing SD card...");
  pinMode(10,OUTPUT);
  
  if (!SD.begin(4)) {
      Serial.println("Initialization failed!");
      return;
    }
    Serial.println("initialization done.");
}

void SDcard::writefile(uint64_t timestamp_sd, int eeprom){
  
    myfile = SD.open("data.txt", FILE_WRITE);
    
    if (myfile) {
      myfile.print("G|");
      uint64_t xx = timestamp_sd/1000000000ULL;
      if (xx >0) myfile.print((long)xx);
      myfile.print((long)(timestamp_sd-xx*1000000000));
      myfile.print("|");
      myfile.print(eeprom);
      myfile.print("|");
      for(int i = 0; i<3;i++){ // nombre de capteurs = 3
        String data = this->mem->getNext();
        myfile.print(data);
        if (i!=2)
        myfile.print("|");
      }
      myfile.println("");
      //myfile.print("|H,");
      //myfile.println(value);
      myfile.close();
    }
    else {
      Serial.println("error opening data.txt");
    }
  }

void SDcard::readfile(){

  // re-open the file for reading:
  myfile = SD.open("data.txt");
  if (myfile) {
    // read from the file until there's nothing else in it:
    while (myfile.available()) {
      Serial.write(myfile.read());
    }
    // close the file:
    myfile.close();
  } else {
    Serial.println("error opening data.txt");
  }
}

void SDcard::removefile(){
   if (SD.exists("data.txt")) {
      SD.remove("data.txt");
   }
}
