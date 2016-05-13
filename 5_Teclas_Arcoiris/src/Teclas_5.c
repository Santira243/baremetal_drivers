/* Copyright 2016, Teclas 1
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
#define TEC1               1

#define TECIZQ             2
#define TECDER             3
#define TIEMPO_T           1
#define TLEDS          250
#define TARC           30
#define MIN_COR        0
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
uint8_t estado;
uint8_t arciris;
uint8_t contador;

uint8_t cdor_cres;
uint8_t cdor_cores;
uint8_t color;
uint8_t auxiliar;
uint8_t RGB_L[3];


void Rutina(void)
{
    TitilarLeds();
    contador++;
    Chip_RIT_ClearInt(LPC_RITIMER);
    if (arciris)
    {
    	if (cdor_cres<TARC)
    		{
    			cdor_cres++;
    		}
    	    else
    		{
    	    	cdor_cres=MIN_COR;
    		}
    }

}

void RGB_c(uint8_t auxcol[3])
{
	Apagar('R');
	Apagar('G');
    Apagar('B');
	if(cdor_cres < floor((auxcol[0]*TARC)/254) )
		{
		   Prender('R');
		}
	if(cdor_cres < floor((auxcol[1]*TARC)/254) )
		{
			Prender('G');
		}
	if(cdor_cres < floor((auxcol[2]*TARC)/254) )
		{
			Prender('B');
		}
}

void TitilarLeds(){

	if (contador ==TLEDS)
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

		if (arciris)
		{
			Apagar('r');
			Apagar('g');
			Arcoiris();

		}

		contador = 0;

		if(color < 16)
		{
			color++;
		}
		else
		{
			color = 0;
		}


	}

}

void Arcoiris()
{

     Pintar(color);
}

void Pintar(uint8_t pint)
{
	switch (pint)
	{
	case 0:
	  {
		  RGB_L[0]=254;
		  RGB_L[1]=0;
		  RGB_L[2]=0;

		 break;
	  }
  case 1:
	 {
		  RGB_L[0]=100;
		  RGB_L[1]=100;
		  RGB_L[2]=0;
		 break;
     }
	case 2:
	{
		  RGB_L[0]=0;
		  RGB_L[1]=254;
		  RGB_L[2]=0;
		break;
	}
	case 3:
		{
			  RGB_L[0]=0;
			  RGB_L[1]=100;
			  RGB_L[2]=100;
			  break;
		}
	case 4:
	{
		  RGB_L[0]=0;
		  RGB_L[1]=0;
		  RGB_L[2]=254;
	   	  break;
	}
	case 5:
	{
		  RGB_L[0]=25;
		  RGB_L[1]=25;
		  RGB_L[2]=125;
	      break;
	}
	case 6:
		{
			  RGB_L[0]=255;
			  RGB_L[1]=55;
			  RGB_L[2]=11;
		     break;
		}
	case 7:
		{
			  RGB_L[0]=100;
			  RGB_L[1]=55;
			  RGB_L[2]=100;
		     break;
		}
	case 8:
		{
			  RGB_L[0]=180;
			  RGB_L[1]=0;
			  RGB_L[2]=25;
		     break;
		}
	case 9:
			{
				  RGB_L[0]=200;
				  RGB_L[1]=0;
				  RGB_L[2]=125;
			     break;
			}
	case 10:
			{
				  RGB_L[0]=200;
				  RGB_L[1]=25;
				  RGB_L[2]=14;
			     break;
			}
	case 11:
			{
				  RGB_L[0]=200;
				  RGB_L[1]=70;
				  RGB_L[2]=125;
			     break;
			}
	case 12:
			{
				  RGB_L[0]=200;
				  RGB_L[1]=160;
				  RGB_L[2]=125;
			     break;
			}
	case 13:
			{
				  RGB_L[0]=254;
				  RGB_L[1]=254;
				  RGB_L[2]=125;
			     break;
			}
	case 14:
			{
				  RGB_L[0]=254;
				  RGB_L[1]=10;
				  RGB_L[2]=125;
			     break;
			}
	case 15:
			{
				  RGB_L[0]=254;
				  RGB_L[1]=254;
				  RGB_L[2]=254;
			     break;
			}


	}

	RGB_c(RGB_L);
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
	 auxiliar =Chequea_T();
     switch(auxiliar)
			{
     case TEC1:
    	   arciris = 1;
    	   color=0;
    	   break;
     	 	}

    }

    return 1;
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

