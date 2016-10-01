#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "debounce.h"
#include "led.h"

static tecla_t T1;
static tecla_t T2;
static tecla_t T3;

led_t lamparaAzul;

int main(void)
{

	boardConfig();   //Inicializar la placa
	tickConfig(1, 0);   //Inicializar el conteo de Ticks con resolución de 1ms
	digitalConfig(0, ENABLE_DIGITAL_IO);  //Inicializar DigitalIO

	TeclaConfig(&T1, TEC1);
	TeclaConfig(&T2, TEC2);
	TeclaConfig(&T3, TEC3);

	ledConfig(&lamparaAzul,LEDB);

	IniciarMef();


	//delayConfig(&Tiempo1, 1); //tiempo de espera antirebote


	/* ------------- REPETIR POR SIEMPRE ------------- */
	while (1) {
		ActualizaMef();
		if(ActualizaMef()){
			ledOn(&lamparaAzul);
		}
		else{
			ledOff(&lamparaAzul);
		}
		}



	return 0;
}

