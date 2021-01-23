/******************************************************************************
 * This file is a part of the SM2 Project				                              *
 ******************************************************************************/

/**
 * @file main.c
 * @author Banys & Brychner
 * @date Jan 2021
 * @brief File containing main function of the program.
 * @ver 1
 */



//Headers to include
#include "frdm_bsp.h" 
#include "tpm1.h"
#include "tpm0.h"
#include "uart0.h"
#include "lcd1602.h"
#include "MKL05Z4.h" /*Device header*/

//Variables used to send data via UART
uint32_t i=0;
uint32_t pomiar = 0;
char rx_buf[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};


//Send servo position and data from HC-SR04 via UART
void send(uint32_t val, char* poz)
	{
	TPM1_SetVal(val);														// Set servo in a specific position
	sprintf(rx_buf,"%s", poz);
	for(i=0;rx_buf[i]!=0;i++){
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));
		UART0->D = rx_buf[i];											// Send position of servo via UART
		}
	
	TRIG_inpulse();
	pomiar = TPM0_GetVal();											// Get data from HC-SR04
	sprintf(rx_buf,"%d%c",pomiar/19,0xd);
	for(i=0;rx_buf[i]!=0;i++){
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));
		UART0->D = rx_buf[i];											// Send data via UART
		}
	delay_ms(200);
	}
			


int main (void) { 
	UART0_Init();
	TPM0_Init_InputCapture();						
	TPM1_Init();
	TRIG_GPIO_Init();					// Initialize UART, TPMs, and GPIO
	
  while(1) {
		send(250, "a");
		delay_ms(250);
		send(330, "b");
		delay_ms(250);
		send(410, "c");
		delay_ms(250);
		send(490, "d");
		delay_ms(250);
		send(570, "e");
		delay_ms(250);
		send(650, "f");
		delay_ms(250);
		send(730, "g");
		delay_ms(250);
		send(650, "f");
		delay_ms(250);
		send(570, "e");
		delay_ms(250);
		send(490, "d");
		delay_ms(250);
		send(410, "c");
		delay_ms(250);
		send(330, "b");
		delay_ms(250);				// Loop servo from -90 degs to 90 degs with 7 steps
	}	
}									
						
