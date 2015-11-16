  #include "Bluetooth.h"
  
  Bluetooth::Bluetooth(){}
  Bluetooth::Bluetooth(Memory* _mem){
    this->mem = _mem;
    this->trame.reserve(200);
  }
  
  void Bluetooth::setup(){
  }
  
  int Bluetooth::read(){
    int more;
    Serial.println("lecture");
    while (Serial.available()) {
      char inChar = (char)Serial.read(); 
      this->trame += inChar;
      
      if (inChar == '\r' || inChar == '\n') {
        more = this->process();
        Serial.println(this->trame);
        this->trame = "";
        Serial.println(more);
        return more;
      }
    }
  }
  
  int Bluetooth::process(){
    if(this->trame.length() == 6){
      if(this->trame.substring(0,5) == "HELLO")
        this->hello();
    }
    else if(this->trame.length() == 5){
      if(this->trame.substring(0,4) == "DATA")
        this->data();
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
    String msg = "HELLO;";
    msg.concat(millis());
    msg.concat(";");
    msg.concat(SNUMBER);
    msg.concat("|");
    msg.concat(FIRMWARE);
    Serial.println(msg);
  }
  
  void Bluetooth::data(){
    String msg = "DATA";
    msg.concat(millis());
    for(int i = 0; i<3;i++){
      String data = this->mem->getNext();
      msg.concat(";");
      msg.concat(data);
    }
    Serial.println(msg);
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
