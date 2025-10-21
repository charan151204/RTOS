#include <LPC214X.H>

#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"


void task1(void* a);
void task2(void* b);

int main()
{
	uart_init();
	
	xTaskCreate(task1,"Task1",128,NULL,1,NULL);
	xTaskCreate(task2,"Task2",128,NULL,1,NULL);

	vTaskStartScheduler();

	
}



void task1(void* a)
{
	while(1)
	{
		uart_str((unsigned char *)"Task 1 Running");
		uart_str("\r\n");
		
		vTaskDelay(1);
	}
}

void task2(void* b)
{
	while(1)
	{
		uart_str("Task 2 Running");
		uart_str("\r\n");
		
		vTaskDelay(1);
	}
}