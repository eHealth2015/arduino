/*
 *  eHealthClass sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi 
 *  users to perform biometric and medical applications by using 9 different 
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and 
 *  Patient Position (Accelerometer)."
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 2.0
 *  Author: Luis Martín & Ahmad Saad
 */


// Ensure this library description is only included once
#ifndef eHealthClass_h
#define eHealthClass_h

#include <Arduino.h>

// Library interface description
class eHealthClass {
	
	public: 
  
	//***************************************************************
	// Constructor of the class										*
	//***************************************************************
  
		//! Class constructor.
        eHealthClass(void);
		 
	//***************************************************************
	// Public Methods												*
	//***************************************************************
		
		//! Initializes the position sensor and configure some values.
        void initPositionSensor(void);
		 		
		//! Initializes the BloodPressureSensor sensor and configure some values
        void readBloodPressureSensor(void);
		
		//! Initializes the pulsioximeter sensor and configure some values.
        void initPulsioximeter(void);
					
		//! Returns the corporal temperature.
        float getTemperature( void );
		
        //! Returns the oxygen saturation in blood in percent between 95-99%
        int getOxygenSaturation(void);

		//! Returns the heart beats per minute. 
        int getBPM(void);
 
		//! Returns the value of skin conductance. 
        float getSkinConductance(void);
		
		//! Returns the value of skin resistance. 
        float getSkinResistance (void);
		
        //! Returns the value of skin conductance in voltage (0-5V).
        float getSkinConductanceVoltage(void);

        //! Returns an analogic value to represent the Electrocardiography (0-5V).
        float getECG(void);

		//! Returns the body position.
		/*!
		\param void   
		\return uint8_t : the position of the pacient.
		 *		1 == Supine position.
		 *		2 == Left lateral decubitus.
		 *		3 == Rigth lateral decubitus.
		 *		4 == Prone position.
         *		5 == Stand or sit position*/
         uint8_t getBodyPosition(void);
		 
		//! Returns the  value of the systolic pressure.
        int getSystolicPressure(int i);

		//! Returns the  value of the diastolic pressure.
        int getDiastolicPressure(int i);

        //! Returns an analogic value to represent the air flow (0-1023) read from the analogic in..
        int getAirFlow(void);

		//! Prints the current body position 
        void printPosition( uint8_t position );
		
		//! It reads a value from pulsioximeter sensor.
        void readPulsioximeter(void);

		//!  Prints air flow wave form in the serial monitor
        void airFlowWave(int air);

		//!Returns the number of data stored in the blood pressure sensor.
		/*!
		\param void
		\return int : length of data 
		*/	uint8_t getBloodPressureLength(void);

		//!Struct to store data of the blood pressure sensor.
		struct bloodPressureData {
			uint8_t year; 
			uint8_t month;
			uint8_t day;
			uint8_t hour;
			uint8_t minutes;
			uint8_t systolic;
			uint8_t diastolic;
			uint8_t pulse;
		};

		//!Vector to store the blood pressure measures and dates.
		bloodPressureData bloodPressureDataVector[8];

        //!  Returns the library version
        /*!
        \param void
        \return int : The library version.
        */	int version(void);

        //! Convert month variable from numeric to character.
        /*!
         \param int month in numerical format.
         \return String with the month characters (January, February...).
         */
        String numberToMonth(int month);

	private:

	//***************************************************************
	// Private Methods												*
	//***************************************************************

		//! Initialize the MMA8452 registers 
		void initMMA8452(byte fsr, byte dataRate);

		//! Sets the MMA8452 to standby mode. It must be in standby to change most register settings.
		void MMA8452Standby();
		
		//! Sets the MMA8452 to active mode. Needs to be in this mode to output data.
		void MMA8452Active();

		//! Read i registers sequentially, starting at address into the dest byte array
		void readRegisters(byte address, int i, byte * dest);

		//! Read a single byte from address and return it as a byte.
		byte readRegister(uint8_t address);

		//! Writes a single byte (data) into address.
		void writeRegister(unsigned char address, unsigned char data);

		//! This function will read the p/l source register and
		//! print what direction the sensor is now facing. 
		void portraitLandscapeHandler();

		//! Assigns a value depending on body position.
		void bodyPosition(void);
		
		//! Converts from 7 segments to number.
		uint8_t segToNumber(uint8_t A,
							uint8_t B,
							uint8_t C,
							uint8_t D,
							uint8_t E,
							uint8_t F,
							uint8_t G );

		//! Assigns a value depending on body position.
		char swap(char _data);

	//***************************************************************
	// Private Variables											*
	//***************************************************************

		//! It stores the systolic pressure value
		int systolic;

		//! It stores the diastolic pressure value
		int diastolic;

		//! It stores the  beats per minute value.
		int BPM;
		
		//! It stores blood oxigen saturation value.
		int SPO2;
		
		//! It stores current body position.
		uint8_t bodyPos; 

		//! x/y/z accel register data store here.
		byte data[6];

		//! Stores the 12-bit signed value.
		int accelCount[3];

		//! Stores the real accel value in g's.
		float accel[3];  

		//! Stores the body position in vector value. 
		uint8_t position[];

		//!It stores the number of data of the glucometer.
		uint8_t length;
};

extern eHealthClass eHealth;

#endif
