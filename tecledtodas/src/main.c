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

/*P2_10 gpio0_14  */
#define LED1_SCU_PORT  2
#define LED1_SCU_PIN   10
#define LED1_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED1_FUNC      FUNC0
#define LED1_GPIO_PORT 0
#define LED1_GPIO_PIN  14

/*P2_11 gpio1_11  */
#define LED2_SCU_PORT  2
#define LED2_SCU_PIN   11
#define LED2_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED2_FUNC      FUNC0
#define LED2_GPIO_PORT 1
#define LED2_GPIO_PIN  11

/*P2_12 gpio1_12  */
 #define LED3_SCU_PORT  2
#define LED3_SCU_PIN   12
#define LED3_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED3_FUNC      FUNC0
#define LED3_GPIO_PORT 1
#define LED3_GPIO_PIN  12

/*P2_0 gpio5_0 LED R */
 #define LED4_SCU_PORT  2
#define LED4_SCU_PIN   0
#define LED4_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED4_FUNC      FUNC4
#define LED4_GPIO_PORT 5
#define LED4_GPIO_PIN  0

/*P2_1 gpio5_1 LED G */
 #define LED5_SCU_PORT  2
#define LED5_SCU_PIN   1
#define LED5_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED5_FUNC      FUNC4
#define LED5_GPIO_PORT 5
#define LED5_GPIO_PIN  1

 /*P2_2 gpio5_2 LED B */
 #define LED6_SCU_PORT  2
#define LED6_SCU_PIN   2
#define LED6_MODE      (SCU_MODE_INACT | SCU_MODE_ZIF_DIS)
#define LED6_FUNC      FUNC4
#define LED6_GPIO_PORT 5
#define LED6_GPIO_PIN  2

/*P1_6 gpio1_9 tecla 4*/
#define TEC4_SCU_PORT  1
#define TEC4_SCU_PIN   6
#define TEC4_MODE      (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define TEC4_FUNC      FUNC0
#define TEC4_GPIO_PORT 1
#define TEC4_GPIO_PIN  9

/*P1_2 gpio0_9 tecla 3 */
#define TEC3_SCU_PORT  1
#define TEC3_SCU_PIN   2
#define TEC3_MODE      (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define TEC3_FUNC      FUNC0
#define TEC3_GPIO_PORT 0
#define TEC3_GPIO_PIN  9

/*P1_1 gpio0_8 tecla 2 */
#define TEC2_SCU_PORT  1
#define TEC2_SCU_PIN   1
#define TEC2_MODE      (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define TEC2_FUNC      FUNC0
#define TEC2_GPIO_PORT 0
#define TEC2_GPIO_PIN  8

/*P1_0 gpio0_4 tecla 1*/
#define TEC1_SCU_PORT  1
#define TEC1_SCU_PIN   0
#define TEC1_MODE      (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define TEC1_FUNC      FUNC0
#define TEC1_GPIO_PORT 0
#define TEC1_GPIO_PIN  4


#define INPUT  0
#define OUTPUT 1

#define OFF 0
#define ON  1

