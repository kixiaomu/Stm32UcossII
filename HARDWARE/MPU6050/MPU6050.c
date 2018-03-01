#include "MPU6050.h"

//获取加速度计的值
short getAccX(void);
short getAccY(void);
short getAccZ(void);

//获取陀螺仪的值
short getGyroX(void);
short getGyroY(void);
short getGyroZ(void);

//获取温度
short getTemperature(void);

//求算角度数据
float ADX_GetAngle(short xValue, short yValue, short zValue, unsigned char dir);

void MPU6050_Inital(void)
{
	delay_ms( 100 );
	//解除休眠
	Single_Write_IIC( SLAVEADRESS , PWR_MGMT_1 , 0x00 );
	delay_ms( 50 );
	Single_Write_IIC( SLAVEADRESS , PWR_MGMT_1 , 0x00 );
	Single_Write_IIC( SLAVEADRESS , SMPLRT_DIV , 0x07 );
	Single_Write_IIC( SLAVEADRESS , CONFIG , 0x07 );
	Single_Write_IIC( SLAVEADRESS , GYRO_CONFIG , 0x18 );
	Single_Write_IIC( SLAVEADRESS , ACCEL_CONFIG , 0x01 );
	delay_ms( 100 );
}            

short getAccX(void)
{
	short AccX = 0;
	char AccXH = 0 , AccXL = 0;

	AccXH = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_H );
	AccXL = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_L );

	AccX = (AccXH<<8)|AccXL;

	return AccX;
}

short getAccY(void)
{
	short AccY = 0;
	char AccYH = 0 , AccYL = 0;

	AccYH = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_H );
	AccYL = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_L );

	AccY = (AccYH<<8)|AccYL;

	return AccY;
}

short getAccZ(void)
{
	short AccZ = 0;
	char AccZH = 0 , AccZL = 0;

	AccZH = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_H );
	AccZL = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_L );

	AccZ = (AccZH<<8)|AccZL;

	return AccZ;
}

short getGyroX(void)
{
	short GyroX = 0;
	char GyroXH = 0 , GyroXL = 0; 
	
	GyroXH = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_H );
	GyroXL = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_H );
	
	GyroX = (GyroXH<<8)|GyroXL;
	
	return GyroX;	
}

short getGyroY(void)
{
   	short GyroY = 0;
	char GyroYH = 0 , GyroYL = 0; 
	
	GyroYH = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_H );
	GyroYL = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_H );
	
	GyroY = (GyroYH<<8)|GyroYL;
	
	return GyroY;	
}

short getGyroZ(void)
{
   	short GyroZ = 0;
	char GyroZH = 0 , GyroZL = 0; 
	
	GyroZH = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_H );
	GyroZL = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_H );
	
	GyroZ = (GyroZH<<8)|GyroZL;
	
	return GyroZ;	
}

short getTemperature(void)
{
 	short temperature = 0;
	char temperatureH = 0 , temperatureL = 0;

	temperatureH = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_H );
	temperatureL = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_L );

	temperature = (temperatureH<<8)|temperatureL;

	return temperature;
}


float ADX_GetAngle(short xValue, short yValue, short zValue, unsigned char dir)
{
    double	temp;
 	float res = 0;
	
	switch(dir)
	{   
        /* 与自然Z轴的角度 */
		case 0:
 			temp = sqrt((xValue * xValue + yValue * yValue)) / zValue;
 		//printf("temp=%lf\r\n",temp);	
			
		res = atan(temp);
 			break;
        
        /* 与自然X轴的角度 */
		case 1:
 			temp = xValue / sqrt((yValue * yValue + zValue * zValue));
 			res = atan(temp);
 			break;

        /* 与自然Y轴的角度 */
 		case 2:
 			temp = yValue / sqrt((xValue * xValue + zValue * zValue));
 			res = atan(temp);
 			break;

        default:
            break;
 	}
	res = res * 180 / 3.14; 
	return res;
}
float rox=0;
float rox_temp=0;
//  chose_rol：选择角度  0->X角  1->Y角  2->Z角
void Get_rol_MPU6050(u8 id,u8 chose_rol)
{
	u8 i=0;
	
    u8 can_Txbuff[2]={0};  //{ID H+ L}
//	if(timer_flag_ms)
//	{
//		timer_flag_ms=0;
//		can_Txbuff[0]=id;
//		for(i=0;i<3;i++)
//		{
//			 rox=ADX_GetAngle(getAccX(),getAccY(),getAccZ(),chose_rol)+rox;
//		}	
//		can_Txbuff[1]=(u8)(rox/3);   		
//		delay_ms(1);                
//		
//		rox_temp=rox/3;
//		//rox=0;
//		printf("rox=%d\r\n",(u8)(rox/3));
	 	//CAN_Send(can_Txbuff);	
	//}
}

