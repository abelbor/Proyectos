/*
 * teclas.c
 *
 *  Created on: 9/9/2016
 *      Author: Marcelo
 */

#include "sAPI.h"
#include "teclas.h"

enum{
	BUTTON_INIT,
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
};

static delay_t tecDelay;

static void initTecla(tecla_t *tecla);

bool_t isPressed (tecla_t *tecla){
	static uint8_t inicia=1;
	bool_t rta=0;

	if(inicia){
		inicia=0;
		digitalConfig(0, ENABLE_DIGITAL_IO);
		delayConfig(&tecDelay, 1);
	}

	switch(tecla->status){
	case BUTTON_INIT:
		initTecla(tecla);
		tecla->status=BUTTON_UP;
		break;
	case BUTTON_UP:
		if(digitalRead(tecla->nro)==tecla->pressed_val){
			tecla->debounce = 40;
			tecla->status = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&tecDelay)){
			if(tecla->debounce) tecla->debounce--;
			else{
				if(digitalRead(tecla->nro)==tecla->pressed_val){
					rta=1;
					tecla->status = BUTTON_DOWN;
				}
				else tecla->status = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(digitalRead(tecla->nro)==tecla->release_val){
			tecla->debounce = 20;
			tecla->status = BUTTON_RISING;
		}
		break;
	case BUTTON_RISING:
		if(delayRead(&tecDelay)){
			if(tecla->debounce) tecla->debounce--;
			else{
				tecla->status=BUTTON_UP;
				if(digitalRead(tecla->nro)==tecla->pressed_val) tecla->status=BUTTON_DOWN;
			}
		}
		break;
	default:
		tecla->status = BUTTON_INIT;
		break;
	}
	return rta;
}

void initTecla(tecla_t *tecla){
	digitalConfig( tecla->nro, INPUT );
	tecla->pressed_val = 0;
	tecla->release_val = 1;
}
