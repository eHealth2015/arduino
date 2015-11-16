#ifndef ECG_H
#define ECG_H

#include "Arduino.h"

class ECG
{
    public:
        ECG();

        //! Returns the heart beats per minute.
        int getBPM(void);

        //! Returns an analogic value to represent the Electrocardiography (0-5V).
        float getECG(void);

};

#endif // ECG_H
