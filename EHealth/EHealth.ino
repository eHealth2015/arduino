  #include <PinChangeInt.h>
  #include <eHealthClass.h>
  #include <Arduino.h>
  #include <MsTimer2.h>
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
  int DELAY = NORMAL;
  
  //Temps pendant lequel on accélère les mesures à la réception d'un message more
  int ACCEL_TIME = 15000;
  int stop_time = 0;
  
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
  int timestamp=0;  

  Memory mem = Memory(48);
  Bluetooth bt = Bluetooth(&mem);
  SDcard sd;
 
  void appli()
  {
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
        mem.save('H',airflow);
        bt.data_rt(); // Doit être effectué quand on veut envoyer les données.
     }
    else if (DELAY == NORMAL){
      // Store the values in the SD card
      
      timer++;
      mean_airflow += airflow;
      Serial.println(airflow);
      if (timer == 10){
        // Process valeurs moyennes
        // Stocker les valeurs moyennes "mean_ariflow"
        sd.writefile('H',(mean_airflow/timer),getTimestamp());
        Serial.println("MEAN");
        Serial.println((mean_airflow/timer));
        mean_airflow=0;
        //mem.save('H',airflow);
        //bt.data_sd();
        timer = 0;

        // Foonction delete sur carte SD des 3 fichiers
      }
    }
    //mem.save('H',airflow);
    //bt.data_rt();
  }
  
  void setup() 
  {
    Serial.begin(115200); // initialisation de la connexion série (avec le module bluetooth)
  
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
    if(DELAY == FAST && millis() >= stop_time)
      DELAY = NORMAL; 
    delay(DELAY);
  }

  unsigned long getTimestamp(){
    return millis();
  }
  
  //Include always this code when using the pulsioximeter sensor
  //=========================================================================
  void readPulsioximeter()
  {  
    cont ++;
    if (cont == 50) 
    { //Get only of one 50 measures to reduce the latency
      eHealth.readPulsioximeter();  
      cont = 0;  
    }
  }
  
  /* Event se déclenchant lorsqu'une donnée arrive sur le port série */
  void serialEvent(){
    int retour = bt.read();
    if(retour == 1)
      accelDelay();
    else if(retour == 2)
      DELAY = NORMAL;
    //else if (retour == "A")
      // TO DO
  }
  
  void accelDelay(){
    DELAY = FAST;
    stop_time = millis() + ACCEL_TIME;
  }
