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
  //data.reserve(100);
  
  if(this->nextSend != this->nextSave){
    long time = this->data[this->nextSend].time;
    double value = this->data[this->nextSend].value;
    char type = this->data[this->nextSend].type;
    
    data.concat(type);
    data.concat(",");
    data.concat(doubleToString(value,2));

    this->nextSend = (this->nextSend+1)%this->size;
  }
   
  return data;
    
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

