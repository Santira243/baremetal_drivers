/* Copyright 2016, Teclas 6
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

/** \brief Blinking Bare Metal example source file
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
#include "led.h"
#include "teclas_2.h"
#include "timers.h"
#include "stdint.h"
#include "chip.h"

/*==================[macros and definitions]=================================*/
#define DELAY 1000000
#define TEC1             1
#define TEC2             2
#define TEC3             3
#define TIEMPO_T           1
#define TU           700

/*==================[internal data declaration]==============================*/
uint8_t auxiliar;

uint8_t estado;
uint32_t teclas_count[4];

uint32_t etec3_TU;

tecla pulsador[4];


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

void TitilarLeds()
{
    	if (estado)
		{
			Apagar('r');
			Prender('g');
			estado=0;
		}
		else
	   	{
			Prender('r');
			Apagar('g');
        	estado=1;
	   	}
}


void Rutina()
{
	uint8_t i;
	for(i=0; i<4; i++)
	{
		if (Chequea_T(&pulsador[i]))
			{
			if(!pulsador[i].estado)
							{
								pulsador[i].estado = 1;
								teclas_count[i] = 0;
							}
							else
							{
								teclas_count[i]++;
							}
			}

	  if(( pulsador[i].estado== 1) && (!Chequea_T(&pulsador[i])))
		{
			/*
			Se solt� la tecla i
			*/
			TitilarLeds();
	     	 pulsador[i].estado = 0;
		}

   }
    Chip_RIT_ClearInt(LPC_RITIMER);

}


int main(void)
{
   /* perform the needed initialization here */
	Init_Leds();

	while (!Init_Teclas(&pulsador[0],0,4,1,0,0));
	/*
	    Ejemplo:
	    En EDU CIA el Pulsador 0, TEC 1 //
	    Se instanciar�a de la siguiente forma:
	    tecla puls0;
	    Init_Teclas(&pulsador[0],0,4,1,0,0)
	    donde:
	    *puerto = 0; // GPIO port 0 -4
	    *pin_loc = 4;
	    *pin_group = 1; // Grupo 1 de pines (P1_0)
	    *pin_num = 0; //Pin 0
	    *func = 0; //Func0
	*/

	while (!Init_Teclas(&pulsador[1],0,8,1,1,0));
	while (!Init_Teclas(&pulsador[2],0,9,1,2,0));
	while (!Init_Teclas(&pulsador[3],1,9,1,6,0));

    Init_Timers();
    Setear_Tiempo(TIEMPO_T);

   while(1)
   {
   }

    return 1;
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

