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
typedef enum{ r, a, v , b } estadoTiempos;
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
estadoMEF estadoActual;
estadoTiempos tiempoColor;

uint8_t tiempocumplido = 0;
char tiempoascci;
uint8_t data;
uint8_t opcion=1;
uint8_t ingrese_tiempoA[] = " ingrese [0..9] para amarillo y pulse ENTER:\r\n";
uint8_t ingrese_tiempoV[] = " ingrese [0..9] para verde y pulse ENTER:\r\n";
uint8_t ingrese_tiempoR[] = " ingrese [0..9] para rojo y pulse ENTER:\r\n";
uint8_t suelte_boton[] = "SOLTAR TECLA 4 y luego pulsar ENTER, \r\n debe verse cambios en tiempos de led encendidos \r\n";
uint8_t presentacion[] = "mantenga presionada TECLA 4 mientras cambia los tiempos \r\n con valores del 1 al 9 (segundos) \r\n";
uint8_t valor;
uint8_t dataV;
uint8_t dataR;
uint8_t dataA;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

	//inicializa la maquina de estado
void IniciaMEF(void){
	estadoActual = ROJO;
	}
//inicializa la maquina de estado
void IniciaTiempos(void){
	tiempoColor = v;
	dataA = 2+48;/* 2 segundos guardado como '2' ascci*/
	dataR = 4+48;
	dataV = 4+48;
	}

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

//actualiza la maquina de estado del SEMAFORO
void ActualizaMEF(void){
	switch (estadoActual){
		case ROJO:
			ponerEnRojo();
			tiempoascci=tiempocumplido+48; /*convierto de entero a ascci*/
			if (tiempoascci==dataR){
				estadoActual=AMARILLO;
				tiempocumplido=0;
				tiempoascci='0';
				}
		break;
		
		case AMARILLO:
			ponerEnAmarillo();
			tiempoascci=tiempocumplido+48;/*convierto de entero a ascci*/
			if (tiempoascci==dataA){
				estadoActual=VERDE;
				tiempocumplido=0;
				tiempoascci='0';
				}
		break;
		
		case VERDE:
			ponerEnVerde();
			tiempoascci=tiempocumplido+48;/*convierto de entero a ascci*/
			if (tiempoascci==dataV){
				estadoActual=ROJO;
				tiempocumplido=0;
				tiempoascci='0';
				}
		break;

		default:
				IniciaMEF();
		break;
 }//fin switch
}//fin actualizaMEF

//actualiza la maquina de tiempos segun tecla ingresada
void ActualizaTiempos(void){
	switch (tiempoColor){
		case v:
			uartWriteString( UART_USB, ingrese_tiempoV );
			opcion = uartReadByte( UART_USB );/*consulta ingresos*/
			while (opcion!=13){
				if (opcion){
					dataV=opcion;
					opcion = uartReadByte( UART_USB );
					uartWriteByte( UART_USB, opcion );
					tiempoColor= r; /*cambia estado si entro dato*/
			    	}
				opcion = uartReadByte( UART_USB );
			}
		break;

		case r:
			uartWriteString( UART_USB, ingrese_tiempoR );
			opcion = uartReadByte( UART_USB );/*consulta ingresos*/
			while (opcion!=13){
				if (opcion){
				dataR=opcion;
				opcion = uartReadByte( UART_USB );
				uartWriteByte( UART_USB, opcion );
				tiempoColor= a;/*cambia estado si entro dato*/
				}
				opcion = uartReadByte( UART_USB );
			}
			break;

		case a:
			uartWriteString( UART_USB, ingrese_tiempoA );
			opcion = uartReadByte( UART_USB );/*consulta ingresos*/
			while (opcion!=13){
				if (opcion){
					dataA=opcion;
					opcion = uartReadByte( UART_USB );
					uartWriteByte( UART_USB, opcion );
					tiempoColor= b;/*cambia estado si entro dato*/
					}
				opcion = uartReadByte( UART_USB );
				}
			break;
		case b:
					uartWriteString( UART_USB, suelte_boton );
					opcion = uartReadByte( UART_USB );
					while (opcion!=13){/*hasta no pulsar ENTER NO SALE DEL while*/
						tiempoColor= v;/*cambia estado si entro dato*/
						opcion = uartReadByte( UART_USB );
						}
					break;
		default:
				IniciaTiempos();
		break;
 }//fin switch
}//fin actualizatiempos



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
   	IniciaTiempos();

  // Inicializa la maquina de estado al arrancar o al tildarse
	IniciaMEF();

	/* MUESTRA PRESENTACION*/
	uartWriteString( UART_USB, presentacion );

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {

		valor = !digitalRead( TEC4 );/*tecla a mantener pulsada para que permita cambio de tiempos*/
		if (valor){
			ActualizaTiempos();/*solo si mantengo pulsado pide actualizar tiempos*/
		}
		ActualizaMEF(); /*actualiza el semaforo*/

		//delayRead retorna TRUE cuando se cumple el tiempo de retardo 
		if ( delayRead( &delayBase ) ){
			tiempocumplido++;
		}

  }// FIN while 1

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}//main

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
