/* Copyright 2016, TECLAS
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

/** \brief Blinking Bare Metal driver Teclas
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
 * 20160430 v0.0.1 initials initial version
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
#include "teclas.h"

void Init_Teclas(void){
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(PinGroup1,TEC_1,MD_PUP|MD_EZI|MD_ZI,FUNC0);   // Remapea P1_0 en GPIO 0-4
	Chip_SCU_PinMux(PinGroup1,TEC_2,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Remapea P1_1 en GPIO 0-8
	Chip_SCU_PinMux(PinGroup1,TEC_3,MD_PUP|MD_EZI|MD_ZI,FUNC0);  // Remapea P1_2 en GPIO 0-9
	Chip_SCU_PinMux(PinGroup1,TEC_4,MD_PUP|MD_EZI|MD_ZI,FUNC0);  // Remapea P1_6 en GPIO 1-9

	Chip_GPIO_SetDir(LPC_GPIO_PORT,Puerto0,1<<pTEC_1|1<<pTEC_2|1<<pTEC_3,entrada); //setea Puerto0
    Chip_GPIO_SetDir(LPC_GPIO_PORT,Puerto1,1<<pTEC_4,entrada);//setea Puerto1


}

uint8_t Chequea_T(){

	uint8_t aux = 0;


	if( !(Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,Puerto0,pTEC_1)) )
		{
		aux= 1;
		}
	if( !(Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,Puerto0,pTEC_2)) )
		{
		aux= 2;
		}
	if( !(Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,Puerto0,pTEC_3)) )
		{
		aux= 3;
		}
	if( !(Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,Puerto1,pTEC_4)) )
		{
		aux= 4;
		}

		return aux;

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

