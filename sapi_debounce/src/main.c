#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */


uint8_t ciclos=0,accion=0;

delay_t Tiempo1;

typedef enum{UP, FALLING, RISING, DOWN} estadoTecla;

estadoTecla estado;

void IniciaMef(void){
	estado = UP;
}

//---------------------------------
//     MEF de la tecla
//-----------------------------------
void ActualizarTecla(void){
	switch (estado) {
	case UP:
		if (!digitalRead(TEC1)) {
			estado = FALLING;
			ciclos=0;
		}
		break;

	case FALLING:
		if ( ciclos>40 )
			if (!digitalRead(TEC1)) {
				estado = DOWN;
				ciclos=0;
			} else
				estado = UP;

		break;

	case DOWN:

		if (digitalRead(TEC1)) {
			estado = RISING;
			ciclos=0;
		}
		break;

	case RISING:
		if ( ciclos>40 )
			if (digitalRead(TEC1)) {
				estado = UP;
				accion=!accion;//toglea una accion o un led o ejecuta funcion
				ciclos=0;
			}
			else
				estado = DOWN;
		break;

	default:
		IniciaMef();
		break;
	}

}

int main(void)
{

	boardConfig();   //Inicializar la placa
	tickConfig(1, 0);   //Inicializar el conteo de Ticks con resolución de 1ms
	digitalConfig(0, ENABLE_DIGITAL_IO);  //Inicializar DigitalIO

	digitalConfig(TEC1, INPUT);
	digitalConfig(TEC2, INPUT);
	digitalConfig(TEC3, INPUT);
	digitalConfig(TEC4, INPUT);

	digitalConfig(LEDR, OUTPUT);
	digitalConfig(LEDG, OUTPUT);
	digitalConfig(LEDB, OUTPUT);
	digitalConfig(LED1, OUTPUT);
	digitalConfig(LED2, OUTPUT);
	digitalConfig(LED3, OUTPUT);

	IniciaMef();

	delayConfig(&Tiempo1, 1); //tiempo de espera antirebote


	/* ------------- REPETIR POR SIEMPRE ------------- */
	while (1) {
		ActualizarTecla();
		if(delayRead(&Tiempo1)){
			ciclos++;
		}
		digitalWrite(LEDB, accion); //toglea led o puede ser una llamada a funcion cuando se pulsa TEC1

	}
	return 0 ;
}

