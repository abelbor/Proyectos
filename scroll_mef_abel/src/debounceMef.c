#include "main.h"
#include "sAPI.h"
#include "configTecLed.h"
#include "debounceMef.h"

#define	DEBOUNCE_DELAY 40 //MS

typedef enum{ UP, FALLING, DOWN, RISING } estadoMEF;

estadoMEF estado;

typedef enum{LED1_ON, LED2_ON, LED3_ON, LEDRGB_ON, LEDS_OFF} MefLeds;

MefLeds estadoLed;

uint8_t estadoActual=1;
uint8_t estadoAnterior=0;
int8_t led = 0;


	//inicializa la maquina de estado
void IniciaMEF(void){
	estado = UP;
	}
void IniciaControl(void){
	estadoLed = LED1_ON;
	}
	//actualiza la maquina de estado
void ActualizaMEF(void){
	switch (estado){

	case UP:
		estadoAnterior=estadoActual;
		estadoActual = digitalRead( TEC1 );
		if (estadoAnterior!=estadoActual){
			estado=FALLING;
			}
			
			
	break;
		
	case FALLING:
		delay(40);
		estadoActual=digitalRead( TEC1 );
		if ((estadoAnterior!=estadoActual)){
			estado=DOWN;
					
			}
		else{ 
			estado=UP;		
			}			

	break;
		
	case DOWN:
		estadoAnterior=0;		
		estadoActual=digitalRead( TEC1 );
		if (estadoAnterior!=estadoActual){
			estado=RISING;
		
			}
			
	break;
	case RISING:
		delay(40);
		estadoActual=digitalRead( TEC1 );
		if (estadoAnterior!=estadoActual){
			estado=UP;
			Control();//led= !led;
			}
		else 
		estado= DOWN;	

	break;
		
	default:
		IniciaMEF();
	break;
 }//fin switch
}//fin actualizaMEF

void Control(void){

	switch(estadoLed){
		case LED1_ON:
			digitalWrite( LED1, ON );
			estadoLed=LED2_ON;
		break;
		
		case LED2_ON:
			digitalWrite( LED1, OFF );
			digitalWrite( LED2, ON );
			estadoLed=LED3_ON;	
		break;
		
		case LED3_ON:
			digitalWrite( LED2, OFF );
			digitalWrite( LED3, ON );
			estadoLed=LEDRGB_ON;
		break;
		
		case LEDRGB_ON:
			digitalWrite( LED3, OFF );
			digitalWrite( LEDR, ON );
			estadoLed=LEDS_OFF;
		break;
		
		case LEDS_OFF:
                        digitalWrite( LEDR, OFF );
			digitalWrite( LEDG, OFF );
			digitalWrite( LEDB, OFF );
			digitalWrite( LED1, OFF );
			digitalWrite( LED2, OFF );
			digitalWrite( LED3, OFF );
			estadoLed=LED1_ON;
		break;
		
		default:
			digitalWrite( LEDR, OFF );
			digitalWrite( LEDG, OFF );
			digitalWrite( LEDB, OFF );
			digitalWrite( LED1, OFF );
			digitalWrite( LED2, OFF );
			digitalWrite( LED3, OFF );
			estadoLed=LED1_ON;
			break;
 }//switch
}// f Control







