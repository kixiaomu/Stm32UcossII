#ifndef __UCOSII_TASK_DEFINE_H_
#define __UCOSII_TASK_DEFINE_H_
#include "includes.h"
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	
 			   
//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);


//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED1_STK_SIZE  					64
//任务堆栈
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *pdata);

//KEY 扫描任务
#define KEY_SCAN_TASK_PRIO				8
OS_STK KEY_SCAN_TASK_STK[64];
void key_scan_task(void *pdata);

//KEY 处理任务
#define KEY_HANDLER_TASK_PRIO           9
OS_STK KEY_HANDLER_TASK_STK[64];
void key_handler_task(void *pdata);

//信号量处理任务1
#define SEM_HANDLER_TASK1_PRIO	        11
OS_STK SEM_HANDLER_TASK1_STK[64];
void sem_handler_task1(void *pdata);
//信号量处理任务2
#define SEM_HANDLER_TASK2_PRIO	        12
OS_STK SEM_HANDLER_TASK2_STK[64];
void sem_handler_task2(void *pdata);
//信号量处理任务3
#define SEM_HANDLER_TASK3_PRIO	        13
OS_STK SEM_HANDLER_TASK3_STK[64];
void sem_handler_task3(void *pdata);
//队列请求函数
#define QUEUE_REQUEST_TASK_PRIO			14
OS_STK QUEUE_REQUEST_TASK_STK[64];
void queue_request_task(void* pdata);
//队列发送函数
#define QUEUE_POST_TASK_PRIO			15
OS_STK QUEUE_POST_TASK_STK[64];
void queue_post_task(void *pdata);

#define KEY1_CHECK_TASK_PRIO			16
OS_STK KEY1_CHECK_TASK_STK[64];
void key1_check_task(void *pdata);
#endif
