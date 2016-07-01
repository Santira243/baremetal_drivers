/* Copyright 2016, FINAL
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

/** \brief Final
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Serial
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
#include "stdint.h"
#include "led.h"
#include "adconv.h"
#include "serial.h"
#include "teclas_2.h"
#include "timers.h"
#include "analogpin.h"
#include "chip.h"

/*==================[macros and definitions]=================================*/
#define DELAY 1000000
#define TEC1             0
#define TEC2             1
#define TEC3             2
#define TEC4             3
#define INICIO_FACTOR    127
#define TIEMPO_T           10
#define TU           700
#define U2           2
#define B_RATE          115200
#define DELTA        5


/*==================[internal data declaration]==============================*/
uint8_t auxiliar;
uint8_t estado;
uint32_t teclas_count[4];
uint32_t etec3_TU;
tecla pulsador[4];
uint8_t estado_led;
uint8_t factor;
uint8_t DAC_EST;
uint8_t SERIAL;
uint8_t  valor_dac;
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



void Cambiar_estado_led()
{
	if(estado_led==TRUE)
	{
		Prender('r');
	    estado_led= FALSE;
	}
	else
	{
		Apagar('r');
		estado_led= TRUE;
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
		  switch(i)
		  			{
		       case TEC1:
		    	   DAC_EST = 1;
		    	   factor += DELTA;
		    	   break;

		       case TEC2:
		    	   DAC_EST = 1;
		    	   factor -= DELTA;
		    	   break;

		       case TEC3:
		    	   DAC_EST = 0;
		    	   break;

		       case TEC4:

		    	   break;


		       	 	}

	     	 pulsador[i].estado = 0;
		}
	}

	uint8_t auxserie;
	uint16_t aux;
	uint32_t aux2;
	aux = RecibirADC();
	if(aux > 1)
		{
	     Cambiar_estado_led();
		}

	aux2 = (uint32_t) (aux*(10*factor/INICIO_FACTOR)/10);

	if(aux2>1023)
			{
				valor_dac = 1023;
			}
		else
			{
			valor_dac = (uint16_t) aux2;
			}

	while(!Enviar_DAC(valor_dac));

    auxserie = (uint8_t) aux;
	while(!Enviar_num( auxserie));
	Chip_RIT_ClearInt(LPC_RITIMER);

}

int main(void)
{
   /*
    * Inicializaciones
    *
    */
	Init_Leds();
	Init_Serial(U2,B_RATE);
	Init_AD(1,1);
	Init_DAC(0);
	Init_Timers();

	while (!Init_Teclas(&pulsador[0],0,4,1,0,0));
    while (!Init_Teclas(&pulsador[1],0,8,1,1,0));
	while (!Init_Teclas(&pulsador[2],0,9,1,2,0));
	while (!Init_Teclas(&pulsador[3],1,9,1,6,0));

	 /*
	  * SETEOS
	  *
	  */

    Setear_Tiempo(TIEMPO_T);
    factor = INICIO_FACTOR;

   while(1)
   {


   }

    return 1;
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

