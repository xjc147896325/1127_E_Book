/**
  *********************************************************************
  * @file    main.c
  * @author  jOKERII
  * @version V1.0
  * @date    2021-11-27
  * @brief   
  *********************************************************************
  * @attention
  *
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Ӳ��bspͷ�ļ� */
#include "bsp_led.h"
#include "bsp_mp3.h"
#include "bsp_infrared.h"
#include "bsp_debug_usart.h"
#include "bsp_key.h"
#include "bsp_timer.h"

/* ��׼��ͷ�ļ� */
#include <string.h>
/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t LED_Task_Handle = NULL;/* LED������ */
static TaskHandle_t KEY_Task_Handle = NULL;/* KEY������ */
static TaskHandle_t Uart_Task_Handle = NULL;/* UART������ */
static TaskHandle_t Book_1_Task_Handle = NULL;/* Book_1������ */
static TaskHandle_t Book_2_Task_Handle = NULL;/* Book_2������ */
static TaskHandle_t Book_3_Task_Handle = NULL;/* Book_3������ */
static TaskHandle_t Book_4_Task_Handle = NULL;/* Book_4������ */

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */
SemaphoreHandle_t BinarySem_Handle =NULL;
SemaphoreHandle_t Book_1_BinarySem_Handle =NULL;
SemaphoreHandle_t Book_2_BinarySem_Handle =NULL;
SemaphoreHandle_t Book_3_BinarySem_Handle =NULL;
SemaphoreHandle_t Book_4_BinarySem_Handle =NULL;


/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
 
extern char Usart_Rx_Buf[USART_RBUFF_SIZE];

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void AppTaskCreate(void);/* ���ڴ������� */

static void LED_Task(void* pvParameters);/* Test_Task����ʵ�� */
static void KEY_Task(void* pvParameters);/* KEY_Task����ʵ�� */
static void Uart_Task(void* pvParameters);/* UART_Task����ʵ�� */
static void Book_1_Task(void* pvParameters);/* Book_1_Task����ʵ�� */
static void Book_2_Task(void* pvParameters);/* Book_2_Task����ʵ�� */
static void Book_3_Task(void* pvParameters);/* Book_3_Task����ʵ�� */
static void Book_4_Task(void* pvParameters);/* Book_4_Task����ʵ�� */

static void BSP_Init(void);/* ���ڳ�ʼ�����������Դ */

/*****************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����������Ӳ����ʼ�� 
            �ڶ���������APPӦ������
            ������������FreeRTOS����ʼ���������
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
  /* ������Ӳ����ʼ�� */
  BSP_Init();
  
  printf("RTOS_Init\n\n");
  
   /* ����AppTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* ������ں��� */
                        (const char*    )"AppTaskCreate",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */    
}


/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	taskENTER_CRITICAL();           //�����ٽ���
  
	  /* ���� BinarySem */
	BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != BinarySem_Handle)
	printf("BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");
  
	  /* ���� Book_2_BinarySem */
	Book_1_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_1_BinarySem_Handle)
	printf("Book_1_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");  
  
	  /* ���� Book_2_BinarySem */
	Book_2_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_2_BinarySem_Handle)
	printf("Book_2_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");  
	
	  /* ���� Book_3_BinarySem */
	Book_3_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_3_BinarySem_Handle)
	printf("Book_3_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");	
	
	  /* ���� Book_4_BinarySem */
	Book_4_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_4_BinarySem_Handle)
	printf("Book_4_BinarySem_Handle��ֵ�ź��������ɹ�!\r\n");
	
	//������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
	xSemaphoreGive(Book_1_BinarySem_Handle);	//�ͷŶ�ֵ�ź���

  /* ����led_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )LED_Task, /* ������ں��� */
						(const char*    )"LED_Task",/* �������� */
						(uint16_t       )512,   /* ����ջ��С */
						(void*          )NULL,	/* ������ں������� */
						(UBaseType_t    )2,	    /* ��������ȼ� */
						(TaskHandle_t*  )&LED_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
	printf("����Test_Task����ɹ�!\r\n");
	
	/* ����Uart_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Uart_Task,  /* ������ں��� */
						(const char*    )"Uart_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )3, /* ��������ȼ� */
						(TaskHandle_t*  )&Uart_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����Uart_Task����ɹ�!\r\n");
	
	/* ����KEY_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )KEY_Task,  /* ������ں��� */
						(const char*    )"KEY_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )4, /* ��������ȼ� */
						(TaskHandle_t*  )&KEY_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����KEY_Task����ɹ�!\r\n");
	
	/* ����Book_1_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Book_1_Task,  /* ������ں��� */
						(const char*    )"Book_1_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )5, /* ��������ȼ� */
						(TaskHandle_t*  )&Book_1_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����Book_1_Task����ɹ�!\r\n");
	
	/* ����Book_2_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Book_2_Task,  /* ������ں��� */
						(const char*    )"Book_2_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )6, /* ��������ȼ� */
						(TaskHandle_t*  )&Book_2_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����Book_2_Task����ɹ�!\r\n");
	
	/* ����Book_3_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Book_3_Task,  /* ������ں��� */
						(const char*    )"Book_3_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )7, /* ��������ȼ� */
						(TaskHandle_t*  )&Book_3_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����Book_3_Task����ɹ�!\r\n");
	
	/* ����Book_4_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Book_4_Task,  /* ������ں��� */
						(const char*    )"Book_4_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )8, /* ��������ȼ� */
						(TaskHandle_t*  )&Book_4_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����Book_4_Task����ɹ�!\r\n");
	

	vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����

	taskEXIT_CRITICAL();            //�˳��ٽ���
}



