#include "Memory.h"

Memory::Memory(){}
Memory::Memory(unsigned int _size){
  this->size = _size;
  this->data = (measure*) malloc(this->size*sizeof(measure));
  
  for(int i = 0; i < this->size; i++){
    this->data[i].type = 'A';
    this->data[i].value = 0.0;
  }
}

void Memory::setup(){
}
void Memory::save(char type,double value){
  this->data[this->nextSave].type = type;
  this->data[this->nextSave].value = value;

  this->nextSave  = (this->nextSave+1)%this->size;

  if(this->nextSave == this->nextSend)
    this->nextSend  = (this->nextSend+1)%this->size;
}

String Memory::getNext(){
  String data;
  
  if(this->nextSend != this->nextSave){
    double value = this->data[this->nextSend].value;
    char type = this->data[this->nextSend].type;
    
    data += type;
    data += ",";
    data += value;

    this->nextSend = (this->nextSend+1)%this->size;
  }  
  return data;    
}
