#include "tpm1.h"
#define SERVO 12 //Servo controlled through pin 12 of PORT A

// Flag representing setting the PWM output
static uint8_t tpm1Enabled = 0;

// Function initializes TPM1 CH0 as the PWM output
void TPM1_Init(void) {
		
		
  SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;		// Enable TPM1 mask in SGC6 register
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    // Choose MCGFLLCLK clock source

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 	// Connect port A to clock
	PORTA->PCR[12] = PORT_PCR_MUX(2);			// PWM output -> PTA12, TPM1 channel 0
	
	TPM1->SC |= TPM_SC_PS(7);  					  // Set prescaler to 128
	TPM1->SC |= TPM_SC_CMOD(1);					  // Internal input clock source

	TPM1->MOD = 6554; 										// T = 20 ms																		
	
// "Edge-aligned PWM high true pulses" mode
	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 		
	TPM1->CONTROLS[0].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
	TPM1->CONTROLS[0].CnV = 500; // Set servo in neutral (0 degs) position

	tpm1Enabled = 1;  // Set  flag
}


// Function used to change the position of the servo
void TPM1_SetVal(uint32_t value) {
	 if (tpm1Enabled) TPM1->CONTROLS[0].CnV = value;
}



