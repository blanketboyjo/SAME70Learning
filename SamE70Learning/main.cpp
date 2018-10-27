/*
 * SamE70Learning.cpp
 *
 * Created: 10/25/2018 7:54:32 PM
 * Author : Jordan
 */ 


#include "sam.h"
#define LEDPIN 8
#define CLOCK_PIN 13
#define NPCS1_PIN 25
//NPCS1 is PD25 peripheral B


void initSPI(void){
    //Configure PMC_PCR to enable clock?
    
    //Give SPI a clock
    PMC->PMC_PCER0  = (1<< ID_SPI0);
    //Start SPI
    SPI0->SPI_CR    = SPI_CR_SPIEN;
    //Setup to forced CS and Master mode
    SPI0->SPI_MR    = SPI_MR_PS_Msk|SPI_MR_MSTR_Msk;
    //Setup NPCS1 to peripheral control
    PIOD->PIO_ABCDSR[0] |=  (1<<NPCS1_PIN);
    PIOD->PIO_ABCDSR[0] &= ~(1<<NPCS1_PIN);
    PIOD->PIO_PDR        =  (1<<NPCS1_PIN);
    
    //Setup MOSI to peripheral control
    
    
    //Setup SCK to peripheral control
    
    //Setup Particular CSR
    SPI0->SPI_CSR[0]    =   SPI_CSR_BITS_8_BIT  |
                            SPI_CSR_SCBR(12)    |
                            SPI_CSR_CSNAAT_Msk  ;
    SPI0->SPI_CSR[1]    =   SPI0->SPI_CSR[0];
    SPI0->SPI_CSR[2]    =   SPI0->SPI_CSR[0];
    SPI0->SPI_CSR[3]    =   SPI0->SPI_CSR[0];
    
//  Send data to Chip Select 1
    SPI0->SPI_TDR       =   SPI_TDR_PCS(0x01)|
                            SPI_TDR_TD(0xAA);
}

int main(void)
{
	//Todo: PB13 to peripheral B
	//Todo: find out how to enable PCLK0 output
	//
	//Stop watch dog
	WDT->WDT_MR |= WDT_MR_WDDIS_Msk;
    /* Initialize the SAM system */
    SystemInit();
	//Set CLOCK_PIN to output based on peripheral
	
	PIOB->PIO_ABCDSR[0]|= (1 << CLOCK_PIN);
	PIOB->PIO_ABCDSR[1]&= ~(1 << CLOCK_PIN);
	PIOB->PIO_PDR		= (1 << CLOCK_PIN);
    //Set clock source to main
    PMC->PMC_PCK[0] = PMC_PCK_CSS_MCK;
    //Enable the clock
	PMC->PMC_SCER   = PMC_SCSR_PCK0;
	
    //Setting up LED pin
	PIOC->PIO_PER = (1 << LEDPIN);
	PIOC->PIO_OER = (1 << LEDPIN);
	
    
    //
    /* Replace with your application code */
    while (1) {
		PIOC->PIO_SODR = (1 << LEDPIN);
		for(unsigned int i = 0xFFFFF; i> 0; i--);
		PIOC->PIO_CODR =(1 << LEDPIN);
		for(unsigned int i = 0xFFFFF; i> 0; i--);
    }
}
