
#ifndef LCD_H
#define	LCD_H

#include "basic.h"

extern void lcd_init(void);
extern void dis_init(void);
extern void lcd_write_reg(Uint8 data);
extern void lcd_write_ram(Uint8 data);
extern void lcd_dis_dot(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse);
extern void lcd_dis_smallchar(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse);
extern void lcd_dis_char(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse);
extern void lcd_dis_bigchar(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse);
extern void lcd_dis_clrall(void);
extern void lcd_dis_company(void);
extern void lcd_dis_softver(void);
#ifdef TEST
extern void lcd_test(void);
#endif
#endif	

