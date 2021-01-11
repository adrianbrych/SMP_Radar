/******************************************************************************
 * This file is a part of the SM2 Tutorial (C).                               *                                                 *
 ******************************************************************************/

/**
 * @file tpm.h
 * @author Koryciak
 * @date Nov 2020
 * @brief File containing enums, structures and declarations for TPM.
 * @ver 0.1
 */

#ifndef TPM_H
#define TPM_H

#include "frdm_bsp.h"

/**
**
 * @brief TPM0 initialization. PWM.
 */
void TPM1_Init(void);
/**
 * @brief Get value of counter from channel of TPM1.
 *
 * @return Value of counter.

 */
void TPM1_SetVal(uint32_t value);

#endif /* TPM_H */
