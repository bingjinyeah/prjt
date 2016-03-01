#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "eedata.h"
#include "lcd.h"
#include "char.h"

extern Uint16 _EEDATA(2) _InverseDisEnable;
extern void delayus(Uint16 num);
extern void delayms(Uint16 num);
void lcd_init(){
	RESETB_Tris = 0;
	Nop();
	RESETB_Write = 1;
	delayus(500);
	RESETB_Write = 0;
	delayus(500);
	RESETB_Write = 1;
	dis_init();
    RESETB_Tris = 0;
	Nop();
	RESETB_Write = 1;
	delayus(500);
	RESETB_Write = 0;
	delayus(500);
	RESETB_Write = 1;
	dis_init();
	
}

void dis_init(){
	
	Uint16 inverse;
	
	eedata_read(_InverseDisEnable,inverse);
	
	ADPCFG = 0xffe3;
	RW_WRB_Tris = 0;
	RS_Tris = 0;
	DB0_Tris = 0;
	DB1_Tris = 0;
	DB2_Tris = 0;
	DB3_Tris = 0;
	DB4_Tris = 0;
	DB5_Tris = 0;
	DB6_Tris = 0;
	DB7_Tris = 0;
	lcd_write_reg(0xa2);
	lcd_write_reg(0x2f);
	if(inverse==0x69){
		lcd_write_reg(0xa1);
		lcd_write_reg(0xc0);
	}else{
		lcd_write_reg(0xa0);
		lcd_write_reg(0xc8);
	}
	lcd_write_reg(0x25);
	lcd_write_reg(0x81);
	lcd_write_reg(0x32);
	lcd_write_reg(0x40);
	lcd_write_reg(0xa6);
	lcd_write_reg(0xaf);
	
}

void lcd_write_reg(Uint8 data){
	
	RS_Tris = 0;
    Nop();
    RS_Write = 0;
    RW_WRB_Tris = 0;
	Nop();
	RW_WRB_Write = 0;
	Nop();
	DB0_Tris = 0;
	DB1_Tris = 0;
	DB2_Tris = 0;
	DB3_Tris = 0;
	DB4_Tris = 0;
	DB5_Tris = 0;
	DB6_Tris = 0;
	DB7_Tris = 0;
    Nop();
	DB0_Write = data;
	DB1_Write = data>>1;
	DB2_Write = data>>2;
	DB3_Write = data>>3;
	DB4_Write = data>>4;
	DB5_Write = data>>5;
	DB6_Write = data>>6;
	DB7_Write = data>>7;
	Nop();
	Nop();
	Nop();
	Nop();
    RW_WRB_Tris = 0;
	Nop();
	RW_WRB_Write = 1;
}

void lcd_write_ram(Uint8 data){
	
	RS_Tris = 0;
    Nop();
    RS_Write = 1;
    RW_WRB_Tris = 0;
	Nop();
	RW_WRB_Write = 0;
	Nop();
	DB0_Tris = 0;
	DB1_Tris = 0;
	DB2_Tris = 0;
	DB3_Tris = 0;
	DB4_Tris = 0;
	DB5_Tris = 0;
	DB6_Tris = 0;
	DB7_Tris = 0;
    Nop();
	DB0_Write = data;
	DB1_Write = data>>1;
	DB2_Write = data>>2;
	DB3_Write = data>>3;
	DB4_Write = data>>4;
	DB5_Write = data>>5;
	DB6_Write = data>>6;
	DB7_Write = data>>7;
	Nop();
	Nop();
	Nop();
	Nop();
    RW_WRB_Tris = 0;
	Nop();
	RW_WRB_Write = 1;
}

void lcd_set_row(Uint8 row){
	
	lcd_write_reg(row+0xb0);
}

void lcd_set_cloumn(Uint8 cloumn){
	
	Uint8 temp = cloumn;
	
	cloumn>>=4;
	cloumn+=16;
	lcd_write_reg(cloumn);
	temp &= 0x0f;
	lcd_write_reg(temp);
}

