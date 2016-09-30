/*
 * Este script permite "depurar" los estado de la MEF
 * de led cada vez que la maquina cambia de estado.
 * Funciona con TEC4
 * */
#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */

//Lista de estados
enum States { 
	UP,
	FALLING,
	DOWN,
	RISING
};

#define	DEBOUNCE_DELAY 40 //MS

/* ------------- INICIALIZACIONES ------------- */
void init(void){

	/* Inicializar la placa */
	boardConfig();

	/* Inicializar el conteo de Ticks con resolución de 1ms */
	tickConfig(1, 0);

	/* Inicializar DigitalIO */
	digitalConfig(0, ENABLE_DIGITAL_IO);

	/* Configuración de pines de salida para
	 Leds de la CIAA-NXP */
	digitalConfig(LEDR, OUTPUT);
	digitalConfig(LEDG, OUTPUT);
	digitalConfig(LEDB, OUTPUT);
	digitalConfig(LED1, OUTPUT);
	digitalConfig(LED2, OUTPUT);
	digitalConfig(LED3, OUTPUT);
	
	/* Configuración de pines de entrada para
	Teclas de la CIAA-NXP */
	digitalConfig( TEC1, INPUT );
	digitalConfig( TEC2, INPUT );
	digitalConfig( TEC3, INPUT );
	digitalConfig( TEC4, INPUT );	
}

//funciones que definen el encendido y apagado de leds
void isUp(void){
	digitalWrite( LEDR, 1 );
	digitalWrite( LED1, 0 );
	digitalWrite( LED2, 0 );
	digitalWrite( LED3, 0 );
}

void isFalling(void){
	digitalWrite( LEDR, 0 );
	digitalWrite( LED1, 1 );
	digitalWrite( LED2, 0 );
	digitalWrite( LED3, 0 );
}

void isDown(void){
	digitalWrite( LEDR, 0 );
	digitalWrite( LED1, 0 );
	digitalWrite( LED2, 1 );
	digitalWrite( LED3, 0 );
}

void isRising(void){
	digitalWrite( LEDR, 0 );
	digitalWrite( LED1, 0 );
	digitalWrite( LED2, 0 );
	digitalWrite( LED3, 1 );
}

int main(void) {
	
	//Configura las I/O
	init();	

	enum States state = UP;
	
	uint8_t estadoActual= 1;
	uint8_t estadoAnterior = 0;
	uint8_t ledOn = 0;
	
	while(1) {
		switch(state) {
			case UP:
				isUp(); //LEDR indica que la MEF esta en UP
				estadoAnterior = 1;
				estadoActual = digitalRead( TEC4 );
				if(estadoActual != estadoAnterior){
					state = FALLING;
				}				
				break;
			case FALLING:				
				isFalling(); //LED1 indica que la MEF esta en FALLING
				delay(DEBOUNCE_DELAY);
				estadoActual = digitalRead( TEC4 );				
				if(estadoActual != estadoAnterior){
					state = DOWN;
				} else {
					state = UP;	
				}
				break;
			case DOWN:
				isDown(); //LED2 indica que la MEF esta en DOWN
				estadoAnterior = 0;
				//ledOn = !ledOn;
				//digitalWrite( LED3, ledOn );
				estadoActual = digitalRead( TEC4 );
				
				if(estadoActual != estadoAnterior){
					state = RISING;
				}
				break;
			case RISING:
				isRising(); //LEDR indica que la MEF esta en RISING
				delay(DEBOUNCE_DELAY);
				estadoActual = digitalRead( TEC4 );
				
				if(estadoActual != estadoAnterior){
					state = UP;
				} else {
					state = DOWN;
				}
				break;
		}
	}

	return 0;
}
