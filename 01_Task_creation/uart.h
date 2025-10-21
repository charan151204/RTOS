// UART.c
#include <lpc21xx.h>

void uart_init()
{
    PINSEL0 &= ~0x0000000F;    // Clear P0.0, P0.1 bits
    PINSEL0 |=  0x00000005;    // Set P0.0 = TXD0, P0.1 = RXD0

    U0LCR = 0x83;              // Enable DLAB, 8-bit, 1 stop, no parity
    U0DLL = 97;                // For 9600 baud @ 15MHz
    U0DLM = 0;
    U0LCR = 0x03;              // Disable DLAB
}

void uart_tx(unsigned char ch)
{
    U0THR = ch;
    while ((U0LSR & (1<<5)) == 0);  // Wait for THR empty
}

unsigned char uart_rx()
{
    while ((U0LSR & 1) == 0);       // Wait until data received
    return U0RBR;
}

void uart_str(unsigned char* s)
{
    while (*s)
        uart_tx(*s++);
}

void uart_str_rec(unsigned char* s, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        s[i] = uart_rx();
        if (s[i] == '\r')
        {
            s[i] = '\0';
            break;
        }
    }
}



