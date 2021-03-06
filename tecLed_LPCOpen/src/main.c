/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
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

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "main.h"       /* <= own header */

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */


#define LED1_SCU_PORT  2
#define LED1_SCU_PIN   10
#define LED1_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED1_FUNC      FUNC0
#define LED1_GPIO_PORT 0
#define LED1_GPIO_PIN  14

#define TEC2_SCU_PORT  1
#define TEC2_SCU_PIN   1
#define TEC2_MODE      (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define TEC2_FUNC      FUNC0
#define TEC2_GPIO_PORT 0
#define TEC2_GPIO_PIN  8

#define INPUT  0
#define OUTPUT 1

#define OFF 0
#define ON  1

int main(void)
{
   /* perform the needed initialization here */
	uint8_t valor = OFF;

	//Configuración de SCU para LED1
	Chip_SCU_PinMux( LED1_SCU_PORT,
		               LED1_SCU_PIN,
				           LED1_MODE ,
				            LED1_FUNC
						);

	//Configuración de SCU para TEC 2
	Chip_SCU_PinMux( TEC2_SCU_PORT,
		               TEC2_SCU_PIN,
				           TEC2_MODE ,
				            TEC2_FUNC
						);

	//Configuración de GPIO para LED1
	Chip_GPIO_SetDir( LPC_GPIO_PORT,
		              LED1_GPIO_PORT,
				  (1 << LED1_GPIO_PIN),
				               OUTPUT
						);

	//Configuración de GPIO para TEC 2
	Chip_GPIO_SetDir( LPC_GPIO_PORT,
		              TEC2_GPIO_PORT,
				  (1 << TEC2_GPIO_PIN),
				                INPUT
						);

   while(1) {

	   /* add your code here */

		// Leer TEC2
		valor = Chip_GPIO_GetPinState( LPC_GPIO_PORT,
                            			TEC2_GPIO_PORT,
                             			 TEC2_GPIO_PIN
                           		  );

		// Escribir LED1
		Chip_GPIO_SetPinState( LPC_GPIO_PORT,
                            LED1_GPIO_PORT,
                             LED1_GPIO_PIN,
									         !valor
                           );
   }
   return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
