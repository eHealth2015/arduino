#include "ecg.h"

ECG::ECG()
{
}

float eHealthClass::getECG(void)
{
    float analog0;
    // Read from analogic in.
    analog0=analogRead(0);
    // binary to voltage conversion
    return analog0 = (float)analog0 * 5 / 1023.0;
}
