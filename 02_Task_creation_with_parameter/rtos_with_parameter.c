#include <LPC214X.H>

#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"


void task1(void* a);

int main()
{
	uart_init();
	
	xTaskCreate(task1,"Task1",128,"Task 1\n",1,NULL);
	xTaskCreate(task1,"Task2",128,"Task 2\n",1,NULL);

	vTaskStartScheduler();

	
}



void task1(void* a)
{
	unsigned char *str;
	
	while(1)
	{
		str = (unsigned char *)a;
		uart_str(str);
		uart_str("\r\n");
		
		vTaskDelay(5);
	}
}


