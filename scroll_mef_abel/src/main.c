/* al pulsar la tecla se encienden los leds sucesivamente desde el LED1 
 hasta completar toda la secuencia
/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "configTecLed.h"

extern int8_t led;

 /* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolución de 1ms */
   tickConfig(1,0);

   /* Inicializar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );

   configTecLed();
  
// Inicializa la maquina de estado al arrancar o al tildarse
	IniciaMEF();//maquina debounce
  	IniciaControl();//MEF que controla los leds
	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		
		ActualizaMEF();
            	
  }

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
