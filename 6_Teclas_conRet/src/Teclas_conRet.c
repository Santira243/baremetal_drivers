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
#include "teclas.h"
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
uint8_t etec1;
uint8_t etec1_count;
uint8_t etec2;
uint32_t etec2_count;
uint8_t estado;
uint32_t etec3_count;
uint32_t etec3_TU;
uint8_t etec3;

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





void TitilarLeds(){


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
       if (etec3_TU<22)
       {
    	   Prender('r');
    	   Prender('g');
    	   Prender('a');
    	   Prender('R');
    	   Prender('G');
    	   Prender('B');
       }
       else
       {
    	  Apagar('R');
    	  Apagar('G');
    	  Apagar('B');
    	  Apagar('a');
       }
	}

void Rutina(void)
{
   auxiliar =Chequea_T();

   switch(auxiliar)
			{
				case TEC1:
					if(!etec1)
					{
						etec1 = 1;
						etec1_count = 0;
					}
					else
					{
						etec1_count++;

					}
					break;
				case TEC2:
					if(!etec2)
						{
							etec2 = 1;
							etec2_count = 0;

						}
						else
						{
							etec2_count++;
						}
						break;
				case TEC3:
					if(!etec3)
						{
							etec3 = 1;
							etec3_count = 0;

						}
						else
						{
							etec3_count++;
						}
							break;
				   default:
					   etec3 = 0;
					   etec3_TU = TU;
               	   break;
			}

   if((etec1== 1) && (auxiliar ==0))
    {
    	/*
    	Se soltó la tecla 1
    	*/
    	TitilarLeds();
    	etec1 = 0;

    }

   if((etec2== 1) && (etec2_count>TU))
	{
	   TitilarLeds();
	   etec2_count =0;
	}

   if((etec3== 1) && (etec3_count>etec3_TU))
	{
	   TitilarLeds();
	   if(etec3_TU > 20)
		   {
		   etec3_TU=(etec3_TU*7)/8;
		   }
	   etec3_count =0;
	}


    Chip_RIT_ClearInt(LPC_RITIMER);

}


int main(void)
{
   /* perform the needed initialization here */
	Init_Leds();
    Init_Teclas();
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

