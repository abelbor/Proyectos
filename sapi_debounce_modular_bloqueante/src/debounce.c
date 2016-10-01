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

typedef enum{UP, FALLING, RISING, DOWN} estadoTecla;

delay_t teclaDelay;


bool_t TeclaConfig( tecla_t * tecla, uint8_t digitalIn ){
	tecla->digitalInput = digitalIn;
	tecla->estadoTec=0;           //estado de tecla
	tecla->tiempoDeb;          //tiempo de debounce
	tecla->estadoEnum= UP;     //ESTADO INICIAL DE MAQUINA
	digitalConfig( tecla->digitalInput, INPUT );

	return tecla->estadoTec;
}

bool_t TeclaRead( tecla_t * tecla ){
	tecla->estadoTec=digitalRead(tecla->digitalInput);
	return tecla->estadoTec;
}
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void ConfigTeclas(uint8_t Tuno,uint8_t Tdos, uint8_t Ttres, uint8_t Tcuatro){
	TeclaConfig( &T1, Tuno );
	TeclaConfig( &T2, Tdos );
	TeclaConfig( &T3, Ttres );
	TeclaConfig( &T4, Tcuatro );
}


bool_t ActualizaMef( tecla_t * tecla, uint8_t digitalIn ){
	static uint8_t inicial=1;
	bool_t rta=0;

	if(inicial){
		inicial=0;
		delayConfig(&teclaDelay, 1);
	}
	tecla->digitalInput = digitalIn; //asigna que tecla recibe
	//tecla->estadoTec=OFF;
	switch (tecla->estadoEnum) {
	case UP:
		if (digitalRead(tecla->digitalInput)==0) {
			tecla->estadoEnum = FALLING;
		}
		break;
	case FALLING:
		delay(40);
		if (digitalRead(tecla->digitalInput)==0) {
			tecla->estadoEnum = DOWN;
		} else{
			tecla->estadoEnum = UP;
		}
		break;
	case DOWN:
		if (digitalRead(tecla->digitalInput==1)) {
			tecla->estadoEnum = RISING;
		}
		break;
	case RISING:
		delay(40);
		if (digitalRead(tecla->digitalInput)==1) {
			tecla->estadoEnum = UP;
			bool_t rta=1;//tecla->estadoTec=ON;//accion
		}
		else{
			tecla->estadoEnum = DOWN;
		}
		break;
	default:
		tecla->estadoEnum = UP;
		break;
	}
	return rta;
}

