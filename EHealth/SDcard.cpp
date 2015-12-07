#include "SDcard.h"

SDcard::SDcard(){}
void SDcard::setup(){

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
      Serial.println("Initialization failed!");
      return;
    }
    Serial.println("initialization done.");
}

//    void Bluetooth::data_sd(){
//    String msg = ":C";
//    msg.concat("|");
//    msg.concat(millis());
//    msg.concat("|");
//    msg.concat("seqID");
//    msg.concat("|");
//    for(int i = 0; i<1;i++){ // nombre de capteurs = 1
//      String data = this->mem->getNext(); 
//      msg.concat(data);
//    }
//    msg.concat(";");
//    Serial.println(msg);
//  }

void SDcard::writefile(char type,double value, unsigned long timestamp_sd){
  File myfile;
  
  switch(type){
  case 'H':
    myfile = SD.open("airflow.txt", FILE_WRITE);
    if (myfile) {
      myfile.print(":C|");
      myfile.print(timestamp_sd);
      myfile.print("|seqID|H,");
      myfile.println(value);
      Serial.println("done.");
    }
    else {
      Serial.println("error opening airflow.txt");
    }
    myfile.close();
    break;
    
   default:
   break;
  }
  }
