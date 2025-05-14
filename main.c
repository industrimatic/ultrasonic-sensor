#include "delay.h" 
#include "usart.h"
#include "csb.h"

uint32_t time = 0;
float distance = 0;
int main(void)
{
	
	delay_init(168);
	uart_init(115200);
	csb_Init();

	while(1)
	{	
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);
		delay_us(100);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);

		distance = time/2.0 * 34*0.001; //time :us---34:cm/ms
		printf("distance:%.3fcm\n",distance);

		delay_ms(1000);
	}
}

void EXTI1_IRQHandler(void) 
{ 
	if(EXTI_GetITStatus(EXTI_Line1) == SET) 
	{ 
		TIM_SetCounter(TIM2,0); 
		TIM_Cmd(TIM2,ENABLE);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1);
		time = TIM2 -> CNT;
		TIM_Cmd(TIM2,DISABLE);
		
	} 
	EXTI_ClearITPendingBit(EXTI_Line1);  
} 