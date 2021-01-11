#include "tpm1.h"
#define SERVO 0



static uint8_t tpm1Enabled = 0;


void TPM1_Init(void) {
		
		
  SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;		
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    // CLK ~ 41,9MHz (CLOCK_SETUP=0)

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 
	PORTA->PCR[12] = PORT_PCR_MUX(2);			// PCM output -> PTA12, TPM1 channel 0
	
	TPM1->SC |= TPM_SC_PS(7);  					  // 41,9MHz / 4 ~ 10,48MHz
	TPM1->SC |= TPM_SC_CMOD(1);					  // internal input clock source

	TPM1->MOD = 6554; 										  // 8bit PCM
																				// 10,48MHz / 256 ~ 40,96kHz
	
// "Edge-aligned PWM true pulses" mode -> PCM output
	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 		
	TPM1->CONTROLS[0].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); 
	TPM1->CONTROLS[0].CnV = 500; 

	tpm1Enabled = 1;  /* set local flag */
}


void TPM1_SetVal(uint32_t value) {
	 if (tpm1Enabled) TPM1->CONTROLS[0].CnV = value;    // ToDo 3.1.8: Choose correct channel for PWM update    // ToDo 3.1.8: Choose correct channel for PWM update.
}

