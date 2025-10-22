#include <lpc21xx.h>
#include "lcd_disp.h"

void lcd_init()
{
//    send_cmd(0x38);
//    send_cmd(0x0E);
//    send_cmd(0x01);
//    send_cmd(0x06);
//    send_cmd(0x0C);
//    send_cmd(0x80);
	
			send_cmd(0x30); // 8-bit mode
			lcd_delay();
			send_cmd(0x30);
			lcd_delay();
			send_cmd(0x30);
			lcd_delay();
			send_cmd(0x38); // Function set
			send_cmd(0x0C); // Display on, cursor off
			send_cmd(0x06); // Entry mode
			send_cmd(0x01); // Clear display

}

void send_cmd(unsigned char cmd)
{
	  IO1CLR=0xFF070000;   // 1111 1111 0000 0111 0000 0000 0000 0000   25->31 : DATA PINS DO-D7   16->18 : RS | RW | EN 
    IO1SET=(cmd<<24);    // cmd to 24 bits because data starts from 25-31
    IO1CLR=bit(16);      // RS = 0
    IO1CLR=bit(17);      // R/W = 0 write mode
    IO1SET=bit(18);      // EN = 1       
    lcd_delay();			   // Delay
    IO1CLR=bit(18);      // EN = 0         
}


void send_data(unsigned char data)
{
    IO1CLR=0xFF070000;          // 1111 1111 0000 0111 0000 0000 0000 0000   25->31 : DATA PINS DO-D7   16->18 : RS | RW | EN 
    IO1SET=(data<<24);          // cmd to 24 bits because data starts from 25-31
    IO1SET=bit(16);             // RS = 0
    IO1CLR=bit(17);             // R/W = 0 write mode
    IO1SET=bit(18);             // EN = 1
    lcd_delay();                // Delay
    IO1CLR=bit(18);             // EN = 0
}

void send_str(unsigned char *str)
{
    while(*str) {
        send_data(*str++);
    }
}

void lcd_delay()
{
    unsigned int i,j;
    for(i=0;i<=20000;i++)
		{
			for(j=0;j<50;j++);
		}
}


