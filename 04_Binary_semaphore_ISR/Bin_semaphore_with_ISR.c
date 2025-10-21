
#include<stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"

void interrupt_config(void);
void recsemaphore(void *q);

xSemaphoreHandle binarysemaphore;

void uart_recieve(void)__irq
{
  unsigned char r;
  static portBASE_TYPE interrupttask;
  interrupttask=pdFALSE;
  
  if(U0IIR&0x04) 
	{
    r=U0RBR;
    uart_str("Received Data : ");
    U0THR=r;
    while(!(U0LSR&0x20));
    uart_str("\r\n");
    uart_str("Going to give semaphore\r\n");
    xSemaphoreGiveFromISR(binarysemaphore,&interrupttask);
    uart_str("Semaphore has given\r\n");
  }
  VICVectAddr = 0x00;
}

int main()
{
  vSemaphoreCreateBinary(binarysemaphore);
  uart_init();
	interrupt_config();
  xSemaphoreTake(binarysemaphore,portMAX_DELAY);
  xTaskCreate(recsemaphore,"intertask",128,NULL,1,NULL);
  vTaskStartScheduler();
  while(1);
}



void recsemaphore(void *q)
{
  while(1) 
	{
    if(xSemaphoreTake(binarysemaphore,portMAX_DELAY)==pdTRUE) {
      uart_str("Received Semaphore From ISR\r\n");
    }
  }
}

void interrupt_config()
{
  
  U0TER=(1<<7);
  U0IER=0x01;  
  VICIntSelect=0x0000;    
  VICIntEnable|=0x0040;   
  VICVectAddr2=(unsigned long int)uart_recieve;  
  VICVectCntl2=0x26; 
}