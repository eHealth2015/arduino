#include "Memory.h"

Memory::Memory(){}
Memory::Memory(unsigned int _size){
  this->size = _size;
  this->data = (measure*) malloc(this->size*sizeof(measure));
  
  for(int i = 0; i < this->size; i++){
    this->data[i].type = 'A';
    this->data[i].time = 0;
    this->data[i].value = 0.0;
  }
}

void Memory::setup(){
}
void Memory::save(char type,double value){
  this->data[this->nextSave].type = type;
  this->data[this->nextSave].time = millis();
  this->data[this->nextSave].value = value;

  this->nextSave  = (this->nextSave+1)%this->size;

  if(this->nextSave == this->nextSend)
    this->nextSend  = (this->nextSend+1)%this->size;
}

String Memory::getNext(){
  String data;
  data.reserve(100);
  
  if(this->nextSend != this->nextSave){
    long time = this->data[this->nextSend].time;
    double value = this->data[this->nextSend].value;
    char type = this->data[this->nextSend].type;
    
    data.concat(time);
    data.concat("|");
    data.concat(type);
    data.concat("|");
    data.concat(doubleToString(value,2));

    this->nextSend = (this->nextSend+1)%this->size;
  }
   
  return data;
    
}


JsonObject& Memory::parsingJSON(double value1){ //, double value2, double value3
  
    StaticJsonBuffer<200> jsonBuffer;
    // Build object tree in memory
    JsonObject& root = jsonBuffer.createObject();
    
    root["type"] = "DATA";
    root["time"] = millis();
    
    JsonArray& sensor = root.createNestedArray("sensor");
    JsonArray& data = root.createNestedArray("data");
    sensor.add("A");
    data.add(value1, 3);  // 6 is the number of decimals to print
    //sensor.add("B");
    //data.add(value2, 3);
    //sensor.add("O");
    //data.add(value3, 3);  
    root.printTo(Serial);

    return root;
}

String Memory::doubleToString(double input,int decimalPlaces){
  if(decimalPlaces!=0){
    String string = String((int)(input*pow(10,decimalPlaces)));
    if(abs(input)<1){
      if(input>0)
        string = "0"+string;
      else if(input<0)
        string = string.substring(0,1)+"0"+string.substring(1);
    }
    return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
  }
  else {
    return String((int)input);
  }
}

