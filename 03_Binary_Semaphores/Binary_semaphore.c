#include <LPC214X.H>

#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

xSemaphoreHandle binarysem;

void task1(void* a);
void task2(void* a);

int main()
{
	uart_init();
	
  vSemaphoreCreateBinary(binarysem);
	
  xTaskCreate(task1,"task1",128,NULL,1,NULL);
  xTaskCreate(task2,"task2",128,NULL,1,NULL);
	
  vTaskStartScheduler();
	
  while(1);
}



void task1(void* a)
{

	while(1) 
	{  
    xSemaphoreTake(binarysem,portMAX_DELAY);
    uart_str("Task1 functioning");
    uart_str("\r\n");
    xSemaphoreGive(binarysem);
    vTaskDelay(50);
  }
}

void task2(void *a)
{
  while(1) {
    xSemaphoreTake(binarysem,portMAX_DELAY);
    uart_str("Task2 functioning");
    uart_str("\r\n");
    xSemaphoreGive(binarysem);
    vTaskDelay(50);
  }
}
