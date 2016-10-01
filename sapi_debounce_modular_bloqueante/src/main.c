#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "debounce.h"
#include "led.h"


led_t lamparaAzul;
led_t lamparaVerde;
led_t lamparaRojo;
led_t lamparaRed;
led_t lamparaGreen;

//tecla_t T1;
//tecla_t T2;

bool_t izquierda;
bool_t derecha;
bool_t cambioAngulo;

/* Variable de Retardo no bloqueante */
delay_t delay2;

bool_t valor = 0;
uint8_t servoAngle = 0; /* 0 a 180 grados */
int i=0;
int Angulos[3]={15,30,45};
int Step=0;                 //Pasos de angulos
int AnguloAsignado=0;
int main(void)
{

	boardConfig();   //Inicializar la placa
	tickConfig(1, 0);   //Inicializar el conteo de Ticks con resolución de 1ms
	digitalConfig(0, ENABLE_DIGITAL_IO);  //Inicializar DigitalIO

	ConfigTeclas(TEC1,TEC2,TEC3,TEC4);

	/* Inicializar Retardo no bloqueante con tiempo en ms
			   500 ms = 0,5 s */
	delayConfig (&delay2 , 500);

	ledConfig(&lamparaAzul,LEDB);
	ledConfig(&lamparaRed,LEDR);
	ledConfig(&lamparaGreen,LEDG);
	ledConfig(&lamparaVerde,LED3);
	ledConfig(&lamparaRojo,LED2);
	//delayConfig(&Tiempo1, 1); //tiempo de espera antirebote

	/*Configurar Servo */
	valor = servoConfig( 0,      ENABLE_SERVO_TIMERS );
	valor = servoConfig( SERVO0, ENABLE_SERVO_OUTPUT );

	/* Usar Servo */
	valor = servoWrite( SERVO0, servoAngle );
	servoAngle = servoRead( SERVO0 );
	/* config UART */
	uartConfig( UART_USB, 115200 );

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while (1) {
		cambioAngulo=ActualizaMef(&T3,TEC3);
		if (cambioAngulo){
			Step=Angulos[i];
			i++;
			if (i>2) i=0;
			//uartWriteByte( UART_USB, AnguloCorrido-48 );
		}

		izquierda=ActualizaMef(&T1,TEC1);
		if (izquierda && (AnguloAsignado<=180)){

			AnguloAsignado=Step+AnguloAsignado;
			if ( !delayRead( &delay2 ) )
				servoWrite( SERVO0, AnguloAsignado );
		}
		else{
			if(AnguloAsignado>180)AnguloAsignado=180;
		}

		derecha=ActualizaMef(&T2,TEC2);
		if (derecha && (AnguloAsignado<=180)){

			AnguloAsignado=AnguloAsignado-Step;
			if ( !delayRead( &delay2 ) )
				servoWrite( SERVO0, AnguloAsignado );
		}
		else{
			if(AnguloAsignado>180)AnguloAsignado=0;
		}


	}//while

	return 0;
}

