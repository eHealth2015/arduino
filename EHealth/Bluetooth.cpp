  #include "Bluetooth.h"
  
  Bluetooth::Bluetooth(){}
  Bluetooth::Bluetooth(Memory* _mem){
    this->mem = _mem;
  }
  
  void Bluetooth::setup(){
  }
  
  String Bluetooth::read(){
    while (Serial.available()){
      String inString = Serial.readStringUntil('\n');
      return inString;
      }
    }
  
  void Bluetooth::data_rt(uint64_t timestamp, int eeprom){
    String msg = "F";
    msg.concat("|");
    uint64_t xx = timestamp/1000000000ULL;
      if (xx >0) msg.concat((long)xx);
      msg.concat((long)(timestamp-xx*1000000000));
      msg.concat("|");
      msg.concat(eeprom);
      msg.concat("|");
    for(int i = 0; i<3;i++){ // nombre de capteurs = 3
      String data = this->mem->getNext();
      msg.concat(data);
      if (i!=2)
      msg.concat("|");
    }
    Serial.println(msg);
  }

  void Bluetooth::data_alert(int nb_alert,uint64_t timestamp, int eeprom){
    String msg = "E";
    msg.concat("|");
    uint64_t xx = timestamp/1000000000ULL;
      if (xx >0) msg.concat((long)xx);
      msg.concat((long)(timestamp-xx*1000000000));
      msg.concat("|");
      msg.concat(eeprom);
      msg.concat("|");
    for(int i = 0; i<nb_alert;i++){ // nombre de capteurs = 3
      String data = this->mem->getNext();
      msg.concat(data);
      if (i!=nb_alert-1)
      msg.concat("|");
    }
    Serial.println(msg);
  }

    void Bluetooth::data_sd(){
    //Read SD function (line by line and send to Serial)
    //String msg;
    //msg.concat(data);
    //}
    //msg.concat(";");
    //Serial.println(msg);
  }
