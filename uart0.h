/******************************************************************************
 * This file is a part of the SM2 Project				                              *
 ******************************************************************************/

/**
 * @file uart0.h
 * @author Banys & Brychner
 * @date Jan 2021
 * @brief File containing enums, structures and declarations for UART0.
 * @ver 1
 */
 
#ifndef TPM_H
#define TPM_H
 
#include "MKL05Z4.h"

#define CLK_DIS 					0x00
#define MCGFLLCLK 				0x01
#define OSCERCLK					0x02
#define MCGIRCLK					0x03

// Initialization of UART
void UART0_Init(void);

#endif
