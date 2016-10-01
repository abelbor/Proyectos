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

/* Date: 2016-06-06 */

/*==================[inclusions]=============================================*/

#include "main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

#include "led.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/* Variables globales privadas del módulo */
static led_t lamparaVerde;
static led_t lamparaAmarilla;
static led_t lamparaRoja;

/* Variable de Retardo no bloqueante */
static delay_t delayBase;
static uint8_t i = 0;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/* Prendo solo el led verde del semáforo, apago los demás */
static void semaforoPonerEnVerde(void){
   ledOn( &lamparaVerde );
   ledOff( &lamparaAmarilla );
   ledOff( &lamparaRoja );
}

/* Prendo solo el led amrillo del semáforo, apago los demás */
static void semaforoPonerEnAmarillo(void){
   ledOff( &lamparaVerde );
   ledOn( &lamparaAmarilla );
   ledOff( &lamparaRoja );
}

/* Prendo solo el led rojo del semáforo, apago los demás */
static void semaforoPonerEnRojo(void){
   ledOff( &lamparaVerde );
   ledOff( &lamparaAmarilla );
   ledOn( &lamparaRoja );
}

/*==================[external functions definition]==========================*/

void semaforoConfig( uint8_t ledVerde, uint8_t ledAmarillo, uint8_t ledRojo ){

   /* Inicializar Retardo no bloqueante con tiempo en ms
	   500 ms = 0,5 s */
   delayConfig( &delayBase, 500 );

   ledConfig( &lamparaVerde, ledVerde );
   ledConfig( &lamparaAmarilla, ledAmarillo );
   ledConfig( &lamparaRoja, ledRojo );

}

void semaforoUpdate(void){
		/*
		Tiempo de verde 2s
		Tiempo de amarillo 0,5s
		Tiempo de rojo 3s
		*/
		if ( i == 0 ){
			semaforoPonerEnVerde();
		}
		if ( i == 4 ){
			semaforoPonerEnAmarillo();
		}
		if ( i == 5 ){
			semaforoPonerEnRojo();
		}
		if ( i == 11 ){
			semaforoPonerEnAmarillo();
		}
		if ( i == 12 ){
			i = 0;
		}

		/* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
		if ( delayRead( &delayBase ) ){
			i++;
		}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
