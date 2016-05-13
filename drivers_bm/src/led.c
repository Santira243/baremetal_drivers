/* Copyright 2016, XXXXXXXXX  
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
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


#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "led.h"

#define salida 1

void Init_Leds(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);
	Chip_SCU_PinMux(PinGroup,Red,MD_PUP,FUNC4);   // Remapea P2_0 en GPIO 5-0
	Chip_SCU_PinMux(PinGroup,Green,MD_PUP,FUNC4); // Remapea P2_1 en GPIO 5-1
    Chip_SCU_PinMux(PinGroup,Blue,MD_PUP,FUNC4);  // Remapea P2_2 en GPIO 5-2

	Chip_SCU_PinMux(PinGroup,10,MD_PUP,FUNC0);   // Remapea P2_10 en GPIO 0-10
	Chip_SCU_PinMux(PinGroup,11,MD_PUP,FUNC0); // Remapea P2_11 en GPIO 1-11
	Chip_SCU_PinMux(PinGroup,12,MD_PUP,FUNC0);  // Remapea P2_12 en GPIO 1-12


	Chip_GPIO_SetDir(LPC_GPIO_PORT,Puerto5,1<<Red|1<<Green|1<<Blue,salida); //setea RGB
	Chip_GPIO_SetDir(LPC_GPIO_PORT,Puerto0,1<<Pled_rojo,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,Puerto1,(1<<Pled_verde|1<<Pled_amarillo),salida);

	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto5,Red);
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto5,Green);
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto5,Blue);

	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto0,Pled_rojo);
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto1,Pled_verde);
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto1,Pled_amarillo);
}
void Prender(char a)
{
  switch (a)
  {
  case 'R':
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,Puerto5,Red);
	  break;

  case 'G':
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,Puerto5,Green);
	  break;

  case 'B':
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,Puerto5,Blue);
	  break;
  case 'r':
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,Puerto0,Pled_rojo);
	  break;

  case 'g':
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,Puerto1,Pled_verde);
	  break;

  case 'a':
	  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,Puerto1,Pled_amarillo);
	  break;
  }
}
void Apagar(char b)
{
	  switch (b)
	  {
	  case 'R':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto5,Red);
		  break;

	  case 'G':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto5,Green);
		  break;

	  case 'B':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto5,Blue);
		  break;
	  case 'r':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto0,Pled_rojo);
		  break;

	  case 'g':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto1,Pled_verde);
		  break;

	  case 'a':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,Puerto1,Pled_amarillo);
		  break;
	  }

}













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




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

