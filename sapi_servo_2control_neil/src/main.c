#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */


 uint8_t TiempoTranscurrido=0, var=0,varTec=0,option=0,
 data=0,servoAngle=0,UnoCero=0, ang[10]={0,20,40,60,80,100,120,140,160,180};
 uint16_t muestra = 0;

 delay_t Tiempo1;
 delay_t Tiempo2;

 typedef enum{UP, FALLING, RISING, DOWN} estadoTecla;
 estadoTecla TecActual;

//---------------------------------------------------------------------
//------FUNCION QUE CONTROLA EL SERVO MEDIANTE UART--------------------
//---------------------------------------------------------------------

 void controlUart(void){

	 option = uartReadByte(UART_USB);
	 while ( (varTec==1) && (option != 13)) {

		 ActualizarTecla();

		 if (delayRead(&Tiempo1)){						//------------
			 UnoCero =!UnoCero;				//    ACA  SE HACE
			 digitalWrite( LED2, UnoCero );	//   EL BLINKY
			 digitalWrite( LED1, OFF);		//  DEL LED 2
		 }								//------------

		 if (option)
			 data = option;

		 option = uartReadByte(UART_USB);
		 uartWriteByte(UART_USB, option);

	 }
	 if (data==0) data=48;       		//CONDICION POR SI NO SE INTRODUCE
	 //NINGUN VALOR

	 servoWrite( SERVO0, ang[data-48] );



 }

 //---------------------------------------------------------------------
 //-----FUNCION QUE CONTROLA EL SERVO MEDIANTE ADC ---------------------
 //---------------------------------------------------------------------

 void controlAdc(void){

	 if (delayRead(&Tiempo2)){					//----------------
			UnoCero =!UnoCero;					//  ACA SE HACE
			digitalWrite( LED1,UnoCero );		//	EL BLINKY
			digitalWrite( LED2, OFF);			//   DEL LED1
	 						}					//----------------

	  	muestra = analogRead( AI0 );  	//LECTURA DEL CANAL1
 	option = (muestra * 180)/1023;		//REGLA DE 3 , PARA OBTENER LOS GRADOS

 	servoWrite( SERVO0, option );

 }


 //----------------------------------------------------------------------


void IniciarTecla(void){
        TecActual = UP;
        }


//---------------------------------
//     MEF de la tecla
//-----------------------------------
void ActualizarTecla(void){
	switch (TecActual) {
	case UP:
		if (!digitalRead(TEC1)) {
			TecActual = FALLING;
		}
		var = 0;

		break;

	case FALLING:
		delay(40);
		if (!digitalRead(TEC1)) {

			TecActual = DOWN;
		} else
			TecActual = UP;

		break;

	case DOWN:
		if (var == 0) {
			if (varTec == 0){
				varTec=1;
				//controlAdc();
			}
			else {
				varTec=0;
				//controlUart();
			}
		}
		var = 1;


		if (digitalRead(TEC1)) {
			TecActual = RISING;
		}

		break;

	case RISING:
		delay(40);
		if (digitalRead(TEC1)) {
			TecActual = UP;

		} else {
			TecActual = DOWN;

		}

		break;

	default:
		IniciarTecla();

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

	analogConfig( ENABLE_ANALOG_INPUTS );  /* ADC */

	uartConfig(UART_USB, 115200);

	IniciarTecla();

	delayConfig(&Tiempo1, 500);   	//tiempo blinky led2
	delayConfig(&Tiempo2, 1000);	//tiempo blinky led1


	  /* Configurar Servo */
	  servoConfig( 0,      ENABLE_SERVO_TIMERS );

	  servoConfig( SERVO0, ENABLE_SERVO_OUTPUT );



	/* ------------- REPETIR POR SIEMPRE ------------- */
	  while (1) {
		  ActualizarTecla();

		  if(varTec)
			  controlUart();

		  else
			  controlAdc();


	  }
	  return 0 ;
 }

