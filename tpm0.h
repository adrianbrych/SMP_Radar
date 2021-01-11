#ifndef inputCapture
#define inputCapture
#include "frdm_bsp.h"

void TPM0_Init_InputCapture(void);
void TPM0_Init_OutputCompare(void);

void delay_ms( int n);

int TPM0_GetVal(void);

void TPM0_IRQHandler(void);
void TRIG_GPIO_Init(void);
void TRIG_inpulse(void);
void delay_us( int n);
#endif
