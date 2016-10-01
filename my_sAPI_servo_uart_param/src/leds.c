/*
 * leds.c
 *
 *  Created on: 9/9/2016
 *      Author: Marcelo
 */

#include "sAPI.h"
#include "leds.h"

delay_t ledDelay;
uint16_t cicloLed1,cicloLed2,cicloLed3;
int16_t loadCicloLed1,loadCicloLed2,loadCicloLed3;
bool_t statusLed1,statusLed2,statusLed3;
bool_t startLed1,startLed2,startLed3;

enum{
	LED_INIT,
	LED_BLINK,
};

void initLeds(void);

void ledOn(uint8_t led){
	ledBlink(led,-1);
}

void ledOff(uint8_t led){
	ledBlink(led,0);
}

void ledBlink(uint8_t led, int16_t ciclo){
	switch(led){
	case LED1:
		loadCicloLed1=ciclo;
		cicloLed1=0;
		startLed1=1;
		break;
	case LED2:
		loadCicloLed2=ciclo;
		cicloLed2=0;
		startLed2=1;
		break;
	case LED3:
		loadCicloLed3=ciclo;
		cicloLed3=0;
		startLed3=1;
		break;
	}
}

void fsmControlLed(void){
	static uint8_t status=LED_INIT;

	switch (status){
	case LED_INIT:
		digitalConfig(0, ENABLE_DIGITAL_IO);
		initLeds();
		delayConfig(&ledDelay, 1);
		status=LED_BLINK;
		break;
	case LED_BLINK:
		if(delayRead(&ledDelay)){
			if(loadCicloLed1>0){
				if(cicloLed1) cicloLed1--;
				else{
					if(startLed1){
						startLed1 = 0;
						statusLed1 = 1;
					}
					cicloLed1 = loadCicloLed1;
					digitalWrite(LED1,statusLed1);
					statusLed1 ^= 1;
				}
			}else if(loadCicloLed1==-1) digitalWrite(LED1,ON);
			else digitalWrite(LED1,OFF);

			if(loadCicloLed2){
				if(cicloLed2) cicloLed2--;
				else{
					if(startLed2){
						startLed2 = 0;
						statusLed2 = 1;
					}
					cicloLed2 = loadCicloLed2;
					digitalWrite(LED2,statusLed2);
					statusLed2 ^= 1;
				}
			}else if(loadCicloLed2==-1) digitalWrite(LED2,ON);
			else digitalWrite(LED2,OFF);

			if(loadCicloLed3){
				if(cicloLed3) cicloLed3--;
				else{
					if(startLed3){
						startLed3 = 0;
						statusLed3 = 1;
					}
					cicloLed3 = loadCicloLed3;
					digitalWrite(LED3,statusLed3);
					statusLed3 ^= 1;
				}
			}else if(loadCicloLed3==-1) digitalWrite(LED3,ON);
			else digitalWrite(LED3,OFF);
		}
		break;
	}
}

void initLeds(void){
	digitalConfig( LED1, OUTPUT );
	digitalConfig( LED2, OUTPUT );
	digitalConfig( LED3, OUTPUT );
}