/**********************************************************************
  * @ ������  �� LED_Task
  * @ ����˵���� LED_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void LED_Task(void* parameter)
{	 
  while (1) {
    LED1_ON;
    //printf("Test_Task Running,LED1_ON\r\n");
    vTaskDelay(500);   /* ��ʱ500��tick */
    
    LED1_OFF;     
    //printf("Test_Task Running,LED1_OFF\r\n");
    vTaskDelay(500);   /* ��ʱ500��tick */
  }
}

/**********************************************************************
  * @ ������  �� Uart_Task
  * @ ����˵���� Uart_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Uart_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	while (1) {
	//��ȡ��ֵ�ź��� xSemaphore,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */
		if(pdPASS == xReturn) {
			LED2_TOGGLE;
			printf("�յ�����:%s\n",Usart_Rx_Buf);
			memset(Usart_Rx_Buf,0,USART_RBUFF_SIZE);/* ���� */
		}
	}
}

/**********************************************************************
  * @ ������  �� KEY_Task
  * @ ����˵���� Test_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void KEY_Task(void* parameter)
{	
	
	while (1) {
	//��ȡ��ֵ�ź��� xSemaphore,û��ȡ����һֱ�ȴ�
		vTaskDelay(100);
	}
}

/**********************************************************************
  * @ ������  �� Book_1_Task
  * @ ����˵���� Book_1_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Book_1_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	uint8_t flag = 1;

	while (1) {
		//��ȡ��ֵ�ź��� Book_4_BinarySem_Handle,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(Book_1_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */
		
		Light_OFF;


		if(pdPASS == xReturn) {
			Light0(0); //red

			while(flag) {
				if(!Infrared_Scan(INFRARED0_GPIO_PORT,INFRARED0_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED0_GPIO_PORT,INFRARED0_PIN)) {
						flag = 0;
					}
				}
				else {
					if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
						vTaskDelay(10);
						if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
						MP3_Control(1);
						vTaskDelay(2000);
						MP3_Control(0);
						}
					}
				}
			}
			flag = 1;
			//do something
			Light0(1);
			Light2(0); // green
			MP3_Control(2);
			vTaskDelay(4500);
			MP3_Control(0);
			
			while(flag) {
				if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do other thing
			MP3_Control(5);
			Set_Pwm1(TIM14, 50);
			vTaskDelay(900);
			Set_Pwm1(TIM14, 0);
			vTaskDelay(2600);
			MP3_Control(0);
			
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_2_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_1_BinarySem_Handle);	//�ͷŶ�ֵ�ź���

			vTaskDelay(100);
		}
	}
}

