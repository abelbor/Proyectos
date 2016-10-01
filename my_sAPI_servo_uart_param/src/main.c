/*
 * main.c
 *
 *  Created on: 9/9/2016
 *      Author: Marcelo
 */

/*
 * UART a 115200
 * Servo 0 (T-F1 EDU-CIAA)
 */

#include "sAPI.h"
#include "peri.h"

const uint8_t msg_aviso[]="El incremento actual es de: ";
const uint8_t msg_aviso2[]=" grados\r\n";

uint8_t grados,step=15;
delay_t servoDelay;

tecla_t tecla1,tecla2,tecla3;

void appServo(void);

int main(){
	/* Inicializar la placa */
	boardConfig();

	/* Inicializar el conteo de Ticks con resolución de 1ms, sin tickHook */
	tickConfig( 1, 0 );

	(void)servoConfig(0,ENABLE_SERVO_TIMERS);
	(void)servoConfig(SERVO0,ENABLE_SERVO_OUTPUT);
	delayConfig(&servoDelay, 300);

	tecla1.nro=TEC1;
	tecla2.nro=TEC2;
	tecla3.nro=TEC3;

	ledBlink(LED1,500);

	uartConfig(UART_USB,115200);

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {

		if(isPressed(&tecla1)){
			grados += step;
			if(grados > 180) grados = 180;
		}
		if(isPressed(&tecla2)){
			grados -= step;
			if(grados > 180) grados = 0;
		}
		if(isPressed(&tecla3)){
			if(step==15){
				step = 30;
				ledOff(LED1);
				ledBlink(LED2,500);
			}else if(step==30){
				step = 45;
				ledOff(LED2);
				ledBlink(LED3,500);
			}else{
				step = 15;
				ledOff(LED3);
				ledBlink(LED1,500);
			}
			uartWriteString(UART_USB,(uint8_t *)(msg_aviso));
			uartWriteByte(UART_USB,((step / 10)|0x30));
			uartWriteByte(UART_USB,((step % 10)|0x30));
			uartWriteString(UART_USB,(uint8_t *)(msg_aviso2));
		}
		fsmControlLed();
		appServo();
	}
	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
	return 0 ;
}

void appServo(void){
	static int8_t grados_ant=-1;

	if((delayRead(&servoDelay))&&(grados != grados_ant)){
		grados_ant=grados;
		servoWrite(SERVO0,grados);
	}
}
