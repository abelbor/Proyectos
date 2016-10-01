#include "main.h"
#include "sAPI.h"
#include "configTecLed.h"
#include "debounceMef.h"

typedef enum{ UP, FALLING, DOWN, RISING } estadoMEF;

#define	DEBOUNCE_DELAY 40 //MS

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
estadoMEF estado;

uint8_t estadoActual=1;
uint8_t estadoAnterior=0;
int8_t led = 0;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

	//inicializa la maquina de estado
void IniciaMEF(void){
	estado = UP;
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
				led= !led;//Control();
				}
		    else 
				estado= DOWN;	

			break;
		
		
		default:
				IniciaMEF();
		break;
 }//fin switch
}//fin actualizaMEF
