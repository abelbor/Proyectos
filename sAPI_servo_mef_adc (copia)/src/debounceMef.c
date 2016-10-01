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
			led= !led;
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
	digitalWrite( LED1, 0 );
	opcion = uartReadByte( UART_USB );/*consulta ingresos*/

	  if (opcion){
		posicion=opcion;
		opcion = uartReadByte( UART_USB );
		uartWriteByte( UART_USB, opcion );
		}

	switch (posicion){
		case '0':
			servoWrite( SERVO0, 0 );
			delay(200);
		break;
		case '1':
			servoWrite( SERVO0, 18 );
		    delay(200);
		break;
		case '2':
			servoWrite( SERVO0, 36 );
			delay(200);
		break;
		case '3':
			servoWrite( SERVO0, 72 );
			delay(200);
		break;
		case '4':
			servoWrite( SERVO0, 90 );
			delay(200);
		break;
		case '5':
			servoWrite( SERVO0, 108 );
			delay(200);
		break;
		case '6':
			servoWrite( SERVO0, 126 );
			delay(200);
		break;
		case '7':
			servoWrite( SERVO0, 144 );
			delay(200);
		break;
		case '8':
			servoWrite( SERVO0, 162 );
			delay(200);
		break;
		case '9':
			servoWrite( SERVO0, 180 );
			delay(200);
		break;
	}//switch posicion
}// fin controlservouart

void ControlServoAdc(void){

	digitalWrite( LED1, 1 );
/* retorna TRUE cuando se cumple retardo, ES EL TIEMPO DE MUESTREO */
	   if ( delayRead( &delay1 ) ){
/* Leo la Entrada Analogica AI0 - ADC0 CH1 */
		  muestra = analogRead( AI0 );

/* cheque el valor de la variable "muestra", segun valor, enciende ciertos leds */
	   if ( muestra <= 0 ){
		   if ( !delayRead( &delay2 ) ){
		    servoWrite( SERVO0, 0 );
	        }//delay(200);
			 }
	   else if ( muestra <= 102 ){
			servoWrite( SERVO0, 18 );
			delay(200);
			 }
	   else if ( muestra <= 204 ){
			servoWrite( SERVO0, 36 );
			delay(200);
			 }
	   else if ( muestra <= 306 ){
			servoWrite( SERVO0, 54 );
			delay(200);
			 }
	   else if ( muestra <= 408 ){
			servoWrite( SERVO0, 72 );
			delay(200);
			 }
	   else if ( muestra <= 510 ){
			servoWrite( SERVO0, 90 );
			delay(200);
			 }
	   else if ( muestra <= 612 ){
			servoWrite( SERVO0, 108 );
			delay(200);
			 }
	   else if ( muestra <= 714 ){
			servoWrite( SERVO0, 126 );
			delay(200);
			 }
	   else if ( muestra <= 816 ){
			servoWrite( SERVO0, 144 );
			delay(200);
			 }
	   else if ( muestra <= 918 ){
			servoWrite( SERVO0, 162 );
			delay(200);
			 }
	   else if ( muestra <= 1020 ){
			servoWrite( SERVO0, 180 );
			delay(200);
			 }
      }//if delayRead
 }//fun ControlServoAdc






