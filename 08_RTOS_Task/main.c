#include<FreeRTOS.H>
#include<task.h>
#include "lcd_disp.h"

#define bit(x) (1<<x)

void lcd(void *);
void led(void *);

int main()
{
    IO0DIR=IO1DIR=0xffffffff;
    lcd_init();
	
    xTaskCreate(lcd,"lcd scroll",1024,0,1,0);
    xTaskCreate(led,"led blinking",1024,0,1,0);
	
    vTaskStartScheduler();
}

void lcd(void *str)
{
    send_cmd(0x80);
    send_str("RTOS Task");
    while(1) 
		{
        send_cmd(0x18);
        vTaskDelay(1);
    }
}

void led(void *str)
{
    while(1) 
			{
        IO0SET=0xff00;
        vTaskDelay(1);
        IO0CLR=0xff00;
        vTaskDelay(1);
    }
}

