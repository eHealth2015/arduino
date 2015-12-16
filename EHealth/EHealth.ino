  #include <PinChangeInt.h>
  #include <eHealthClass.h>
  #include <Arduino.h>
  #include <MsTimer2.h>
  #include <EEPROM.h>
  
  #include "Memory.h"
  #include "Bluetooth.h"
  #include "SDcard.h"

  // Les capteurs
  double airflow=0;
  int PRbpm=0;
  int oxy=0;
  float temperature = 0; //body temperature
  float conductance = 0;  //Galvanic Skin Response (GSR)

  // Valeurs moyennes des capteurs
  double mean_airflow=0, mean_airflow_rt=0;
  int mean_PRbpm=0;
  int mean_oxy=0;
  float mean_temperature = 0;
  float mean_conductance = 0;

  // Compteur pulsiomètre
  int cont=0;
  
  // Différentes vitesses de rafraichissement
  int NORMAL = 1000;
  int FAST = 333;
  // Fréquence de rafraichissement des capteurs
  int DELAY = NORMAL;
//  // Temps pendant lequel on accélère les mesures à la réception d'un message more
//  int ACCEL_TIME = 15000;
//  int stop_time = 0;
    
  // Flag pour l'interruption
  // boolean flag = false;

  // Compteur/timestamp
  int timer=0, timer_rt=0, nb_alert=0;
  int timestampStringLength = 13;
  char timestampChar[13+1];
  uint64_t timestamp = 0;
  uint64_t power = 1000000000000;

  //EEPROM
  int address = 0;
  int valueEEPROM;

  // Initialisation Mémoire/Bluetooth/carteSD
  Memory mem = Memory(40);//48
  Bluetooth bt = Bluetooth(&mem);
  SDcard sd = SDcard(&mem);
 
  void appli()
  {
    //if (timestamp != 0){
    
    //On acquiert les données
    airflow = eHealth.getAirFlow();
    //PRbpm = eHealth.getBPM();
    //if(bpm < 60 && bpm >= 0)
    //  bpm += 100;
    //oxy = eHealth.getOxygenSaturation();
    temperature = eHealth.getTemperature();
    conductance = eHealth.getSkinConductance();

    // Send ALERTS If abnormal values :
    if ((mean_airflow == 0 && timer == 10)) { // Sleep Apnea more than 10sec detected in the SD card
      nb_alert +=1;
      mem.save('H',(mean_airflow/timer));
    }
    else if (mean_airflow_rt == 0 && timer_rt == 10){ // Sleep Apnea more than 10sec detected in real time
      nb_alert +=1;
      mem.save('H',(mean_airflow_rt/timer_rt));
    }    
    if ( (37.5 < temperature) || (temperature < 36.5)){ // Alert Hypothermie, Fever or Hyperthermia, Hyperpyrexia
      nb_alert +=1;
      mem.save('K',temperature);
    }
//    if (conductance){
//      nb_alert +=1;
//      mem.save('L',conductance);
//    }
//    if ((95 > oxy) || (99 < oxy)){
//      nb_alert +=1;
//      mem.save('J',oxy);
//    }
//    if (60 > PRbpm){
//      nb_alert +=1;
//      mem.save('I',PRbpm);
//    }
    if (nb_alert != 0){
       bt.data_alert(nb_alert,getTimestamp(),valueEEPROM);
       nb_alert = 0;
    }

     if (DELAY == FAST){
      mean_airflow_rt += airflow;
      mem.save('H',airflow);
      //mem.save('I',PRbpm);
      //mem.save('J',oxy);
      mem.save('K',temperature);
      mem.save('L',conductance);
      bt.data_rt(getTimestamp(),valueEEPROM);
      if (timer_rt == 11){
        mean_airflow_rt = 0;
        timer_rt = 0; 
      }
      timer_rt++;
     }
    else if (DELAY == NORMAL){
      // Store the values in the SD card
      mean_airflow += airflow;
      //mean_PRbpm += PRbpm;
      //mean_oxy += oxy;
      mean_temperature += temperature;
      mean_conductance += conductance;
      if (timer == 11){
        mem.save('H',(mean_airflow/timer));
        //mem.save('I',(mean_PRbpm/timer));
        //mem.save('J',(mean_oxy/timer));
        mem.save('K',(mean_temperature/timer));
        mem.save('L',(mean_conductance/timer));
        sd.writefile(getTimestamp(),valueEEPROM);
        mean_airflow=0;
        //mean_PRbpm = 0;
        //mean_oxy = 0;
        mean_temperature = 0;
        mean_conductance = 0;
        timer = 0;
      }
      timer++;
    }
    //}
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
  
//  // Include always this code when using the pulsioximeter sensor
//  // =========================================================================
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
      //Serial.println("Error Type unknown");
    }
  }
  
//  void accelDelay(){
//    DELAY = FAST;
//    stop_time = millis() + ACCEL_TIME;
//  }
