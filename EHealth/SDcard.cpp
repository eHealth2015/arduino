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

//void SDcard::readfile(){
//  myfile = SD.open("results.txt", FILE_READ); // Open the file in Read/Write mode
//  while (myfile.available()) {
//    char c = myfile.read();
//    // Utiliser c pour récupérer les valeurs des capteurs
//  }
//  myfile.close();
//}

void SDcard::writefile(char type,double value){
  File myfile;
  
  switch(type){
  case 'H':
    myfile = SD.open("airflow.txt", FILE_WRITE);
    if (myfile) {
      myfile.println(value + '\n');
      Serial.println(value + '\n');
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
