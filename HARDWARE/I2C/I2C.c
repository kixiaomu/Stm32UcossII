#include "I2C.h"

/************************************************************/
/*ģ��IIC���ų�ʼ������*/
/************************************************************/
void IIC_GPIO_Configuration( GPIO_TypeDef * GPIOx_SDA , uint16_t SDA_Pin , GPIO_TypeDef * GPIOx_SCL , uint16_t SCL_Pin )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint32_t RCC_GPIOx_SDA = 0;
	uint32_t RCC_GPIOx_SCL = 0;

	//�õ��˲�������Ŷ˿�
//	RCC_GPIOx_SDA = GPIO_Filter( GPIOx_SDA );
//	RCC_GPIOx_SCL = GPIO_Filter( GPIOx_SCL );
	
	//ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_GPIOx_SDA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_GPIOx_SCL,ENABLE);

	//��������
	GPIO_InitStructure.GPIO_Pin = SDA_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SCL_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOx_SCL, &GPIO_InitStructure);

	//��ʼ��IIC��ģʽ
	SET_SDA;
	SET_SCL;  
}

/*******************************************************************
TWI_START
������������
*******************************************************************/
u8 IIC_Start(void)
{
	SET_SDA;
	delay_us(5);

	SET_SCL;
	delay_us(5);

	if( IIC_SDA_STATE == RESET )
	{
		return IIC_BUS_BUSY;
	}

	RESET_SDA;
	delay_us(5);

	RESET_SCL;
	delay_us(5);

	if( IIC_SDA_STATE == SET )
	{
		return IIC_BUS_ERROR;
	}

	return IIC_BUS_READY;
}

/*******************************************************************
TWI_STOP
����ֹͣ����
*******************************************************************/
void IIC_Stop(void)
{
	RESET_SDA;
	delay_us(5);

	SET_SCL;
	delay_us(5);

	SET_SDA;
	delay_us(5);
}

/*******************************************************************************
* ��������:TWI_SendNACK                                                                     
* ��    ��:�յ�����,����NACK                                                                                                                                       
 *******************************************************************************/
void IIC_SendNACK(void)
{
	RESET_SDA;
	delay_us(5);
	SET_SCL;
	delay_us(5);
	RESET_SCL; 
	delay_us(5); 
}

/*******************************************************************************
* ��������:TWI_SendACK                                                                     
* ��    ��:�յ�����,����ACK                                                                                                                                        
*******************************************************************************/
void IIC_SendACK(void)
{
	SET_SDA;
	delay_us(5);
	SET_SCL;
	delay_us(5);
	RESET_SCL; 
	delay_us(5);
}

/*******************************************************************************
 * ��������:TWI_SendByte                                                                     
 * ��    ��:����һ���ֽ�                                                                                                                                      
 *******************************************************************************/
u8 IIC_SendByte(u8 Data)
{
	 u8 i;
	 RESET_SCL;
	 for(i=0;i<8;i++)
	 {  
		//---------���ݽ���----------
		if(Data&0x80)
		{
			SET_SDA;
		}
		else
		{
			RESET_SDA;
		} 
		Data<<=1;
		delay_us(10);
		//---���ݽ�������һ����ʱ----
		//----����һ��������[������] 
		SET_SCL;
		delay_us(10);
		RESET_SCL;
		delay_us(10);//��ʱ,��ֹSCL��û��ɵ�ʱ�ı�SDA,�Ӷ�����START/STOP�ź�
		//---------------------------   
	 }
	 //���մӻ���Ӧ�� 
	 SET_SDA; 
	 delay_us(10);
	 SET_SCL;
	 delay_us(10);   
	 if(IIC_SDA_STATE)
	 {
		RESET_SCL;
		return IIC_NACK;
	 }
	 else
	 {
		RESET_SCL;
		return IIC_ACK;  
	 }    
}

/*******************************************************************************
 * ��������:TWI_ReceiveByte                                                                     
 * ��    ��:����һ���ֽ�                                                                                                                                       
 *******************************************************************************/
u8 IIC_RecvByte(void)
{
	 u8 i,Dat = 0;
	 SET_SDA;
	 RESET_SCL; 
	 Dat=0;
	 for(i=0;i<8;i++)
	 {
		SET_SCL;//����ʱ��������[������],�ôӻ�׼�������� 
		delay_us(5); 
		Dat<<=1;
		if(IIC_SDA_STATE) //������״̬
		{
			Dat|=0x01; 
		}   
		RESET_SCL;//׼�����ٴν�������  
		delay_us(10);//�ȴ�����׼����         
	 }
	 return Dat;
}

/******���ֽ�д��*******************************************/
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    IIC_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ�� //��ο�����pdf22ҳ 
    IIC_SendByte(REG_data);       //�ڲ��Ĵ������ݣ� //��ο�����pdf22ҳ 
    IIC_Stop();                   //����ֹͣ�ź�
}

/********���ֽڶ�ȡ*****************************************/
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address)
{  
	u8 REG_data;
	
    IIC_Start();                          //��ʼ�ź�
    IIC_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    IIC_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ��//��0��ʼ	
    IIC_Start();                          //��ʼ�ź�
    IIC_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data = IIC_RecvByte();            //�����Ĵ�������
	IIC_SendACK();   
	IIC_Stop();                           //ֹͣ�ź�
    return REG_data; 
}


