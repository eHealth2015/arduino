#include "monitor.h"

#define valCritique 25
#define valInter    5

Monitor::Monitor()
{
    tachycardie = (int*)calloc(1,sizeof(int));
    nbTachycardie = 0;

    bradicardie = (int*)calloc(1,sizeof(int));
    nbBradicardie = 0;

    badSPO2 =  (int*)calloc(1,sizeof(int));
    nbSPO2 = 0;

    airflow = (int*)calloc(1,sizeof(int));
    nbAirflow = 0;

    hyperventil = (float*)calloc(1,sizeof(float));
    nbHyperventil = 0;
}

Monitor::~Monitor()
{
    delete tachycardie;
    delete bradicardie;
    delete airflow;
    delete badSPO2;
    delete hyperventil;
}

byte Monitor::monitorHeart(byte compteur, int bpm)   // retourne un int sous la forme d'un op_code: ex 00 -> tachycardie
{
    //Heart BEAT:
    //uint8_t FCmax = 220 - age;

    //tachycardie
    if (bpm >= 110)  //! condition a modifier en fonction de chaque individu (rythme cardique normal propre)
    {
        nbTachycardie ++;
        return 1;
    }

    else if (bpm <= 40)
    {
        nbBradicardie ++;
        return 1;
    }

    else
    {
        return 0;
    }
}




byte Monitor::monitorSPO2(byte compteur, int oxy)
{
    if (oxy < 94)  //94
    {
        nbSPO2 ++;
        return 1;
    }
    else if (oxy == 100)
    {
        return 4;       // danger immédiat, empoisonnement au monoxyde ---< Alerte (non implémenté)
    }
    else
    {
        return 0;
    }
}

byte Monitor::monitorBreathing(byte compteur, int period)
{
    //hyperventilation?
    if (period < 2) //correspond à plus de 30 respirations par seconde au REPOS
    {
        nbHyperventil ++;
        return 1;
    }
    else
    {
        return 0;
    }
}


byte Monitor::correlation(boolean _apneeFlag)
{
    if (nbSPO2 < valInter && _apneeFlag == false && nbTachycardie < valInter &&
            nbBradicardie < valInter && nbHyperventil < 3)
        return 1; // tout est normal

    else if (nbSPO2 > valCritique && _apneeFlag == true)
    {
        position = eHealthClass::getBodyPosition();
        nbSPO2 = 0;
        return 8;          // 8 = apnée avec désaturation
    }

    else if (nbTachycardie > valCritique && nbHyperventil > 3)
    {
       nbTachycardie = 0;
       nbHyperventil = 0;
       return 2;      //2 = Stress/emotion
    }

    else if (nbBradicardie > valCritique)
    {
        nbBradicardie = 0;
        return 3;      //3 = Bradicardie
    }

    else if (nbTachycardie > valCritique)
    {
        nbTachycardie = 0;
        return 4;      //4 = tachycardie
    }

    else if (_apneeFlag == true)
    {
        return 5;       // 5 = apnee sans SPO2;
    }

    else if (nbSPO2 > valCritique)
    {
        nbSPO2 = 0;
        return 6;       //6 = probleme d'oxygénation
    }

    else if (nbHyperventil > 3)
    {
        nbHyperventil = 0;
        return 7;       //7 = hyperventilation
    }

    else
        return 10;
}

void Monitor::fillTab(byte cpt, int _bpm, int _oxy, int _airflow)
{
        tachycardie = (int*)realloc(tachycardie,(cpt+1)*sizeof(int));
        tachycardie[cpt] = _bpm;

        badSPO2 = (int*)realloc(badSPO2, (cpt+1)*sizeof(int));
        badSPO2[cpt] = _oxy;

        airflow = (int*)realloc(airflow, (cpt+1)*sizeof(int));
        airflow[cpt] = _airflow;
}

byte Monitor::checkSensors(int bpm, int oxy, int periodeAirflow)         // on vérifie que le capteur n'a pas de defauts
{
    //on vérifie la sonde oxyométrique
    if (bpm <= 1 && oxy < 10)
        return 1;

    //on vérifie le capteur d'airflow
    else if (periodeAirflow > 20)
        return 1;

    else
        return 0;

}

void Monitor::setAge(byte _age)
{
    age = _age;
}

byte Monitor::getAge()
{
    return age;
}