int main(void)
{
   /* perform the needed initialization here */
	uint8_t valor1 = ON;
        uint8_t valor2 = ON;
        uint8_t valor3 = ON;
        uint8_t valor4 = ON;

	//Configuración de SCU para LED1
	Chip_SCU_PinMux( LED1_SCU_PORT,LED1_SCU_PIN,LED1_MODE ,LED1_FUNC);
    //Configuración de SCU para LED2
	Chip_SCU_PinMux( LED2_SCU_PORT,LED2_SCU_PIN,LED2_MODE ,LED2_FUNC);
    //Configuración de SCU para LED3
	Chip_SCU_PinMux( LED3_SCU_PORT,LED3_SCU_PIN,LED3_MODE ,LED3_FUNC);
    
     //RGB 456   
    //Configuración de SCU para LED4
	Chip_SCU_PinMux( LED4_SCU_PORT,LED4_SCU_PIN,LED4_MODE ,LED4_FUNC);
    //Configuración de SCU para LED5
	Chip_SCU_PinMux( LED5_SCU_PORT,LED5_SCU_PIN,LED5_MODE ,LED5_FUNC);
    //Configuración de SCU para LED6
	Chip_SCU_PinMux( LED6_SCU_PORT,LED6_SCU_PIN,LED6_MODE ,LED6_FUNC);
   

    //Configuración de SCU para TEC 1
	Chip_SCU_PinMux( TEC1_SCU_PORT,TEC1_SCU_PIN,TEC1_MODE ,TEC1_FUNC);
	//Configuración de SCU para TEC 2
	Chip_SCU_PinMux( TEC2_SCU_PORT,TEC2_SCU_PIN,TEC2_MODE ,TEC2_FUNC);
    //Configuración de SCU para TEC 3
	Chip_SCU_PinMux( TEC3_SCU_PORT,TEC3_SCU_PIN,TEC3_MODE ,TEC3_FUNC);
    //Configuración de SCU para TEC 4
	Chip_SCU_PinMux( TEC4_SCU_PORT,TEC4_SCU_PIN,TEC4_MODE ,TEC4_FUNC);

	//Configuración de GPIO para LED1
	Chip_GPIO_SetDir( LPC_GPIO_PORT,LED1_GPIO_PORT,(1 << LED1_GPIO_PIN),OUTPUT);
    //Configuración de GPIO para LED2
	Chip_GPIO_SetDir( LPC_GPIO_PORT,LED2_GPIO_PORT,(1 << LED2_GPIO_PIN),OUTPUT);
    //Configuración de GPIO para LED3
	Chip_GPIO_SetDir( LPC_GPIO_PORT,LED3_GPIO_PORT,(1 << LED3_GPIO_PIN),OUTPUT);
    //Configuración de GPIO para LED4
	Chip_GPIO_SetDir( LPC_GPIO_PORT,LED4_GPIO_PORT,(1 << LED4_GPIO_PIN),OUTPUT);
    //Configuración de GPIO para LED5
	Chip_GPIO_SetDir( LPC_GPIO_PORT,LED5_GPIO_PORT,(1 << LED5_GPIO_PIN),OUTPUT);
    //Configuración de GPIO para LED6
	Chip_GPIO_SetDir( LPC_GPIO_PORT,LED6_GPIO_PORT,(1 << LED6_GPIO_PIN),OUTPUT);

	//Configuración de GPIO para TEC 1
	Chip_GPIO_SetDir( LPC_GPIO_PORT,TEC1_GPIO_PORT,(1 << TEC1_GPIO_PIN),INPUT);
    //Configuración de GPIO para TEC 2
	Chip_GPIO_SetDir( LPC_GPIO_PORT,TEC2_GPIO_PORT,(1 << TEC2_GPIO_PIN),INPUT);
    //Configuración de GPIO para TEC 3
	Chip_GPIO_SetDir( LPC_GPIO_PORT,TEC3_GPIO_PORT,(1 << TEC3_GPIO_PIN),INPUT);
    //Configuración de GPIO para TEC 4
	Chip_GPIO_SetDir( LPC_GPIO_PORT,TEC4_GPIO_PORT,(1 << TEC4_GPIO_PIN),INPUT);


   while(1) {

	   /* add your code here */

	// Leer TEC1
	valor1 = Chip_GPIO_GetPinState( LPC_GPIO_PORT,TEC1_GPIO_PORT,TEC1_GPIO_PIN);
        // Escribir LED4
	Chip_GPIO_SetPinState( LPC_GPIO_PORT,LED4_GPIO_PORT,LED4_GPIO_PIN,!valor1);
        // Escribir LED5
	Chip_GPIO_SetPinState( LPC_GPIO_PORT,LED5_GPIO_PORT,LED5_GPIO_PIN,!valor1);
        // Escribir LED6
	Chip_GPIO_SetPinState( LPC_GPIO_PORT,LED6_GPIO_PORT,LED6_GPIO_PIN,!valor1);
        

        // Leer TEC2
	valor2 = Chip_GPIO_GetPinState( LPC_GPIO_PORT,TEC2_GPIO_PORT,TEC2_GPIO_PIN);
        // Escribir LED1
	Chip_GPIO_SetPinState( LPC_GPIO_PORT,LED1_GPIO_PORT,LED1_GPIO_PIN,!valor2);

        // Leer TEC3
	valor3 = Chip_GPIO_GetPinState( LPC_GPIO_PORT,TEC3_GPIO_PORT,TEC3_GPIO_PIN);
        // Escribir LED2
	Chip_GPIO_SetPinState( LPC_GPIO_PORT,LED2_GPIO_PORT,LED2_GPIO_PIN,!valor3);	

        // Leer TEC4
	valor4 = Chip_GPIO_GetPinState( LPC_GPIO_PORT,TEC4_GPIO_PORT,TEC4_GPIO_PIN);
        // Escribir LED3
	Chip_GPIO_SetPinState( LPC_GPIO_PORT,LED3_GPIO_PORT,LED3_GPIO_PIN,!valor4);

   
}
   return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

