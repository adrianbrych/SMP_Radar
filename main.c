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

void lcd_update(int a) {
		LCD1602_SetCursor(1, 0);
		LCD1602_PrintNum(a);
	}
	uint32_t i=0;
int main (void) { 
	UART0_Init();
	LCD1602_Init ();
	LCD1602_SetCursor(4, 1);
	LCD1602_Print("a");
	TPM0_Init_InputCapture();	    // TPM0 initialization						
	//TPM0_Init_OutputCompare();
	TPM1_Init();
	TRIG_GPIO_Init();
	
	LCD1602_SetCursor(0,0);
	char rx_buf[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};

  while(1) {
		TPM1_SetVal(250);
		for(int k =0; k<11; k++){
			TRIG_inpulse();
		}
		TPM1_SetVal(500);
		TPM1_SetVal(750);
		TPM1_SetVal(500);
		
		int x = TPM0_GetVal();
		lcd_update(x/19);
		sprintf(rx_buf,"%d%c",x/19,0xd);
			for(i=0;rx_buf[i]!=0;i++)
			{
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				UART0->D = rx_buf[i];
			}
			delay_ms(100);
		
		
		}
}									
								
