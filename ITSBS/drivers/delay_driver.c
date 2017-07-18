

#include "board.h"


#define SYSTICK_COUNTFLAG   16


static uint8_t   fac_us = 0;
static uint16_t  fac_ms = 0;


void delayInit(void)
{        
	SysTick->CTRL &= 0xFFFFFFFB;	 //! bit2���,ѡ���ⲿʱ��  HCLK/8

	fac_us = (72000000/1000000)/8;	 //! 1us�������������,����(SystemFrequency/1000000)����1US���������,8����Ҫ8��Ƶ		 
	fac_ms = (uint16_t)fac_us*1000;  //! 1ms�������������
	
}



void delayMs(uint16_t nms)
{	 		  	  
	uint32_t temp;	
	SysTick->LOAD=(uint32_t)nms*fac_ms;
	SysTick->VAL  = 0x00;                  
	SysTick->CTRL = 0x01; 
	do
	{
		temp=SysTick->CTRL;
	}
	while ((temp&0x01)&&(!(temp&(1<<SYSTICK_COUNTFLAG))));  
	SysTick->CTRL = 0x00;    
	SysTick->VAL  = 0x01;                    
}   
	


void delayUs(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD = nus*fac_us; 	  		 
	SysTick->VAL  = 0x00;                   
	SysTick->CTRL = 0x01; 	
	do
	{
		temp = SysTick->CTRL;
	}
	while (temp & 0x01 &&!(temp&(1<<SYSTICK_COUNTFLAG)));

	SysTick->CTRL = 0x00;
	SysTick->VAL  = 0x00;                    
}















































