#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "semphr.h"


void task1(void *p);
void task2(void *p);
void task3(void *p);

xSemaphoreHandle countingsemaphore;

void rx1(void)__irq
{
  static portBASE_TYPE interrupttask;
  unsigned char r;
  
  if(U0IIR&0x04) {
    r=U0RBR;
    uart_str("Received Data = ");
    U0THR=r;
    while(!(U0LSR&0x20));
    uart_str("\r\nGoing to Give Semaphore From ISR\r\n");
    xSemaphoreGiveFromISR(countingsemaphore,&interrupttask );    
  }
  VICVectAddr = 0x00;
  
}
void uart_interrupt()
{
  
  U0TER=(1<<7);
  U0IER=0x01;  
  VICIntSelect=0x0000;     
  VICIntEnable|=0x0040;   
  VICVectAddr2=(unsigned long int)rx1;  
  VICVectCntl2=0x26;  
}

int main()
{
  uart_init();
	uart_interrupt();
	
  countingsemaphore=xSemaphoreCreateCounting(3,0);
  xTaskCreate(task1,"task1",128,NULL,1,NULL);
  xTaskCreate(task2,"task2",128,NULL,1,NULL);
	xTaskCreate(task3,"task3",128,NULL,1,NULL);
	
  vTaskStartScheduler();
	
  while(1);
  
}


void task1(void *p)
{
  while(1) 
		{
    if(countingsemaphore!=NULL) {      
      if(xSemaphoreTake(countingsemaphore,portMAX_DELAY)==pdTRUE) {
        uart_str("Task 1 Takes Semaphore\r\n");
      
      }
    }
  }
}
void task2(void *p)
{
  while(1) {
    if(countingsemaphore!=NULL) {      
      if(xSemaphoreTake(countingsemaphore,portMAX_DELAY )==pdTRUE) {
        uart_str("Task 2 Takes Semaphore");
       
      }
    }
  }
}
void task3(void *p)
{
  while(1) 
		{
    if(countingsemaphore!=NULL) {      
      if(xSemaphoreTake(countingsemaphore,portMAX_DELAY)==pdTRUE) {
        uart_str("Task 3 Takes Semaphore\r\n");
      
      }
    }
  }
}

