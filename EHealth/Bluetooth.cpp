  #include "Bluetooth.h"
  
  Bluetooth::Bluetooth(){}
  Bluetooth::Bluetooth(Memory* _mem){
    this->mem = _mem;
    //this->trame.reserve(5);
  }
  
  void Bluetooth::setup(){
  }
  
  String Bluetooth::read(){
    Serial.println("lecture");
    while (Serial.available()) {
      String inString = Serial.readStringUntil('\n');
      return inString;
    }
  }
  
  int Bluetooth::process(){
    if(this->trame.length() == 3){
      if(this->trame.substring(0,1) == "A")
        this->hello();
    }
    else if(this->trame.length() == 5){
      if(this->trame.substring(0,1) == "B")
        //this->data_rt(timestamp);
        ;
      else if(this->trame.substring(0,4) == "MORE")
        return 1;
      else if(this->trame.substring(0,4) == "STOP")
        return 2;
    }
    else{
      this->error();
    }
    return 0;
  }
  
  /**
   * A MODIFIER
   **/
  void Bluetooth::hello(){
    String msg = "A";
    //msg.concat(";");
    Serial.println(msg);
  }
  
  void Bluetooth::data_rt(char type,double value,uint64_t timestamp, int eeprom){
    String msg = "F";
    msg.concat("|");
    uint64_t xx = timestamp/1000000000ULL;
      if (xx >0) msg.concat((long)xx);
      msg.concat((long)(timestamp-xx*1000000000));
      msg.concat("|");
      msg.concat(eeprom);
      msg.concat("|");
      msg.concat(type);
      msg.concat(",");
      msg.concat(value);
//    for(int i = 0; i<1;i++){ // nombre de capteurs = 1
//      String data = this->mem->getNext();
//      msg.concat(data);
//    }
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
  
  /**
   * A MODIFIER
   **/
  void Bluetooth::error(){
    String msg = "ERROR";
    msg.concat(millis());
    msg.concat(";");
    msg.concat(this->trame);
    Serial.println(msg);
  }
