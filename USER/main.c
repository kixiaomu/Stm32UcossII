#include "sys.h" 	
#include "delay.h"	
#include "led.h"
#include "usart.h"
#include "includes.h"
#include "ucosii_task_define.h"


u16 timeCount=0;
u8 key1_count=0;
u8 key1_downstate=0;//按键1 是否抬起的标志
OS_EVENT *key_msg_event;
OS_EVENT *sem_event;
OS_EVENT *queue_msg;//消息队列
void * msg_array[256];//消息数组
OS_TMR   * tmr1;			//软件定时器1
OS_TMR   * tmr2;			//软件定时器2
void tmr1_callback(OS_TMR *ptmr,void *p_arg) 
{
	timeCount++;
	
}
 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	uart_init(115200);
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	  	 
}
	  
//开始任务
void start_task(void *pdata)
{
	u8 err;
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	
	key_msg_event=OSMboxCreate(NULL);
	sem_event=OSSemCreate(0);
	queue_msg=OSQCreate(&msg_array[0],256);//创建一个256大小的消息队列
	
	
	
	
  	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);	
 	OSTaskCreate(key_scan_task,NULL,(OS_STK*)&KEY_SCAN_TASK_STK[63],KEY_SCAN_TASK_PRIO);
	OSTaskCreate(key_handler_task,NULL,(OS_STK*)&KEY_HANDLER_TASK_STK[63],KEY_HANDLER_TASK_PRIO);//创建按钮事件处理函数
	OSTaskCreate(sem_handler_task1,NULL,(OS_STK*)&SEM_HANDLER_TASK1_STK[63],SEM_HANDLER_TASK1_PRIO);
//	OSTaskCreate(sem_handler_task2,NULL,(OS_STK*)&SEM_HANDLER_TASK2_STK[63],SEM_HANDLER_TASK2_PRIO);
//	OSTaskCreate(sem_handler_task3,NULL,(OS_STK*)&SEM_HANDLER_TASK3_STK[63],SEM_HANDLER_TASK3_PRIO);
	OSTaskCreate(queue_request_task,NULL,(OS_STK*)&QUEUE_REQUEST_TASK_STK[63],QUEUE_REQUEST_TASK_PRIO);
	OSTaskCreate(queue_post_task,NULL,(OS_STK*)&QUEUE_POST_TASK_STK[63],QUEUE_POST_TASK_PRIO);
	OSTaskCreate(key1_check_task,NULL,(OS_STK*)&KEY1_CHECK_TASK_STK[63],KEY1_CHECK_TASK_PRIO);//创建按钮1处理任务
	OSTaskSuspend(KEY1_CHECK_TASK_PRIO);//将按钮1处理任务挂起
	
	
	tmr1=OSTmrCreate(1,1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err);		//10ms执行一次
	
	OSTmrStart(tmr1,&err);
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//LED0任务
void led0_task(void *pdata)
{	 	
	while(1)
	{
		LED0=0;
		delay_ms(80);
		LED0=1;
		delay_ms(920);
	}
}

//LED1任务
void led1_task(void *pdata)
{	  
	while(1)
	{
		LED1=0;
		delay_ms(300);
		LED1=1;
		delay_ms(300);
	}
}
void key_scan_task(void *pdata)
{
	while(1)
	{
		if(!KEY1)
			OSMboxPost(key_msg_event,(void *)1);
		if(!KEY2)
			OSMboxPost(key_msg_event,(void *)2);
		delay_ms(30);
	}
}
void key_handler_task(void *pdata)
{
	u32 key;
	u8 err;
	while(1)
	{
		key=(u32)OSMboxPend(key_msg_event,100,&err);
		if(err==OS_ERR_NONE)
		{
			if(key==1)
			{
				key1_downstate=1;
				OSTaskResume(KEY1_CHECK_TASK_PRIO);
				OSSemPost(sem_event);
			}
			if(key ==2)
			{
				
			}
		}
	}
}
void sem_handler_task1(void* pdata)
{
	u8 err;
	
	while(1)
	{
		OSSemPend(sem_event,0,&err);
		key1_count++;
		
	}
}
void sem_handler_task2(void* pdata)
{
	u8 err;
	while(1)
	{
		OSSemPend(sem_event,0,&err);
		printf("task2,sem_event->OSEventCnt:%d\r\n",sem_event->OSEventCnt);
		
	}
}
void sem_handler_task3(void* pdata)
{
	u8 err;
	while(1)
	{
		OSSemPend(sem_event,0,&err);
		printf("task3,sem_event->OSEventCnt:%d\r\n",sem_event->OSEventCnt);
		
	}
}
void queue_request_task(void *pdata)
{
	u8 err;
	u8 *p;
	while(1)
	{
		p=OSQPend(queue_msg,0,&err);
		if(err!=OS_ERR_NONE)
			continue;
		printf("请求到队列消息：%s\r\n",p);
		
	}
}
void queue_post_task(void *pdata)
{
	
	while(1)
	{
		delay_ms(500);
	}
}
void key1_check_task(void *pdata)
{
	u8 i=0;
	u8 key_click_state;
	while(1)
	{
		printf("key1 is touch\r\n");
		while(KEY1==0)//直到key1弹起
		{
			delay_ms(20);
			if(key1_count>30)
				break;
		}
		key1_downstate=0;
		printf("key1弹起,经历:%dms\r\n",key1_count*(30+20));
		if(key1_count<=30)
		{
			printf("key1 短按\r\n");
			key_click_state=1;
			for(i=0;i<=20;i++)
			{
				delay_ms(15);
				if(key1_downstate)
				{
					printf("连续点击了\r\n");
					while(KEY1==0)//直到key1弹起
					{
						delay_ms(20);
					}
					key_click_state=2;
					break;
				}
			}
		}
		else
		{
			printf("key1 长按\r\n");
			key_click_state=3;
		}
		printf("key_click_state=%d\r\n",key_click_state);
		printf("\r\n**************************\r\n");
		while(KEY1==0)//直到key1弹起
		{
			delay_ms(20);
		}
		key1_count=0;
		OSTaskSuspend(KEY1_CHECK_TASK_PRIO);//将按钮1处理任务挂起
	}
}


