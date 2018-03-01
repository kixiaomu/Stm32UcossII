#ifndef _I2C_h_
#define _I2C_h_

#include "includes.h"

/*********************************************************************************/
/*修改模拟IIC的读取引脚以及引脚的端口号											 */
/*这些宏定义定义好了以后引脚初始化函数会自行初始化时钟使能等必要的参数			 */
/*********************************************************************************/
#define IIC_GPIO (GPIOA)
#define IIC_GOIO_SDA (GPIOA)
#define IIC_GPIO_SCL (GPIOA)
#define IIC_SDA (GPIO_Pin_2)
#define IIC_SCL (GPIO_Pin_3)
/*********************************************************************************/


/************************************************************************************/
/*使用此函数 初始化 模拟IIC  其中参数 在以上宏定义中 有定义 使用时只需要修改宏定义即可 */
/* 此函数调用时 请复制以下代码 
	IIC_GPIO_Configuration( IIC_GOIO_SDA , IIC_SDA , IIC_GPIO_SCL , IIC_SCL );  */
/************************************************************************************/
//IIC 引脚配置
void IIC_GPIO_Configuration( GPIO_TypeDef * GPIOx_SDA , uint16_t SDA_Pin , GPIO_TypeDef * GPIOx_SCL , uint16_t SCL_Pin );


/*********************************************************************************/
/*使用以下代码时请勿修改														 */
/*																				 */
/*********************************************************************************/
//使用软件模拟I2C
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

//IIC 启动函数
u8 IIC_Start(void);
//IIC 停止函数
void IIC_Stop(void);
//IIC 发送动作
void IIC_SendACK(void);
//IIC 停止动作
void IIC_SendNACK(void);
//IIC 发送单字节
u8 IIC_SendByte(u8 Data);
//IIC 接收单字节
u8 IIC_RecvByte(void);
//IIC 写入单字节
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
//IIC 读取单字节
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address);

#endif

