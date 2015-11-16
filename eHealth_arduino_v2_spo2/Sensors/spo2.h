#ifndef SPO2_H
#define SPO2_H

class SPO2
{
    public:
        SPO2();

        //! Initializes the pulsioximeter sensor and configure some values.
        void initPulsioximeter(void);

        //! Returns the oxygen saturation in blood in percent between 95-99%
        int getOxygenSaturation(void);

        //! It reads a value from pulsioximeter sensor.
        void readPulsioximeter(void);

    private:
        //! It stores blood oxigen saturation value.
        int SPO2;

        int BPM;
};

#endif // SPO2_H
