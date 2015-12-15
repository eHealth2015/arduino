  #include <PinChangeInt.h>
  #include <eHealthClass.h>
  #include <Arduino.h>
  #include <MsTimer2.h>
  #include <EEPROM.h>
  
  #include "Memory.h"
  #include "Bluetooth.h"
  #include "SDcard.h"

  // Les valeurs qui vont être lues
  double airflow=0;
  //int bpm=0;
  //int oxy=0;
  
  // Compteur pulsiomètre
  int cont=0;
  
  // Différentes vitesses de rafraichissement
  int NORMAL = 1000;
  int FAST = 333;
  
  //Fréquence de rafraichissement des capteurs
  int DELAY = FAST;
  
//  //Temps pendant lequel on accélère les mesures à la réception d'un message more
//  int ACCEL_TIME = 15000;
//  int stop_time = 0;
  
  //les autres capteurs
  float temperature = 0; //body temperature
  uint8_t pos = 0;   //position
  float conductance = 0;  //Galvanic Skin Response (GSR)
  float resistance = 0;
  float conductanceVol = 0;
    
  // Flag pour l'interruption
  boolean flag = false;

  // Compteur temps
  int timer=0;
  double mean_airflow=0;

  int timestampStringLength = 13;
  char timestampChar[13+1];
  uint64_t timestamp = 0;
  uint64_t power = 1000000000000;

  //EEPROM
  int address = 0;
  int valueEEPROM;

  Memory mem = Memory(48);
  Bluetooth bt = Bluetooth(&mem);
  SDcard sd;
 
  void appli()
  {
    if (timestamp != 0){
    
    //On acquiert les données
    airflow = eHealth.getAirFlow();
    /*bpm = eHealth.getBPM();
    if(bpm < 60 && bpm >= 0)
      bpm += 100;*/
    //oxy = eHealth.getOxygenSaturation();
    //temperature = eHealth.getTemperature();
    //pos = eHealth.getBodyPosition(); 
    //conductance = eHealth.getSkinConductance();
    //resistance = eHealth.getSkinResistance();
    //conductanceVol = eHealth.getSkinConductanceVoltage();
     
     if (DELAY == FAST){
      bt.data_rt('H',airflow,getTimestamp(),valueEEPROM);
     }
    else if (DELAY == NORMAL){
      // Store the values in the SD card
      timer++;
      mean_airflow += airflow;
      if (timer == 10){
        sd.writefile((mean_airflow/timer),getTimestamp(),valueEEPROM);
        mean_airflow=0;
        timer = 0;
      }
    }
    }
    else{
      ;
    }
  }
  
  void setup() 
  {
    Serial.begin(115200); // initialisation de la connexion série (avec le module bluetooth)

    valueEEPROM = EEPROM.read(address);
    EEPROM.write(address, valueEEPROM+1);
    mem.setup();
    bt.setup();
    sd.setup();

    // init SPo2
    //eHealth.initPulsioximeter();
  
    //Attach the interruptions for using the pulsioximeter.
    //PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  
    //Init Position
    //eHealth.initPositionSensor();
    
  }

  void loop() 
  {
    appli();
//    if(DELAY == FAST && millis() >= stop_time)
//      DELAY = NORMAL; 
    delay(DELAY);
  }

  uint64_t getTimestamp(){
    return timestamp + millis();
  }
  
//  //Include always this code when using the pulsioximeter sensor
//  //=========================================================================
//  void readPulsioximeter()
//  {  
//    cont ++;
//    if (cont == 50) 
//    { //Get only of one 50 measures to reduce the latency
//      eHealth.readPulsioximeter();  
//      cont = 0;  
//    }
//  }
  
  /* Event se déclenchant lorsqu'une donnée arrive sur le port série */
  void serialEvent(){
    String retour = bt.read();
    Serial.println(retour); 
    String type = retour.substring(0,1);

    if (type=="A"){ // Get the TIMESTAMP
      String timestampString = retour.substring(2);
      timestampString.toCharArray(timestampChar, 13+1);
      for (int i = 0; i < 13; i++) {
        timestamp += power * (timestampChar[i] - 48);
        power /= 10;
      }
    }
    else if (type=="B"){
      DELAY = FAST;
    }
    else if (type=="C"){
      //bt.data_sd();
      sd.readfile();
      sd.removefile();
    }
    else if (type=="D"){
      DELAY = NORMAL;
    }
    else{
      Serial.println("Error Type unknown");
    }
  }
  
//  void accelDelay(){
//    DELAY = FAST;
//    stop_time = millis() + ACCEL_TIME;
//  }
