void lcd_init(void);
void send_cmd(unsigned char cmd);
void send_data(unsigned char data);
void send_str(unsigned char *str);
void lcd_delay(void);

#define bit(x) (1<<x)
