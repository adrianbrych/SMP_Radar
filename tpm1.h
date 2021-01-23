/******************************************************************************
 * This file is a part of the SM2 Project				                              * 
 ******************************************************************************/

/**
 * @file tpm1.h
 * @author Banys & Brychner
 * @date Jan 2021
 * @brief File containing enums, structures and declarations for TPM1.
 * @ver 1
 */

#ifndef TPM_H
#define TPM_H

#include "frdm_bsp.h"

// TPM1 initialization. PWM.
void TPM1_Init(void);

// Setting value to move servo
void TPM1_SetVal(uint32_t value);

#endif 
