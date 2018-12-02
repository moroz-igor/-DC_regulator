/**************************************************************************/
/*!
    @file     trianglewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

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
            int delta(int analog[], int digital[], int first_value);

void setup(void) {
  int first_dacValue = 0;
  int dac_analog[280];
  int dac_digital[280] = {1200};
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
  dac.begin(0x60);
  Serial.println("Generating a triangle wave");
	  first_dacValue = analogRead(0);
	  	Serial.print("first_dacValue - ");
	  	Serial.println(first_dacValue);
  			for(int i = 0; i < 280; i++){
				dac_analog[i] = 300 + i;
				if(i > 0)
				dac_digital[i] = dac_digital[i - 1] + 5;
			}
			int del = delta(dac_analog, dac_digital, first_dacValue);
			/**
			Serial.println();
			Serial.print("Delta - ");
			Serial.print(del);
			**/
				count = first_dacValue + del;
					/**
					Serial.print(" / count  - ");
					Serial.println(count);
					**/
}
void loop(void) {
    uint32_t counter;
		up = digitalRead(8);
		down = digitalRead(9);
			(up) ? count = up_level(): count;
			(down) ? count = down_level(): count;
}

int delta(int analog[], int digital[], int first_value){
	int temp = 0;
	int num = 0;
	int delta = 0;
	if(first_value < 300) {num = 0; }
	if(first_value > 560) { num = 259; }
	for(int i = 0; i < 280; i++){
		temp = analog[i];
			if(first_value == temp){
				num = i;
				break;
			}
	}
		    delta = digital[num] - analog[num];
								  return delta;
}
int up_level(void){
	for (int counter = 0; counter < 4095; counter++)
    {
      delay(10);
      (count < 1200) ? count = 1200 : count = count + 5;
	   if(count > 2500) break;
		dac.setVoltage(count, true);
					   return count;
    }
}
int down_level(void){
	for (int counter = 4095; counter > 0; counter--)
    {
      delay(10);
	  (count > 2500) ? count = 2500 : count = count--;
      count = count - 5;
		if(count < 1100) break;
			dac.setVoltage(count, true);
						   return count;
    }
}
