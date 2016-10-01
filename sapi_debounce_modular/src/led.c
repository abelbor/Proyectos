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

#include "sAPI.h"         /* <= sAPI header */
#include "led.h"         /* <= own header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

bool_t ledConfig( led_t * led, uint8_t digitalOut ){
   led->digitalOutput = digitalOut;
   led->state = OFF;

   digitalConfig( led->digitalOutput, OUTPUT );

   digitalWrite( led->digitalOutput, led->state );

   return led->state;
}


bool_t ledOn( led_t * led ){
   led->state = ON;
   digitalWrite( led->digitalOutput, led->state );
   return led->state;
}


bool_t ledOff( led_t * led ){
   led->state = OFF;
   digitalWrite( led->digitalOutput, led->state );
   return led->state;
}


bool_t ledToggle( led_t * led ){
   if( led->state )
      led->state = OFF;
   else
      led->state = ON;
   digitalWrite( led->digitalOutput, led->state );
   return led->state;
}


bool_t ledRead( led_t * led ){
   return led->state;
}


bool_t ledWrite( led_t * led, bool_t value ){
   led->state = value;
   digitalWrite( led->digitalOutput, led->state );
   return led->state;
}

/*==================[end of file]============================================*/
