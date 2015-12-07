  #include "Bluetooth.h"
  
  Bluetooth::Bluetooth(){}
  Bluetooth::Bluetooth(Memory* _mem){
    this->mem = _mem;
    //this->trame.reserve(5);
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
    if(this->trame.length() == 3){
      if(this->trame.substring(0,1) == "A")
        this->hello();
    }
    else if(this->trame.length() == 5){
      if(this->trame.substring(0,1) == "B")
        this->data_rt();
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
    String msg = ":A";
    msg.concat(";");
    Serial.println(msg);
  }
  
  void Bluetooth::data_rt(){
    String msg = ":B";
    msg.concat("|");
    msg.concat(millis());// Timetstamp = millis() + clockGab
    msg.concat("|");
    msg.concat("seqID");
    msg.concat("|");
    for(int i = 0; i<1;i++){ // nombre de capteurs = 1
      String data = this->mem->getNext();
      msg.concat(data);
    }
    msg.concat(";");
    Serial.println(msg);
  }

    void Bluetooth::data_sd(){
    String msg = ":C";
    msg.concat("|");
    msg.concat(millis());
    msg.concat("|");
    msg.concat("seqID");
    msg.concat("|");
    for(int i = 0; i<1;i++){ // nombre de capteurs = 1
      String data = this->mem->getNext(); 
      //msg.concat(";");
      msg.concat(data);
    }
    msg.concat(";");
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
