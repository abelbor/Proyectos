/*
Versión con dos MEF aplicando switch-case en ambas
*/

#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
};

enum{
	LED_R_ON,
	LED_G_ON,
	LED_B_ON,
	LED_1_ON,
	LED_2_ON,
	LED_3_ON,
	LEDS_OFF,
};

volatile unsigned char debounce;
unsigned char estadoLed=OFF;

void initLeds(void);
void initTec(void);
void fsmDebounce(void);
void fsmControlLed(void);

int main(void)
{
   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolución de 1ms */
   tickConfig(1,0);

   /* Inicializar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );
   
   /* Inicializa LEDs y teclas de la EDU-CIAA-NXP */
   initLeds();
   initTec();

   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {

		fsmDebounce();
		delay(1);
		if(debounce) debounce--;
	}
	return 0;
}

void fsmDebounce(void){
	static unsigned char status=BUTTON_UP;
	
	switch(status){
		case BUTTON_UP:
			if(digitalRead(TEC1)==0){
				debounce=40;
				status = BUTTON_FALLING;
			}
			break;
		case BUTTON_FALLING:
			if(!debounce){
				if(digitalRead(TEC1)==0){
					fsmControlLed();
					status=BUTTON_DOWN;
				}else status=BUTTON_UP;
			}
			break;
		case BUTTON_DOWN:
			if(digitalRead(TEC1)==1){
				debounce=40;
				status = BUTTON_RISING;
			}
			break;
		case BUTTON_RISING:
			if(!debounce){
				if(digitalRead(TEC1)==1) status=BUTTON_UP;
				else status=BUTTON_DOWN;
			}
			break;
		default:
			status = BUTTON_UP;
			break;
	}
}

void fsmControlLed(void){
	static unsigned char status=LED_R_ON;
	
	switch(status){
		case LED_R_ON:
			digitalWrite( LEDR, ON );
			status=LED_G_ON;
			break;
		case LED_G_ON:
			digitalWrite( LEDR, OFF );
			digitalWrite( LEDG, ON );
			status=LED_B_ON;
			break;
		case LED_B_ON:
			digitalWrite( LEDG, OFF );
			digitalWrite( LEDB, ON );
			status=LED_1_ON;
			break;
		case LED_1_ON:
			digitalWrite( LEDB, OFF );
			digitalWrite( LED1, ON );
			status=LED_2_ON;
			break;
		case LED_2_ON:
			digitalWrite( LED1, OFF );
			digitalWrite( LED2, ON );
			status=LED_3_ON;
			break;
		case LED_3_ON:
			digitalWrite( LED2, OFF );
			digitalWrite( LED3, ON );
			status=LEDS_OFF;
			break;
		case LEDS_OFF:
		default:
			digitalWrite( LEDR, OFF );
			digitalWrite( LEDG, OFF );
			digitalWrite( LEDB, OFF );
			digitalWrite( LED1, OFF );
			digitalWrite( LED2, OFF );
			digitalWrite( LED3, OFF );
			status=LED_R_ON;
			break;
	}
}

void initTec(void){
	digitalConfig( TEC1, INPUT );
	digitalConfig( TEC2, INPUT );
	digitalConfig( TEC3, INPUT );
	digitalConfig( TEC4, INPUT );
}

void initLeds(void){
	digitalConfig( LEDR, OUTPUT );
	digitalConfig( LEDG, OUTPUT );
	digitalConfig( LEDB, OUTPUT );
	digitalConfig( LED1, OUTPUT );
	digitalConfig( LED2, OUTPUT );
	digitalConfig( LED3, OUTPUT );
}