/**********************************************************************
  * @ ������  �� Book_2_Task
  * @ ����˵���� Book_2_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Book_2_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	uint8_t flag = 1;

	while (1) {
		//��ȡ��ֵ�ź��� Book_2_BinarySem_Handle,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(Book_2_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */

		xReturn &= xSemaphoreTake(Book_1_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */

		if(pdPASS == xReturn) {
			while(flag) {
				if(!Infrared_Scan(INFRARED2_GPIO_PORT,INFRARED2_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED2_GPIO_PORT,INFRARED2_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do something
			MP3_Control(3);
			vTaskDelay(3000);
			MP3_Control(0);
			Light1(0);//red
			
			while(flag) {
				if(!Infrared_Scan(INFRARED3_GPIO_PORT,INFRARED3_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED3_GPIO_PORT,INFRARED3_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			while(flag) {
				if(!Infrared_Scan(INFRARED4_GPIO_PORT,INFRARED4_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED4_GPIO_PORT,INFRARED4_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			while(flag) {
				if(!Infrared_Scan(INFRARED5_GPIO_PORT,INFRARED5_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED5_GPIO_PORT,INFRARED5_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do other thing
			Light1(1);
			Light3(0);//green
			MP3_Control(3);			
			Set_Pwm1(TIM4, 50);
			vTaskDelay(900);
			Set_Pwm1(TIM4, 0);

			vTaskDelay(2100);
			MP3_Control(0);
			
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_3_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_2_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_1_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
		
			vTaskDelay(100);

		}
	}
}

/**********************************************************************
  * @ ������  �� Book_3_Task
  * @ ����˵���� Book_3_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Book_3_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	uint8_t flag = 1;



	while (1) {
	//��ȡ��ֵ�ź��� Book_3_BinarySem_Handle,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(Book_3_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */
		xReturn &= xSemaphoreTake(Book_2_BinarySem_Handle,/* ��ֵ�ź������ */
								  portMAX_DELAY); /* �ȴ�ʱ�� */

		xReturn &= xSemaphoreTake(Book_1_BinarySem_Handle,/* ��ֵ�ź������ */
								  portMAX_DELAY); /* �ȴ�ʱ�� */
	
		if(pdPASS == xReturn) {
			while(flag) {
				if(!Infrared_Scan(INFRARED6_GPIO_PORT,INFRARED6_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED6_GPIO_PORT,INFRARED6_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do something
			MP3_Control(6);			
			Set_Pwm2(TIM4, 50);
			vTaskDelay(900);
			Set_Pwm2(TIM14, 0);

			vTaskDelay(5100);
			MP3_Control(0);
			
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_4_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_3_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_2_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_1_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			

			vTaskDelay(100);

		}
	}
}

/**********************************************************************
  * @ ������  �� Book_4_Task
  * @ ����˵���� Book_4_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Book_4_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	uint8_t flag = 1;
	while (1)
	{
		//��ȡ��ֵ�ź��� Book_4_BinarySem_Handle,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(Book_4_BinarySem_Handle,/* ��ֵ�ź������ */
								  portMAX_DELAY); /* �ȴ�ʱ�� */
		xReturn = xSemaphoreTake(Book_3_BinarySem_Handle,/* ��ֵ�ź������ */
								  portMAX_DELAY); /* �ȴ�ʱ�� */
		xReturn &= xSemaphoreTake(Book_2_BinarySem_Handle,/* ��ֵ�ź������ */
								  portMAX_DELAY); /* �ȴ�ʱ�� */
		xReturn &= xSemaphoreTake(Book_1_BinarySem_Handle,/* ��ֵ�ź������ */
								  portMAX_DELAY); /* �ȴ�ʱ�� */


		if(pdPASS == xReturn) {
			while(flag) {
				if(!Infrared_Scan(INFRARED7_GPIO_PORT,INFRARED7_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED7_GPIO_PORT,INFRARED7_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do something
			MP3_Control(4);
			vTaskDelay(6000);
			MP3_Control(0);
//			Light4(0);//red


			while(flag) {
				if(!Infrared_Scan(INFRARED8_GPIO_PORT,INFRARED8_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED8_GPIO_PORT,INFRARED8_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do other thing
			Light4(0);//green
			MP3_Control(3);
			Set_Pwm3(TIM4, 50);
			vTaskDelay(900);
			Set_Pwm3(TIM4, 0);
			vTaskDelay(2100);
			MP3_Control(0);

			while(flag) {
				if(!Infrared_Scan(INFRARED9_GPIO_PORT,INFRARED9_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED9_GPIO_PORT,INFRARED9_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;	
			Set_Pwm1(TIM14, 250);
			Set_Pwm1(TIM4, 250);
			Set_Pwm2(TIM4, 250);
			Set_Pwm3(TIM4, 250);
			vTaskDelay(900);
			Set_Pwm1(TIM14, 0);
			Set_Pwm1(TIM4, 0);
			Set_Pwm2(TIM4, 0);
			Set_Pwm3(TIM4, 0);
//			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
//			xSemaphoreGive(Book_4_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
//			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
//			xSemaphoreGive(Book_3_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
//			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
//			xSemaphoreGive(Book_2_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(Book_1_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
			

			vTaskDelay(100);

		}
	}
}

/***********************************************************************
  * @ ������  �� BSP_Init
  * @ ����˵���� �弶�����ʼ�������а����ϵĳ�ʼ�����ɷ��������������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  *********************************************************************/
static void BSP_Init(void)
{
	uint16_t i = 1000;
	/*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 * ���ȼ�����ֻ��Ҫ����һ�μ��ɣ��Ժ������������������Ҫ�õ��жϣ�
	 * ��ͳһ��������ȼ����飬ǧ��Ҫ�ٷ��飬�мɡ�
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	/* LED ��ʼ�� */
	LED_GPIO_Config();	
	
	/* LED ��ʼ�� */
	MP3_Usart_Init();
	while(i--);
	MP3_Control(0);
	
	/* DMA��ʼ��	*/
	USARTx_DMA_Config();
	/* ���ڳ�ʼ��	*/
	Debug_USART_Config();
  
	/* infrared��ʼ��	*/
	Infrared_GPIO_Config();
	
	TIM14_PWM_Init(1999, 839, GPIOA, GPIO_Pin_7); //tim14 ch1
	TIM4_PWM_Init(1999, 839, GPIOB, GPIO_Pin_7); //tim4 ch2
	TIM4_PWM_Init(1999, 839, GPIOB, GPIO_Pin_8); //tim4 ch3
	TIM4_PWM_Init(1999, 839, GPIOB, GPIO_Pin_9); //tim4 ch4

//	Set_Pwm1(TIM14, 250);
//	Set_Pwm2(TIM4, 250);
//	Set_Pwm3(TIM4, 250);
//	Set_Pwm4(TIM4, 250);
//	while(1);   /* ��������ִ�е����� */    

	Light0(0);
	Light1(0);
	Light2(0);
	Light3(0);
	Light4(0);
	
	printf("Init finish\r\n");
}

/********************************END OF FILE****************************/
