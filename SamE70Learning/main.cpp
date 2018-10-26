/*
 * SamE70Learning.cpp
 *
 * Created: 10/25/2018 7:54:32 PM
 * Author : Jordan
 */ 


#include "sam.h"
#define LEDPIN 8
#define CLOCK_PIN 25
int main(void)
{
	//Todo: PA25 to peripheral D
	//Todo: find out how to enable MCCLK output
	//
	//Stop watch dog
	WDT->WDT_MR |= WDT_MR_WDDIS_Msk;
    /* Initialize the SAM system */
    SystemInit();
	//Set CLOCK_PIN to output based on peripheral
	PIOA->PIO_PDR		= (1 << CLOCK_PIN);
	PIOA->PIO_ABCDSR[0]|= (1 << CLOCK_PIN);
	PIOA->PIO_ABCDSR[1]|= (1 << CLOCK_PIN);
	
	 
	//Setting 
	PIOC->PIO_PER = (1 << LEDPIN);
	PIOC->PIO_OER = (1 << LEDPIN);
	
    /* Replace with your application code */
    while (1) {
		PIOC->PIO_SODR = (1 << LEDPIN);
		for(unsigned int i = 0xFFFFF; i> 0; i--);
		PIOC->PIO_CODR =(1 << LEDPIN);
		for(unsigned int i = 0xFFFFF; i> 0; i--);
    }
}
