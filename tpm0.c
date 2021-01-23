#include "tpm0.h"

// File contains functions to handle HC-SR04

#define ECHO 6 // PTB6
#define TRIG 7 // PTB7


static uint16_t tpm0Diff = 0;
static uint16_t tpm0New = 0;
static uint16_t tpm0Old = 0; // Variables used to calculate duration of high pulse on ECHO pin


// Function initalizing TPM0 in the input capture mode
void TPM0_Init_InputCapture(void) {
		
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		// Enable TPM0 mask in SCGC6 register
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);		// Choose MCGFLLCLK clock source
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 	// Connect port B to clock
	PORTB->PCR[ECHO] = PORT_PCR_MUX(2);   // Set multiplexer to TPM0 for ECHO pin
	
	TPM0->SC |= TPM_SC_PS(7);  						// Set prescaler to 128
	TPM0->SC |= TPM_SC_CMOD(1);						// Select the internal input clock source for TPM0
	TPM0->MOD = 13108;   									// T = 40 ms
	
  //Connect channel 3 from TPM0 for "input capture" mode
	TPM0->SC &= ~TPM_SC_CPWMS_MASK; 		// up counting 
	//TPM0->CONTROLS[3].CnSC &= ~TPM_CnSC_MSB_MASK;
	//TPM0->CONTROLS[3].CnSC &= ~TPM_CnSC_MSA_MASK;
	TPM0->CONTROLS[3].CnSC |= (TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_CHIE_MASK); // Set input capture on both edges and enable interrupt on chanel 3
	
	NVIC_SetPriority(TPM0_IRQn, 1);  // TPM0 interrupt priority level  
	NVIC_ClearPendingIRQ(TPM0_IRQn); 
	NVIC_EnableIRQ(TPM0_IRQn);			 // Enable Interrupts 

}


uint32_t TPM0_GetVal(void) {
	return tpm0Diff; // return duration of high pulse on ECHO pin
}

void TRIG_GPIO_Init(void){
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		// Enable clock for PORT B 
		PORTB->PCR[TRIG] = PORT_PCR_MUX(1);  	// Set Pin 5 of PORT B as GPIO 
		PTB->PDDR|=(1<<TRIG); 								// Set pin 5 of PORT B as output 
		PTB->PSOR |= (1<<TRIG); 							// Turn off 
}

void delay_us(uint8_t n) {
volatile uint8_t i;
volatile uint8_t j;
							for( i = 0 ; i < n; i++)
							for(j = 0; j < 4; j++) {}
								

}

void delay_ms( uint32_t n) {
volatile uint32_t i;
volatile uint32_t j;
							for( i = 0 ; i < n; i++)
							for(j = 0; j < 3500; j++) {}
}

void TRIG_inpulse(void){ 
			PTB->PTOR|=(1<<TRIG);     // enable HIGH on TRIG
			delay_us(10); 						// wait 10 us
			PTB->PTOR|=(1<<TRIG);			// disable HIGH on TRIG
			delay_us(10);
}

// function to measure HIGH level time on ECHO pin
void TPM0_IRQHandler(void) {
	tpm0Old = tpm0New;
	tpm0New = TPM0->CONTROLS[3].CnV & 0xFFFF;  		//Enable saving counter value
	tpm0Diff = tpm0New - tpm0Old;							 		//Calculate difference
	TPM0->CONTROLS[3].CnSC |= TPM_CnSC_CHF_MASK;	//Clear channel flag
}

