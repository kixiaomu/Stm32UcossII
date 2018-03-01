#ifndef _I2C_h_
#define _I2C_h_

#include "includes.h"

/*********************************************************************************/
/*�޸�ģ��IIC�Ķ�ȡ�����Լ����ŵĶ˿ں�											 */
/*��Щ�궨�嶨������Ժ����ų�ʼ�����������г�ʼ��ʱ��ʹ�ܵȱ�Ҫ�Ĳ���			 */
/*********************************************************************************/
#define IIC_GPIO (GPIOA)
#define IIC_GOIO_SDA (GPIOA)
#define IIC_GPIO_SCL (GPIOA)
#define IIC_SDA (GPIO_Pin_2)
#define IIC_SCL (GPIO_Pin_3)
/*********************************************************************************/


/************************************************************************************/
/*ʹ�ô˺��� ��ʼ�� ģ��IIC  ���в��� �����Ϻ궨���� �ж��� ʹ��ʱֻ��Ҫ�޸ĺ궨�弴�� */
/* �˺�������ʱ �븴�����´��� 
	IIC_GPIO_Configuration( IIC_GOIO_SDA , IIC_SDA , IIC_GPIO_SCL , IIC_SCL );  */
/************************************************************************************/
//IIC ��������
void IIC_GPIO_Configuration( GPIO_TypeDef * GPIOx_SDA , uint16_t SDA_Pin , GPIO_TypeDef * GPIOx_SCL , uint16_t SCL_Pin );


/*********************************************************************************/
/*ʹ�����´���ʱ�����޸�														 */
/*																				 */
/*********************************************************************************/
//ʹ�����ģ��I2C
#define SET_SDA		{ GPIO_SetBits  ( IIC_GPIO , IIC_SDA );  }
#define RESET_SDA	{ GPIO_ResetBits( IIC_GPIO , IIC_SDA );  }
#define SET_SCL		{ GPIO_SetBits  ( IIC_GPIO , IIC_SCL );  }
#define RESET_SCL 	{ GPIO_ResetBits( IIC_GPIO , IIC_SCL);   }
#define IIC_SDA_STATE (IIC_GPIO->IDR&IIC_SDA)
#define IIC_SCL_STATE (IIC_GPIO->IDR&IIC_SDA)


enum IIC_REPLAY_ENUM
{
	IIC_NACK = 0,
	IIC_ACK = 1
};

enum IIC_BUS_STATE_ENUM
{
	IIC_BUS_READY = 0,
	IIC_BUS_BUSY=1,
	IIC_BUS_ERROR=2
};

//IIC ��������
u8 IIC_Start(void);
//IIC ֹͣ����
void IIC_Stop(void);
//IIC ���Ͷ���
void IIC_SendACK(void);
//IIC ֹͣ����
void IIC_SendNACK(void);
//IIC ���͵��ֽ�
u8 IIC_SendByte(u8 Data);
//IIC ���յ��ֽ�
u8 IIC_RecvByte(void);
//IIC д�뵥�ֽ�
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
//IIC ��ȡ���ֽ�
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address);

#endif

