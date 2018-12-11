#include <EEPROM.h>
/**************************************************************************/
/*!
    @author   Ihor Moroz
    This example will generate a triangle wave with the MCP4725 DAC.
    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935
    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
int count = 0;
		bool up = 0;
		bool down = 0;
			int up_level(void);
			int down_level(void);
void setup(void) {
	/**
	    // очистка EEPROM 
		// clearing of EEPROM
		for (int i = 0 ; i < EEPROM.length() ; i++) {
		EEPROM.write(i, 0);
		}
	**/
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
  dac.begin(0x60);
  Serial.println("Generating a triangle wave");
			/** Трансформация массива EEPROM в четырехзначное число переменной count 
				Transformation of EEPROM array to number
			**/
				count = EEPROM[0]*1000+ EEPROM[1]*100 + EEPROM[2]*10 + EEPROM[3];
					
					Serial.print(" / count  - ");
					Serial.println(count);
					
}
void loop(void) {
    uint32_t counter;
		up = digitalRead(8);
		down = digitalRead(9);
			(up) ? count = up_level(): count;
			(down) ? count = down_level(): count;
			/** Трансформация переменной  count в массив EEPROM
				Transformation of the count variable to EEPROM array
			**/
				EEPROM[0] = count/1000;   
				EEPROM[1] = count/100%10; 
				EEPROM[2] = count%100/10; 
				EEPROM[3] = count%10; 
				/**
				count = EEPROM[0]*1000+ EEPROM[1]*100 + EEPROM[2]*10 + EEPROM[3];
				if(up == 0 && down == 0){
					Serial.print(EEPROM[0]);
					Serial.print(EEPROM[1]);
					Serial.print(EEPROM[2]);
					Serial.print(EEPROM[3]);
					Serial.print(" count - ");
					Serial.println(count);
				}
				**/
}
int up_level(void){
	for (int counter = 0; counter < 4095; counter++)
    {
		delay(5);
		(count < 1200) ? count = 1200 : count = count + 5;
		/**
		Serial.print(" / count  - ");
		Serial.println(count);
		**/
		if(count > 2500){ count = 2500; break;}
		dac.setVoltage(count, true);
					   return count;
    }
}
int down_level(void){
	for (int counter = 4095; counter > 0; counter--)
    {
        delay(5);
	    (count > 2500) ? count = 2500 : count = count - 5;
		/**
	  	Serial.print(" / count  - ");
		Serial.println(count);
		**/
		if(count < 1100) {count = 1100; break;}
			dac.setVoltage(count, true);
						   return count;
    }
}
