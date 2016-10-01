/* Copyright 2016, Abel Bortolameotti.
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

/* Date: 2016-09-18 */

/*==================[inclusions]=============================================*/

#include "sAPI.h"         /* <= sAPI header */
#include "debounce.h"         /* <= own header */
#include "led.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
/* Variable de Retardo no bloqueante */
delay_t delayBase;


typedef enum{UP, FALLING, RISING, DOWN} estadoTecla;
static estadoTecla estado;

int accion=0;
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

bool_t TeclaConfig( tecla_t * tecla, uint8_t digitalIn ){
   tecla->digitalInput = digitalIn;
   tecla->estadoTec=1;
   tecla->tiempoDeb=40;

   digitalConfig( tecla->digitalInput, INPUT );
   delayConfig( &delayBase, 1 );

   return tecla->estadoTec;
}

bool_t TeclaRead( tecla_t * tecla ){
	tecla->estadoTec=digitalRead(tecla->digitalInput);
	return tecla->estadoTec;
}

void IniciarMef(void){
	estado = UP;
}
int ActualizaMef(void){

	switch (estado) {
	case UP:

		if (!TeclaRead()) {
			estado = FALLING;
			//tecla->tiempoDeb=0;
		}
		break;

	case FALLING:
		delay(40);
		//if ( (tecla->tiempoDeb)>40 )

		if (!TeclaRead()) {
			estado = DOWN;
			//	tecla->tiempoDeb=0;
		} else
			estado = UP;

		break;

	case DOWN:

		if (TeclaRead()) {
			estado = RISING;
			//tecla->tiempoDeb=0;
		}
		break;

	case RISING:
		//if ( (tecla->tiempoDeb)>40 )
		delay(40);

		if (TeclaRead()) {
			estado = UP;
			accion=!accion;                //accion
			//	tecla->tiempoDeb=0;
		}
		else
		{estado = DOWN;}
		break;

	default:
		IniciarMef();
		break;
	}
	/* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
	//	if ( delayRead( &delayBase ) ){
	//		(tecla->tiempoDeb)++;
	//	}
	return accion;
}
	//delayread 40



