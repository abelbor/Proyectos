/* Copyright 2014, Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
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

/** \brief Blinking_echo example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Blinking Blinking_echo example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * PR           Pablo Ridolfi
 * JuCe         Juan Cecconi
 * GMuro        Gustavo Muro
 * ErPe         Eric Pernia
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150603 v0.0.3   ErPe change uint8 type by uint8_t
 *                        in line 172
 * 20141019 v0.0.2   JuCe add printf in each task,
 *                        remove trailing spaces
 * 20140731 v0.0.1   PR   first functional version
 */

/*==================[inclusions]=============================================*/
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */
#include "eventos2.h"         /* <= own header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
static int32_t fd_out;
static int32_t fd_in;

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
int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */

TASK(InitTask)
{
   /* init CIAA kernel and devices */
   ciaak_start();

   /* print message (only on x86) */
   ciaaPOSIX_printf("Init Task...\n");

   /* open CIAA digital outputs */
   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);
   fd_in = ciaaPOSIX_open("/dev/dio/in/0", ciaaPOSIX_O_RDONLY);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 250 ticks (250 ms)
    */

   SetRelAlarm(ActivatePeriodicTask, 250, 150);

   /* terminate task */
   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
*/ TASK(PeriodicTask)
{

	uint8_t inputs;
	uint8_t outputs;
	   /* write blinking message */
	ciaaPOSIX_printf("eventos2\n");
	                                                //Boton1..0x0e
	   /* Lee, compara y espera eventos */          //Boton2..0x0d
	ciaaPOSIX_read(fd_in, &inputs, 1);              //Boton3..0x0b
                                                    //Boton4..0x07
    if (inputs == 0x0E){              /* inputs= 1110  0x0e*/  /*inputs == 0x0E*/ /*(inputs&0x01) == 0x0E */
    	ActivateTask(Led1);
    	SetEvent(Led1, Boton1);

    }

	if (inputs == 0x0d){              /* inputs= 1101  0x0d*/   /*inputs == 0x0d*/ /* (inputs&0x02) == 0x0d */
		ActivateTask(Led2);
		SetEvent(Led2, Boton2);

	}
	if (inputs == 0x0b){              /* inputs= 1011  0x0b*/   /*inputs == 0x0d*/ /* (inputs&0x02) == 0x0d */
		ActivateTask(Led3);
		SetEvent(Led3, Boton3);

	}
	if (inputs == 0x07){              /* inputs= 0111  0x07*/   /*inputs == 0x0d*/ /* (inputs&0x02) == 0x0d */
		ActivateTask(Led4);
		SetEvent(Led4, Boton4);

	}

	/* terminate task */
	TerminateTask();

}

TASK(Led1)
{
   uint8_t outputs;

   /* write blinking message */
   ciaaPOSIX_printf("Led1 ON\n");

   /* blink output */
   EventMaskType Events;
   WaitEvent(Boton1);
   ClearEvent(Events);
  	   outputs = 0x08;
	   ciaaPOSIX_write(fd_out, &outputs, 1);

   /* terminate task */
   TerminateTask();
}

TASK(Led2)
{
   uint8_t outputs;

   /* write blinking message */
   ciaaPOSIX_printf("LED2 ON\n");

   /* blink output */

   EventMaskType Events;
      WaitEvent(Boton2);
      ClearEvent(Events);
  	   outputs = 0x10;
	   ciaaPOSIX_write(fd_out, &outputs, 1);
   /* terminate task */
   TerminateTask();
}

TASK(Led3)
{
   uint8_t outputs;

   /* write blinking message */
   ciaaPOSIX_printf("LED3 ON\n");

   /* blink output */

   EventMaskType Events;
      WaitEvent(Boton3);
      ClearEvent(Events);
   	   outputs = 0x20;
	   ciaaPOSIX_write(fd_out, &outputs, 1);

   /* terminate task */
   TerminateTask();
}

TASK(Led4)
{
   uint8_t outputs;
   uint8_t i;
   /* write blinking message */
   ciaaPOSIX_printf("LED4 ON\n");

   /* blink output */

   EventMaskType Events;
      WaitEvent(Boton4);
      ClearEvent(Events);
   if (i<3){     //se ejecuta cada vez que pulso tecla 4 hasta 3 veces-
	   //i++;
	   ciaaPOSIX_read(fd_out, &outputs, 1);
	   outputs ᶺ= 1<<i;
	   ciaaPOSIX_write(fd_out, &outputs, 1);
   }
   else {
	   i=0; //reseteo contador
      }
/* terminate task */
   TerminateTask();
}
/* RESOURCE = POSIXR;
      /*EVENT = POSIXE;*/


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

