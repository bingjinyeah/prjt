
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
extern void lcd_dis_clr_all(void);
extern void lcd_dis_company(void);
extern void lcd_dis_softver(void);
extern void lcd_dis_saved00(void);
extern void lcd_dis_saved0(void);
extern void lcd_dis_saved1(void);
#ifndef LANGUAGE_EN
extern void lcd_dis_saved2(void);
extern void lcd_dis_saved3(void);
#endif
extern void lcd_dis_saved4(void);
#ifndef LANGUAGE_EN
extern void lcd_dis_saved5(void);
extern void lcd_dis_saved6(void);
extern void lcd_dis_saved7(void);
extern void lcd_dis_saved8(void);
extern void lcd_dis_saved9(void);
extern void lcd_dis_saved10(void);
extern void lcd_dis_saved11(void);
extern void lcd_dis_saved12(void);
#endif   
extern void lcd_dis_saved13(void);
#ifndef LANGUAGE_EN
extern void lcd_dis_saved14(void);
extern void lcd_dis_saved15(void);
extern void lcd_dis_saved16(void);
extern void lcd_dis_saved17(void);
#endif
extern void lcd_dis_saved18(void);

extern void lcd_dis_menu_0(void);
extern void lcd_dis_menu_1(void);
extern void lcd_dis_menu_2(void);
extern void lcd_dis_menu_3(void);
extern void lcd_dis_menu_4(void);
extern void lcd_dis_menu_5(void);
extern void lcd_dis_menu_300(void);
extern void lcd_dis_menu_300a(void);
extern void lcd_dis_menu_300b(void);
extern void lcd_dis_menu_310(void);
extern void lcd_dis_menu_311(void);
extern void lcd_dis_menu_312(void);
extern void lcd_dis_menu_profibus(void);
extern void lcd_dis_menu_modbus(void);
extern void lcd_dis_menu_posals(void);
extern void lcd_dis_menu_aux1(void);
extern void lcd_dis_menu_aux2(void);
extern void lcd_dis_menu_aux3(void);
extern void lcd_dis_menu_aux4(void);
extern void lcd_dis_menu_aux5(void);
extern void lcd_dis_menu_aux6(void);
extern void lcd_dis_menu_aux7(void);
extern void lcd_dis_menu_aux8(void);
extern void lcd_dis_menu_redudant(void);
extern void lcd_dis_menu_320(void);
extern void lcd_dis_menu_321(void);
extern void lcd_dis_menu_3210(void);
extern void lcd_dis_menu_322(void);
extern void lcd_dis_menu_3220(void);
extern void lcd_dis_menu_3221(void);
extern void lcd_dis_menu_323(void);
extern void lcd_dis_menu_3230(void);
extern void lcd_dis_menu_32301(void);
extern void lcd_dis_menu_32302(void);
extern void lcd_dis_menu_324(void);
extern void lcd_dis_menu_330(void);
extern void lcd_dis_menu_331(void);
extern void lcd_dis_menu_40(void);
extern void lcd_dis_menu_41(void);
extern void lcd_dis_menu_43(void);
extern void lcd_dis_menu_43_content();
extern void lcd_dis_menu_44(void);
extern void lcd_dis_menu_50(void);  


extern void lcd_dis_alarm_rmflick();
extern void lcd_dis_alarm_oplimitover();
extern void lcd_dis_alarm_cllimitover();
extern void lcd_dis_alarm_lengtherror();
extern void lcd_dis_alarm_cllock();
extern void lcd_dis_alarm_oplock();
extern void lcd_dis_alarm_esd();
extern void lcd_dis_alarm_opesd();
extern void lcd_dis_alarm_clesd();
extern void lcd_dis_alarm_noload();
extern void lcd_dis_alarm_jam();
extern void lcd_dis_alarm_powerdown();
extern void lcd_dis_alarm_vpstop();
extern void lcd_dis_alarm_direrror();
extern void lcd_dis_alarm_salos();
extern void lcd_dis_alarm_dpsalos();
extern void lcd_dis_alarm_opovertor();
extern void lcd_dis_alarm_clovertor();
extern void lcd_dis_alarm();

extern void lcd_dis_remote();
extern void lcd_dis_stop();
extern void lcd_dis_local();
extern void lcd_dis_ident();
extern void lcd_dis_flow();
extern void lcd_dis_vp();
extern void lcd_dis_clr_alarm();
#ifdef TEST
extern void lcd_test(void);
#endif
#endif	

