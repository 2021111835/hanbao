#include <reg52.h>
#include <UART.h>
//#define PWM_DutyCycle 50

sbit PWM_OUT = P1^0;
unsigned char PWM_DutyCycle;

void delay(unsigned int t)
{
    unsigned int i, j;
    for (i = t; i > 0; i--)
        for (j = 20; j > 0; j--);
}

void main()
{
    PWM_OUT = 0;
		PWM_DutyCycle = 0;
		UART_Init();
    while (1)
    {
        PWM_OUT = 1;
        delay(PWM_DutyCycle);
        PWM_OUT = 0;
        delay(100 - PWM_DutyCycle);
    }
}

void UART_Routine() interrupt 4
{
		if(RI == 1)
		{
				PWM_DutyCycle = SBUF;		
				RI = 0;
				UART_send_byte(PWM_DutyCycle);
		}
}