#include "lcd.h"

/*
PE1-> RST       GND->GND 
PD9 ->D14       PD10->D15 
PE15->D12       PD8->D13 
PE13->D10       PE14->D11 
PE11->D8        PE12->D9 
PE9->D6         PE10->D7 
PE7->D4         PE8->D5 
PD0->D2         PD1-> D3
PD14->D0        PD15-> D1
PD5->NWE        PD4-> NOE
PD7->CS         PD11->RS 
PB7->CS3        PA5->SCK 
PA6->MISO       PA7->MOSI 
PD13->PWM       PB6->INT 
5V ->           5V-> 
GND ->GND       3V3->3V3 


*/
void LCD_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);//FSMC时钟是挂载在AHB时钟线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);
	/*
		PE1-> RST
		PD13->PWM 背光
	初始化LCD复位跟背光
	*/
	GPIO_InitStructure.GPIO_Pin=1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=13;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	/*
	数据线	FSMC对应的引脚
	PD9 ->D14          PD10->D15  
	PE15->D12        PD8->D13
	PE13->D10       PE14->D11
	PE11->D8         PE12->D9
	PE9->D6          PE10->D7
	PE7->D4           PE8->D5
	PD0->D2          PD1-> D3
	PD14->D0        PD15-> D1
	
	PD0,PD1,PD8,PD9,PD10,PD14,PD15
	PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15
	*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
}