void lcd_dis_dot(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse){
	
	row<<=1;
	row++;
	cloumn<<=3;
	lcd_set_row(row);
	lcd_set_cloumn(cloumn);
	if(reverse!=0){
		lcd_write_ram(0x7f);
	}else{
		lcd_write_ram(0x80);
	}
	
}

void lcd_dis_smallchar(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse){
	
	Uint16 inverse;
	Uint8 rcount=2;
	Uint8 ccount=8;
	Uint8 code;
	
	row<<=1;
	cloumn<<=3;
	eedata_read(_InverseDisEnable,inverse);
    if(inverse==0x69){
		cloumn+=4;
	}
	while(rcount--){
		lcd_set_row(row);
		lcd_set_cloumn(cloumn);
		ccount=8;
		while(ccount--){
			code = *data++;
			if(reverse!=0){
				code = ~code;
			}
			lcd_write_ram(code);
		}
		row++;			
	}
}    

void lcd_dis_char(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse){
	
	Uint16 inverse;
	Uint8 rcount=2;
	Uint8 ccount=16;
	Uint8 code;
	
	row<<=1;
	cloumn<<=4;
	eedata_read(_InverseDisEnable,inverse);
    if(inverse==0x69){
		cloumn+=4;
	}
	while(rcount--){
		lcd_set_row(row);
		lcd_set_cloumn(cloumn);
		ccount=16;
		while(ccount--){
			code = *data++;
			if(reverse!=0){
				code = ~code;
			}
			lcd_write_ram(code);
		}
		row++;			
	}
}     

void lcd_dis_bigchar(Uint8 row, Uint8 cloumn, Uint8 *data, Uint8 reverse){
	
	Uint16 inverse;
	Uint8 rcount=4;
	Uint8 ccount=32;
	Uint8 code;
	
	row<<=1;
	cloumn<<=4;
	eedata_read(_InverseDisEnable,inverse);
    if(inverse==0x69){
		cloumn+=4;
	}
	while(rcount--){
		lcd_set_row(row);
		lcd_set_cloumn(cloumn);
		ccount=32;
		while(ccount--){
			code = *data++;
			if(reverse!=0){
				code = ~code;
			}
			lcd_write_ram(code);
		}
		row++;			
	}
}     
extern Uint8 _ucharTabClr[] _AUTO_PSV;
void lcd_dis_clrall(){
    Uint8 i,j;
    
    for(j=0;j<8;j++){
        
        for(i=0;i<4;i++){
            lcd_dis_char(i,j,_ucharTabClr,0);
        }
    }
}

void lcd_dis_string(Uint8 row, Uint8 cloumn, Uint8 *data[], Uint8 length,Uint8 reverse){
    if(length>16)
        return;
    while(length--){
        lcd_dis_smallchar(row,cloumn++,*data++,reverse);
    }
}

