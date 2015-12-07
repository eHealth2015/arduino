#ifndef MONITOR_H
#define MONITOR_H

#include"eHealthClass.h"



class Monitor : public eHealthClass
{
public:
    Monitor();
    ~Monitor();

    byte monitorHeart(byte compteur, int bpm);   // compare la valeur bpm à une valeur de référence
    byte monitorSPO2(byte compteur, int oxy);
    byte monitorBreathing(byte compteur, int period);
    //byte monitorAirflow(byte compteur, int breath);

    byte correlation(boolean _apneeFlag);        // retourne le diagnostic

    byte checkSensors(int bpm, int oxy, int periodeAirflow);

    void fillTab(byte cpt, int _bpm, int _oxy, int _airflow);

    int* tachycardie;
    byte nbTachycardie;

    int* bradicardie;
    byte nbBradicardie;

    int* badSPO2;
    byte nbSPO2;

    float* hyperventil;
    byte nbHyperventil;

//    float* apnee;
    byte nbApnee;

    int* airflow;
    byte nbAirflow;

    byte position;


    void setAge(byte _age);
    byte getAge();

private:
    uint8_t age;


};


#endif // MONITOR_H
