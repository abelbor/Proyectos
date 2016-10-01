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

/*==================[macros and definitions]=================================*/
typedef enum{ ROJO, AMARILLO, VERDE } estadoMEF;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
estadoMEF estadoActual;

uint8_t tiempocumplido = 0;
uint8_t trojo;
uint8_t tverde;
uint8_t tamarillo;
uint8_t data;
uint8_t opcion=1;
uint8_t ingrese_tiempo[] = "ingrese tiempo:\r\n";

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

	//inicializa la maquina de estado
void IniciaMEF(void){
	estadoActual = ROJO;
	}

	//actualiza la maquina de estado
void ActualizaMEF(void){
	switch (estadoActual){

		case ROJO:
			ponerEnRojo();
			if (tiempocumplido==trojo){
				estadoActual=AMARILLO;
				tiempocumplido=0;			
				}
			
		break;
		
		case AMARILLO:
			ponerEnAmarillo();
			if (tiempocumplido==tamarillo){
				estadoActual=VERDE;
				tiempocumplido=0;				
				}
			
			break;
		
		case VERDE:
			ponerEnVerde();
			if (tiempocumplido==tverde){
				estadoActual=ROJO;
				tiempocumplido=0;				
				}
			
			break;

		default:
				IniciaMEF();
		break;
 }//fin switch
}//fin actualizaMEF

/* Prendo solo el led verde del semáforo, apago los demás */
void ponerEnVerde(void){
	digitalWrite( LEDG, ON );
	digitalWrite( LED1, OFF );
	digitalWrite( LED2, OFF );
}

/* Prendo solo el led amrillo del semáforo, apago los demás */
void ponerEnAmarillo(void){
	digitalWrite( LEDG, OFF );
	digitalWrite( LED1, ON );
	digitalWrite( LED2, OFF );
}

/* Prendo solo el led rojo del semáforo, apago los demás */
void ponerEnRojo(void){
	digitalWrite( LEDG, OFF );
	digitalWrite( LED1, OFF );
	digitalWrite( LED2, ON );
}

/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

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

   /* Configuración de pines de entrada para
	   Teclas de la CIAA-NXP */
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );

   /* Configuración de pines de salida para
	   Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );

   /* config UART */

   uartConfig( UART_USB, 115200 );

   /* Variable de Retardo no bloqueante */
		delay_t delayBase;

   /* Inicializar Retardo no bloqueante con tiempo en ms
	   500 ms = 0,5 s */
        delayConfig( &delayBase, 500 );

// Inicializa la maquina de estado al arrancar o al tildarse
	IniciaMEF();
   
	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		//chequea teclado y hace eco del ultimo recibido
		//opcion = uartReadByte( UART_USB );
		while (opcion!=13){
		if (opcion){
			data=opcion;
			opcion = uartReadByte( UART_USB );
			uartWriteByte( UART_USB, opcion );
     		}
		//Tiempo de amarillo cambia a 10 seg sino mantiene 1 seg

		if (data=='a'){
			tamarillo=10;
			uartWriteByte( UART_USB, 'A' );
			uartWriteByte( UART_USB, '\r' );
		}

		else{tamarillo=1;}

		//Tiempo de verde cambia a 10 seg sino mantiene 1 seg

		if (data=='v'){
			tverde=10;
			uartWriteByte( UART_USB, 'V' );
			uartWriteByte( UART_USB, '\r' );
		}
		else{tverde=1;}

		//Tiempo de rojo cambia a 10 seg, sino a 1 seg
		if (data=='r'){
			trojo=10;
			uartWriteByte( UART_USB, 'R' );
			uartWriteByte( UART_USB, '\r' );
		  }
		else{trojo=1;}

		ActualizaMEF();

		//delayRead retorna TRUE cuando se cumple el tiempo de retardo 
		if ( delayRead( &delayBase ) ){
			tiempocumplido++;
		
		}
        
	opcion = uartReadByte( UART_USB );
   }//ENTER
		uartWriteString( UART_USB, ingrese_tiempo );


  }//while 1

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}//main

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