void lcd_dis_softver(){
    Uint16 ver;
    Uint8  res,rem;
    Uint8  row;
#ifdef LANGUAGE_EN
    Uint8 *data[] = {_ucharTabS,_ucharTabO,_ucharTabF,_ucharTabT,
                     _ucharTabW,_ucharTabA,_ucharTabR,_ucharTabE};
    Uint8 *data1[] = {_ucharTabV,_ucharTabE,_ucharTabR,_ucharTabS,
                      _ucharTabI,_ucharTabO,_ucharTabN}; 
    lcd_dis_clrall();
    lcd_dis_string(0,4,data,8,0);
    lcd_dis_string(1,4,data1,7,0); 
    row = 3;
#else
    lcd_dis_clrall();
    lcd_dis_char(0,1,_ucharTabRuan,0);
    lcd_dis_char(0,2,_ucharTabJian2,0);
    lcd_dis_char(0,3,_ucharTabBan,0);
    lcd_dis_char(0,4,_ucharTabBen,0);
    lcd_dis_char(0,5,_ucharTabHao,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    row = 2; 
#endif
    lcd_dis_smallchar(row,4,_ucharTabR,0);
    lcd_dis_smallchar(row,5,_ucharTabD,0);
    ver = _bcdSoftVer;
    res = ver/100;
    rem = ver%100; 
    if(res>9)
        res = 1;
    lcd_dis_smallchar(row,6,_ucharTabNum[res],0);
    lcd_dis_smallchar(row,7,_ucharTabXd,0);
    res = rem/10;
    rem = rem%10;
    lcd_dis_smallchar(row,8,_ucharTabNum[res],0);
    lcd_dis_smallchar(row,9,_ucharTabXd,0);
    lcd_dis_smallchar(row,10,_ucharTabNum[rem],0);
}

void lcd_dis_company(){

#ifdef LANGUAGE_EN
    Uint8 *data[] = {_ucharTabR,_ucharTabI,_ucharTabC,_ucharTabH};
    Uint8 *data1[] = {_ucharTabM,_ucharTabE,_ucharTabA,_ucharTabS,
                      _ucharTabU,_ucharTabR,_ucharTabE,_ucharTabAnd}; 
    Uint8 *data2[] = {_ucharTabE,_ucharTabQ,_ucharTabU,_ucharTabI,
                      _ucharTabP,_ucharTabM,_ucharTabE,_ucharTabN,_ucharTabT}; 
    Uint8 *data3[] = {_ucharTabC,_ucharTabO,_ucharTabXd,_ucharTabDouhao,
                      _ucharTabL,_ucharTabT,_ucharTabD,_ucharTabXd}; 
    lcd_dis_clrall();
    lcd_dis_string(0,5,data,4,0);
    lcd_dis_string(1,0,data1,8,0); 
    lcd_dis_control(1,8,0);
    lcd_dis_string(2,3,data2,9,0); 
    lcd_dis_string(3,3,data3,8,0); 
#else
    lcd_dis_clrall();
    lcd_dis_char(1,0,_ucharTabClr,0);
    lcd_dis_char(1,1,_ucharTabWen,0);
    lcd_dis_char(1,2,_ucharTabZhou,0);
    lcd_dis_char(1,3,_ucharTabRui,0);
    lcd_dis_char(1,4,_ucharTabJi4,0);
    lcd_dis_char(1,5,_ucharTabCe,0);
    lcd_dis_char(1,6,_ucharTabKong,0);
    lcd_dis_char(1,7,_ucharTabClr,0);
    
    lcd_dis_char(2,0,_ucharTabClr,0); 
    lcd_dis_char(2,1,_ucharTabShe,0);
    lcd_dis_char(2,2,_ucharTabBei3,0);
    lcd_dis_char(2,3,_ucharTabYou,0);
    lcd_dis_char(2,4,_ucharTabXian1,0);
    lcd_dis_char(2,5,_ucharTabGong,0);
    lcd_dis_char(2,6,_ucharTabSi3,0);
    lcd_dis_char(2,7,_ucharTabClr,0);
#endif
    
}

void lcd_dis_clralarm(){
    
}

void dis_open_lock(){
    
}

void dis_close_lock(){
    
}

void lcd_dis_alarmrmflick(){
    
}

void lcd_dis_stop(){
    
}

void lcd_dis_local(){
    
}

void lcd_dis_remote(){
    
}

void lcd_dis_ident(){
    
}

void lcd_dis_flow(){
    
}

void lcd_dis_dpsalos(){
    
}

#ifdef TEST
void lcd_test(){
    lcd_init();
    lcd_dis_clrall();
    lcd_dis_smallchar(1,6,_ucharTabH,0);
    lcd_dis_smallchar(1,7,_ucharTabE,0);
    lcd_dis_smallchar(1,8,_ucharTabL,0);
    lcd_dis_smallchar(1,9,_ucharTabL,0);
    lcd_dis_smallchar(1,10,_ucharTabO,0);
    delayms(1000);
    lcd_dis_softver();
    delayms(1000);
    lcd_dis_company();
}
#endif