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

int main(void) {
	
	//Configura las I/O
	init();	
	
	//setea el estado inicial
	enum States state = UP;
	
	uint8_t estadoActual= 1;
	uint8_t estadoAnterior = 0;
	uint8_t led = 0;
	
	while(1) {
		switch(state) {
			case UP:
				estadoAnterior = estadoActual;
				estadoActual = digitalRead( TEC4 );
				if(estadoActual != estadoAnterior){
					state = FALLING;
				}				
				break;
			case FALLING:				
				delay(DEBOUNCE_DELAY);
				estadoActual = digitalRead( TEC4 );				
				if(estadoActual != estadoAnterior){
					state = DOWN;
				} else {
					state = UP;	
				}
				break;
			case DOWN:
				estadoAnterior = 0;
				
				estadoActual = digitalRead( TEC4 );
				
				if(estadoActual != estadoAnterior){
					state = RISING;
				}
				break;
			case RISING:
				delay(DEBOUNCE_DELAY);
				estadoActual = digitalRead( TEC4 );
				
				if(estadoActual != estadoAnterior){
					state = UP;
					led = !led; //cambia el led
				} else {
					state = DOWN;
				}
				break;
		}
		digitalWrite( LED3, led );
		
	}

	return 0;
}
