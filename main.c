#include "frdm_bsp.h" 
#include "tpm1.h"
#include "tpm0.h"
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
	
int main (void) { 
	LCD1602_Init ();
	LCD1602_SetCursor(4, 1);
	LCD1602_Print("a");
	TPM0_Init_InputCapture();	    // TPM0 initialization						
	TPM0_Init_OutputCompare();
	TPM1_Init();
	TRIG_GPIO_Init();
	
	LCD1602_SetCursor(0,0);
	

  while(1) {
		TPM1_SetVal(250);
		TPM1_SetVal(500);
		TPM1_SetVal(750);
		TPM1_SetVal(500);
		TRIG_inpulse();
		delay_ms(50);
		int x = TPM0_GetVal();
		lcd_update(x);
		
		
		}
}									
