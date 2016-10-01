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
char posicion='0';
uint8_t opcion=0;

/* Variable para almacenar el valor leido del ADC CH1 */
  uint16_t muestra = 0;
  delay_t delay1;
  delay_t delay2;
  delay_t delay3;
  delay_t delay4;
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
			led= !led; /*togglea el MODO UART A MODO POTENCIOMETRO*/
			}
		else
			estado= DOWN;
		break;

	default:
			IniciaMEF();
	break;
 }//fin switch
}//fin actualizaMEF

void ControlServoUart(void){

	opcion = uartReadByte( UART_USB );/*consulta ingresos*/

	if (opcion){
		posicion=opcion;
		opcion = uartReadByte( UART_USB );
		//uartWriteByte( UART_USB, opcion );
		}

	switch (posicion){
		case '0':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 0 );
		break;

		case '1':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 18 );
		break;

		case '2':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 36 );
		break;

		case '3':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 54 );
		break;

		case '4':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 72 );
		 break;

		case '5':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 90 );
		break;

		case '6':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 126 );
		break;

		case '7':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 144 );
		break;

		case '8':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 162 );
		break;

		case '9':
		 if ( !delayRead( &delay2 ) )
		   servoWrite( SERVO0, 180 );
		break;
	}//switch posicion
}// fin controlservouart

void ControlServoAdc(void){


/* retorna TRUE cuando se cumple retardo, ES EL TIEMPO DE MUESTREO */
	   if ( delayRead( &delay1 ) ){
/* Leo la Entrada Analogica AI0 - ADC0 CH1 */
		  muestra = analogRead( AI0 );

/* cheque el valor de la variable "muestra", segun su rango de valor, usa un angulo para servo  */
	   if ( muestra <= 0 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 0 );
	       }
	   else if ( muestra <= 102 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 18 );
		   }
	   else if ( muestra <= 204 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 36 );
		   }
	   else if ( muestra <= 306 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 54 );
		   }
	   else if ( muestra <= 408 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 72 );
		   }
	   else if ( muestra <= 510 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 90 );
		   }
	   else if ( muestra <= 612 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 108 );
		   }
	   else if ( muestra <= 714 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 126 );
		   }
	   else if ( muestra <= 816 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 144 );
		   }
	   else if ( muestra <= 918 ){
		   if ( !delayRead( &delay2 ) )
		    servoWrite( SERVO0, 162 );
		   }
	   else if ( muestra <= 1020 ){
		   if ( !delayRead( &delay2 ) )
			servoWrite( SERVO0, 180 );
		   }
      }//if delayRead
 }//fun ControlServoAdc






