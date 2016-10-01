/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Main example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Main example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * ENP          Eric Pernia
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 2016-04-26   v0.0.1   First version
 */

/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */
#include "sAPI.h"         /* <= sAPI header */
#include "configTecLed.h"
//#include "debounceMef.h"

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
   /* Configura teclas y leds Edu-Ciaa */
   configTecLed();
   
   /* config UART */
   uartConfig( UART_USB, 115200 );

   /* Inicializar AnalogIO */
   /* Posibles configuraciones:
   *    ENABLE_ANALOG_INPUTS,  DISABLE_ANALOG_INPUTS,
   *    ENABLE_ANALOG_OUTPUTS, DISABLE_ANALOG_OUTPUTS
   */
   analogConfig( ENABLE_ANALOG_INPUTS );  /* ADC */
   analogConfig( ENABLE_ANALOG_OUTPUTS ); /* DAC */

   /* Variable para almacenar el valor leido del ADC CH1 */
   uint16_t muestra = 0;

   bool_t valor = 0;
   extern delay_t delay1;
   extern delay_t delay2;
   bool_t led_state = 0;

   uint8_t servoAngle = 0; /* 0 a 180 grados */

   /*Configurar Servo */
   valor = servoConfig( 0,      ENABLE_SERVO_TIMERS );
   valor = servoConfig( SERVO0, ENABLE_SERVO_OUTPUT );

   /* Usar Servo */
   valor = servoWrite( SERVO0, servoAngle );
   servoAngle = servoRead( SERVO0 );

   digitalWrite( LEDB, 0 );

   delayConfig (&delay1 , 200);
   delayConfig (&delay2 , 200);


  
  //Inicializa la maquina de estado al arrancar o al tildarse
	IniciaMEF();

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		
		ActualizaMEF();
		switch(led){

		case 1:
			ControlServoUart(); /*controla el servo por uart*/
		break;

		case 0:
			ControlServoAdc();/*controla el servo por potenciometro*/
		break;
		}
			
 }//while 1

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}//main

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
