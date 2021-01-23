/******************************************************************************
 * This file is a part of the SM2 Project			                                *
 ******************************************************************************/

/**
 * @file tpm0.h
 * @author Banys & Brychner
 * @date Jan 2021
 * @brief File containing enums, structures and declarations for TPM0.
 * @ver 1
 */

#ifndef tpm0
#define tpm0
#include "frdm_bsp.h"

// Initialization of TPM0 CH3 as Input Capture
void TPM0_Init_InputCapture(void);

// Function used to provide a delay
void delay_ms( uint32_t n);

// Returns the duration of high pulse on ECHO pin
uint32_t TPM0_GetVal(void);

//Interrupt handler, which calculates the duration of the high pulse on ECHO pin
void TPM0_IRQHandler(void);
void TRIG_GPIO_Init(void);
void TRIG_inpulse(void);
void delay_us( uint8_t n);
#endif
