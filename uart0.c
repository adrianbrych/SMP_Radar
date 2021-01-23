#include "uart0.h"

void UART0_Init(void)
{
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;				// Connect UART0 to clock
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;				// Connect PORT B to clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);		        // Set MCGFLLCLK=41943040Hz (CLOCK_SETUP=0) as a clock source
	PORTB->PCR[1] = PORT_PCR_MUX(2);				// PTB1 = TX_D
	PORTB->PCR[2] = PORT_PCR_MUX(2);				// PTB2 = RX_D
	
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );		// Block transmitter and receiver
	UART0->BDH = 0;
	UART0->BDL =91;																					// For CLOCK_SETUP=0, BR=28800,	BDL=91
	UART0->C4 &= ~UART0_C4_OSR_MASK;
	UART0->C4 |= UART0_C4_OSR(15);					//For CLOCK_SETUP=0, BR=28800	OSR=15
	
	
	UART0->C5 |= UART0_C5_BOTHEDGE_MASK;				// Sampling on both edges
	UART0->C2 |= UART0_C2_TE_MASK;					// Transmitter on
}


