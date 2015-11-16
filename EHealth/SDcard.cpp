#include "SDcard.h"

File myfile;
SDcard::SDcard(){}
void SDcard::setup(){
  if (!SD.begin(4)) {
      Serial.println("Initialization failed!");
      return;
    }
    Serial.println("SD Card ready to be used");
}

void SDcard::readfile(){
  myfile = SD.open("results.txt", FILE_READ); // Open the file in Read/Write mode
  while (myfile.available()) {
    char c = myfile.read();
    // Utiliser c pour récupérer les valeurs des capteurs
  }
  myfile.close();
}

void SDcard::writefile(char type,double value){
  
  switch(type){
  case 'A':
    myfile = SD.open("airflow_results.txt", FILE_WRITE);
    myfile.println(value+'\n');
    myfile.close();
    break;
   case 'B':
    myfile = SD.open("bpm_results.txt", FILE_WRITE);
    myfile.println(value+'\n');
    myfile.close();
    break;
   case 'O':
    myfile = SD.open("oxy_results.txt", FILE_WRITE);
    myfile.println(value+'\n');
    myfile.close();
    break;
   default:
   break;
  }
   
}

