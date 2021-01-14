#include "frdm_bsp.h" 
#include "tpm1.h"
#include "tpm0.h"
#include "uart0.h"
#include "lcd1602.h"
#include "MKL05Z4.h" /*Device header*/

void delay_ms( int n) {
volatile int i;
volatile int j;
							for( i = 0 ; i < n; i++)
							for(j = 0; j < 3500; j++) {}
}

uint32_t i=0;

char rx_buf[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};

void send(uint32_t val, char* poz){
	TPM1_SetVal(val);	// 250, 500, 750
		sprintf(rx_buf,"%s", poz);
		for(i=0;rx_buf[i]!=0;i++)
		{
			while(!(UART0->S1 & UART0_S1_TDRE_MASK));
			UART0->D = rx_buf[i];
		}
			TRIG_inpulse();
			int x = TPM0_GetVal();
			sprintf(rx_buf,"%d%c",x/19,0xd);
			for(i=0;rx_buf[i]!=0;i++)
			{
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				UART0->D = rx_buf[i];
			}
	delay_ms(200);
	}
			
	



int main (void) { 
	UART0_Init();
	TPM0_Init_InputCapture();	    // TPM0 initialization						
	//TPM0_Init_OutputCompare();
	TPM1_Init();
	TRIG_GPIO_Init();
	

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
		delay_ms(250);
	}	
}									
							
