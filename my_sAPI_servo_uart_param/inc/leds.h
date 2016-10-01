/*
 * leds.h
 *
 *  Created on: 9/9/2016
 *      Author: Marcelo
 */

#ifndef _LEDS_H_
#define _LEDS_H_

void ledOn(uint8_t led);
void ledOff(uint8_t led);
void ledBlink(uint8_t led, int16_t ciclo);
void fsmControlLed(void);

#endif /* PROYECTOS_MY_BAREMETAL_INC_PERI_LEDS_H_ */
