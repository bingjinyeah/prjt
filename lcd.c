#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "eedata.h"
#include "lcd.h"
#include "char.h"
#include "para.h"
#include "flag.h"

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
//extern Uint8 _ucharTabClr[] _AUTO_PSV;
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

void lcd_dis_chinese_left(Uint8 row, Uint8 reverse){
    
    if(_DisWord0!=_ucharTabClr){
        lcd_dis_char(row,0,_DisWord0,reverse);
    }
    if(_DisWord1!=_ucharTabClr){
        lcd_dis_char(row,1,_DisWord1,reverse);
    }
    if(_DisWord2!=_ucharTabClr){
        lcd_dis_char(row,2,_DisWord2,reverse);
    }
    if(_DisWord3!=_ucharTabClr){
        lcd_dis_char(row,3,_DisWord3,reverse);
    }
}

void lcd_dis_chinese_right(Uint8 row, Uint8 reverse){
    
    if(_DisWord0!=_ucharTabClr){
        lcd_dis_char(row,4,_DisWord0,reverse);
    }
    if(_DisWord1!=_ucharTabClr){
        lcd_dis_char(row,5,_DisWord1,reverse);
    }
    if(_DisWord2!=_ucharTabClr){
        lcd_dis_char(row,6,_DisWord2,reverse);
    }
    if(_DisWord3!=_ucharTabClr){
        lcd_dis_char(row,7,_DisWord3,reverse);
    }
}

void lcd_dis_chinese(Uint8 row, Uint8 cloumn, Uint8 reverse){
    
    if(_DisWord0!=_ucharTabClr){
        lcd_dis_char(row,cloumn,_DisWord0,reverse);
    }
    cloumn++;
    if(_DisWord1!=_ucharTabClr){
        lcd_dis_char(row,cloumn,_DisWord1,reverse);
    }
    cloumn++;
    if(_DisWord2!=_ucharTabClr){
        lcd_dis_char(row,cloumn,_DisWord2,reverse);
    }
    cloumn++;
    if(_DisWord3!=_ucharTabClr){
        lcd_dis_char(row,cloumn,_DisWord3,reverse);
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

void lcd_dis_clr_4char(Uint8 row, Uint8 cloumn){
    Uint8 i;
    
    for(i=0;i<4;i++){
        lcd_dis_char(row,cloumn++,_ucharTabClr,0);
    }
}

void lcd_dis_clr_3char(Uint8 row, Uint8 cloumn){
    Uint8 i;
    
    for(i=0;i<3;i++){
        lcd_dis_char(row,cloumn++,_ucharTabClr,0);
    }
}

void lcd_dis_clr_l0(){
    lcd_dis_clr_4char(0,0);
}

void lcd_dis_clr_l1(){
    lcd_dis_clr_4char(1,0);
}

void lcd_dis_clr_l2(){
    lcd_dis_clr_4char(2,0);
}

void lcd_dis_clr_l3(){
    lcd_dis_clr_4char(3,0);
}

void lcd_dis_clr_l00(){
    lcd_dis_clr_4char(0,4);
}

void lcd_dis_clr_l10(){
    lcd_dis_clr_4char(1,4);
}

void lcd_dis_clr_l20(){
    lcd_dis_clr_4char(2,4);
}

void lcd_dis_clr_l30(){
    lcd_dis_clr_4char(3,4);
}

void lcd_dis_clr_alarm(){
#ifdef  LANGUAGE_EN
    lcd_dis_clr_4char(3,0);
#else
    lcd_dis_clr_l30();
#endif
}

void lcd_dis_num16(Uint8 row, Uint8 cloumn, Uint16 data, Uint8 reverse){
    Uint16 temp;
    Uint8  *pchar;
    Uint8  i;
    
    for(i=0;i<4;i++){
        temp = data>>(12-4*i);
        temp &= 0x0f;
        pchar = _ucharTabNum[temp];
        lcd_dis_smallchar(row,cloumn++,pchar,reverse);
    }
}

#ifndef LANGUAGE_EN
void lcd_dis_alarm_out(Uint8 *data[]){
    lcd_dis_char(3,4,data[0],0);
    lcd_dis_char(3,5,data[1],0);
    lcd_dis_char(3,6,data[2],0);
    lcd_dis_char(3,7,data[3],0);
}
#endif



void lcd_dis_alarm_powerdown(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabDian4, _ucharTabYuan1, _ucharTabDiao1, _ucharTabDian4};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_jam(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabDian4,_ucharTabJi1,_ucharTabDu,_ucharTabZhuan};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_noload(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabFa,_ucharTabWei,_ucharTabChu,_ucharTabCuo};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_clesd(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabES,_ucharTabD0,_ucharTabGuan,_ucharTabFa};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_opesd(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabES,_ucharTabD0,_ucharTabKai,_ucharTabFa};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_esd(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabES,_ucharTabD0,_ucharTabYou,_ucharTabXiao};
    lcd_dis_alarm_out(data);
#endif
}


void lcd_dis_alarm_oplock(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabDa,_ucharTabKai,_ucharTabLian,_ucharTabSuo};
    lcd_dis_alarm_out(data);
#endif     
}

void lcd_dis_alarm_cllock(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabGuan,_ucharTabBi,_ucharTabLian,_ucharTabSuo};
    lcd_dis_alarm_out(data);
#endif      
}

void lcd_dis_alarm_vpstop(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabFa,_ucharTabWei,_ucharTabBu,_ucharTabBian};
    lcd_dis_alarm_out(data);
#endif      
}

void lcd_dis_alarm_direrror(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabZhuan,_ucharTabXiang1,_ucharTabCuo,_ucharTabWu1};
    lcd_dis_alarm_out(data);
#endif      
}

void lcd_dis_alarm_rmflick(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabKai,_ucharTabGuan,_ucharTabTong1,_ucharTabZai};
    lcd_dis_alarm_out(data);
#endif  
}

void lcd_dis_alarm_salos(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabXin,_ucharTabHao,_ucharTabDiu,_ucharTabShi3};
    lcd_dis_alarm_out(data);
#endif  
}

void lcd_dis_alarm_dpsalos(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabZong,_ucharTabXian3,_ucharTabDiu,_ucharTabXin};
    lcd_dis_alarm_out(data);
#endif  
}

void lcd_dis_alarm_opovertor(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabDa,_ucharTabKai,_ucharTabGuo,_ucharTabJu};
    lcd_dis_alarm_out(data);
#endif  
}

void lcd_dis_alarm_clovertor(){
#ifdef LANGUAGE_EN
    
#else
    Uint8 *data[] = {_ucharTabGuan,_ucharTabBi,_ucharTabGuo,_ucharTabJu};
    lcd_dis_alarm_out(data);
#endif  
}

void lcd_dis_alarm_oplimitover(){
#ifdef LANGUAGE_EN
    lcd_dis_alarm_lengtherror();
#else
    Uint8 *data[] = {_ucharTabKai, _ucharTabXian1, _ucharTabChao, _ucharTabChu};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_cllimitover(){
    
#ifdef LANGUAGE_EN
    lcd_dis_alarm_lengtherror();
#else
    Uint8 *data[] = {_ucharTabGuan, _ucharTabXian1, _ucharTabChao, _ucharTabChu};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm_lengtherror(){
    
#ifdef LANGUAGE_EN
    lcd_dis_alarm_lengtherror();
#else
    Uint8 *data[] = {_ucharTabXing, _ucharTabCheng, _ucharTabChao, _ucharTabXian1};
    lcd_dis_alarm_out(data);
#endif
}

void lcd_dis_alarm(){
    Uint8 *data[4];
    
    _Rush_AlarmCount = 0;
    if(_strAlarmFlag & _PhaseLostedFlag){
        lcd_dis_clr_alarm();
#ifdef  LANGUAGE_EN
#ifdef  PHASE1
#else
#endif
#else
        data[0] = _ucharTabDian4;
        data[1] = _ucharTabYuan1;
#ifdef  PHASE1 
        data[2] = _ucharTabQian;
        data[3] = _ucharTabYa;
#else
        data[2] = _ucharTabQue1;
        data[3] = _ucharTabXiang3;
#endif
        lcd_dis_alarm_out(data);
#endif
        return;    
    }
    if(check_hot()){
        lcd_dis_clr_alarm();
#ifdef  LANGUAGE_EN

#else 
        data[0] = _ucharTabDian4;
        data[1] = _ucharTabJi1;
        data[2] = _ucharTabGuo;
        data[3] = _ucharTabRe;
        lcd_dis_alarm_out(data);
#endif
        return;    
    }
    if(_strAlarmFlag & _CTFlag){
        return;
    }
    if(_strAlarmFlag & _OTFlag){
        return;
    }
    if(_L_CodeVP<100){
        _strAlarmFlag |= _VPOver;
        _DP_DIAGR1 |= BIT6;
        lcd_dis_alarm_cllimitover();
        return;
    }
    if(_L_CodeVP>65435){
        _strAlarmFlag |= _VPOver;
        _DP_DIAGR1 |= BIT6;
        lcd_dis_alarm_oplimitover();
        return;
    }
    _strAlarmFlag &= ~_VPOver;
    _DP_DIAGR1 &= ~BIT6;
    lcd_dis_clr_alarm();
    if(_strAlarmFlag & _ESDFlag){
        lcd_dis_alarm_esd();
        return;
    }
}

void lcd_dis_status_out(Uint8 *data[]){
    lcd_dis_char(0,3,data[0],0);
    lcd_dis_char(0,4,data[0],0);
}

void lcd_dis_stop(){
    Uint8 *data[];
    lcd_dis_clr_position();
#ifdef LANGUAGE_EN
    
#else    
    data[0] = _S_ucharTabTing;
    data[1] = _S_ucharTabZhi;
    lcd_dis_status_out(data);
#endif    
}

void lcd_dis_local(){
    Uint8 *data[];
    lcd_dis_clr_position();
#ifdef LANGUAGE_EN
    
#else    
    data[0] = _S_ucharTabJiu;
    data[1] = _S_ucharTabDi;
    lcd_dis_status_out(data);
#endif
}

void lcd_dis_remote(){
    Uint8 *data[];
    lcd_dis_clr_position();
#ifdef LANGUAGE_EN
    
#else    
    data[0] = _S_ucharTabYuan;
    data[1] = _S_ucharTabCheng;
    lcd_dis_status_out(data);
#endif
}

void lcd_dis_ident(){
    Uint16 res;
    lcd_dis_clrall();
#ifdef LANGUAGE_EN
    
#else    
    lcd_dis_char(0,1,_ucharTabBen,0);
    lcd_dis_char(0,2,_ucharTabJi1,0);
    lcd_dis_char(0,3,_ucharTabXu1,0);
    lcd_dis_char(0,4,_ucharTabLie,0);
    lcd_dis_char(0,5,_ucharTabHao,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
#endif    
    eedata_read(_IdentNum1,res);
    lcd_dis_num16(2,4,res,0);
    eedata_read(_IdentNum2,res);
    lcd_dis_num16(2,8,res,0);
}

void lcd_dis_flow(){
    Uint16 res;
    lcd_dis_clrall();
#ifdef LANGUAGE_EN
    
#else    
    lcd_dis_char(0,1,_ucharTabBen,0);
    lcd_dis_char(0,2,_ucharTabJi1,0);
    lcd_dis_char(0,3,_ucharTabXu1,0);
    lcd_dis_char(0,4,_ucharTabLie,0);
    lcd_dis_char(0,5,_ucharTabHao,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
#endif    
    eedata_read(_FlowNum1,res);
    lcd_dis_num16(2,4,res,0);
    eedata_read(_FlowNum2,res);
    lcd_dis_num16(2,8,res,0);   
}

void lcd_dis_check_pass(){
#ifdef LANGUAGE_EN
    
#else    
    lcd_dis_char(2,3,_ucharTabZheng,0);
    lcd_dis_char(2,4,_ucharTabChang2,0);
    delayms(_DisCheckTime);
#endif
}

void lcd_dis_check_error(){
#ifdef LANGUAGE_EN
    
#else    
    lcd_dis_char(2,3,_ucharTabYou,0);
    lcd_dis_char(2,4,_ucharTabWu1,0);
#endif
}

void lcd_dis_vp(){
    lcd_dis_clr_l10();
    lcd_dis_clr_l20();
    lcd_dis_clr_l1();
    lcd_dis_clr_l2();
#ifndef LANGUAGE_EN
    lcd_dis_clr_l3();
#endif
    if(_strAlarmFlag & _CSFlag){
        _BCD_Shi = 12;
        _BCD_Ge = 13;
    }else if(_strAlarmFlag & _OSFlag){
        _BCD_Shi = 10;
        _BCD_Ge = 11;
    }else{
        lcd_dis_char(1,6,_ucharTabBigBfh,0);
        lcd_dis_char(2,6,_ucharTabBigBfh+32,0);
        if(_VPPercent>=100){
            
        }
    }
    
    
    
    
    

}







void lcd_dis_saved00(){
#ifdef  LANGUAGE_EN
    
#else
    lcd_dis_clr_l00();
    lcd_dis_clr_l10();
    lcd_dis_clr_l20();
    lcd_dis_clr_l30();
#endif
}

void lcd_dis_saved0(){
#ifdef  LANGUAGE_EN
    
#else
    lcd_dis_clr_l2();
    lcd_dis_clr_l3();
    lcd_dis_clr_l20();
    lcd_dis_clr_l30();
#endif
}


void lcd_dis_saved1(){
#ifdef  LANGUAGE_EN
    
#else
    lcd_dis_clr_l10();
    lcd_dis_clr_l20();
    lcd_dis_clr_l30();
#endif
}
#ifndef  LANGUAGE_EN
void lcd_dis_saved2(){
    lcd_dis_clr_l1();
}

void lcd_dis_saved3(){ 
    lcd_dis_clr_l2();
}
#endif

void lcd_dis_saved4(){
#ifdef  LANGUAGE_EN
    
#else
    lcd_dis_clr_l1();
    lcd_dis_clr_l10();
#endif
}

#ifndef LANGUAGE_EN
void lcd_dis_saved5(){
    lcd_dis_clr_l2();
    lcd_dis_clr_l20();
}

void lcd_dis_saved6(){
    lcd_dis_clr_l3();
    lcd_dis_clr_l30();
}

void lcd_dis_saved7(){
    lcd_dis_clr_l10();
    lcd_dis_clr_l20();
}

void lcd_dis_saved8(){
    
    lcd_dis_char(1,6,_ucharTabClr,0); 
    lcd_dis_char(1,7,_ucharTabClr,0); 
    lcd_dis_char(2,6,_ucharTabClr,0); 
    lcd_dis_char(2,7,_ucharTabClr,0); 
    lcd_dis_char(3,6,_ucharTabClr,0); 
    lcd_dis_char(3,7,_ucharTabClr,0); 
}

void lcd_dis_saved9(){  
    lcd_dis_char(2,6,_ucharTabClr,0); 
    lcd_dis_char(2,7,_ucharTabClr,0);  
}

void lcd_dis_saved10(){
    
    lcd_dis_clr_3char(0,5); 
    lcd_dis_clr_3char(1,5); 
    lcd_dis_clr_3char(2,5); 
    lcd_dis_clr_3char(3,5); 
}

void lcd_dis_saved11(){
    lcd_dis_clr_l1();
    lcd_dis_clr_l10();
    lcd_dis_clr_l3();
    lcd_dis_clr_l20();
}

void lcd_dis_saved12(){
    lcd_dis_clr_l00();
    lcd_dis_clr_l10();
}

void lcd_dis_saved14(){
    lcd_dis_clr_3char(1,5);
    lcd_dis_clr_4char(2,4);
    lcd_dis_clr_4char(3,4);
}

void lcd_dis_saved15(){
    lcd_dis_clr_l00();
    lcd_dis_clr_l10();
    //lcd_dis_clr_l20();
}

void lcd_dis_saved16(){
    lcd_dis_clr_l1();
    lcd_dis_clr_l10();
    lcd_dis_clr_l3();
    lcd_dis_clr_l30();
}

void lcd_dis_saved17(){
    lcd_dis_clr_l1();
    lcd_dis_clr_l10();
}
#endif

void lcd_dis_saved13(){
#ifdef  LANGUAGE_EN
    
#else
    lcd_dis_char(2,2,_ucharTabKou,0);
    lcd_dis_char(2,3,_ucharTabLing,0);
    lcd_dis_char(2,4,_ucharTabCuo,0);
    lcd_dis_char(2,5,_ucharTabWu1,0);
#endif
}

void lcd_dis_saved18(){
    lcd_dis_clr_l2();
    lcd_dis_clr_l20();
}

void lcd_dis_menu_0(){
    
    
}

void lcd_dis_menu_1(){
    
    
}

void lcd_dis_menu_2(){
    
    
}

void lcd_dis_menu_3(){
    
    
}

void lcd_dis_menu_300(){
    
    
}

void lcd_dis_menu_300a(){
    
    
}

//monitor relay option
void lcd_dis_menu_300b(){
    
    
}

void lcd_dis_menu_310(){
    
    
}


void lcd_dis_menu_311(){
    
    
}

void lcd_dis_menu_312(){
    
    
}
//menu 313
void lcd_dis_menu_profibus(){
    
    
}

void lcd_dis_menu_modbus(){
    
    
}

void lcd_dis_menu_posals(){
    
    
}

void lcd_dis_menu_aux1(){
    
    
}

void lcd_dis_menu_aux2(){
    
    
}

void lcd_dis_menu_aux3(){
    
    
}

void lcd_dis_menu_aux4(){
    
    
}

void lcd_dis_menu_aux5(){
    
    
}

void lcd_dis_menu_aux6(){
    
    
}

void lcd_dis_menu_aux7(){
    
    
}

void lcd_dis_menu_aux8(){
    
    
}

void lcd_dis_menu_redudant(){
    
    
}

//menu lock
void lcd_dis_menu_320(){
    
    
}

void lcd_dis_menu_321(){
    
    
}

void lcd_dis_menu_3210(){
    
    
}

void lcd_dis_menu_322(){
    
    
}

void lcd_dis_menu_3220(){
    
    
}

void lcd_dis_menu_3221(){
    
    
}

void lcd_dis_menu_323(){
    
    
}


void lcd_dis_menu_3230(){
    
    
}

void lcd_dis_menu_32301(){
    
    
}

void lcd_dis_menu_32302(){
    
    
}

void lcd_dis_menu_324(){
    
    
}

void lcd_dis_menu_330(){
    
    
}

void lcd_dis_menu_331(){
    
    
}

void lcd_dis_menu_4(){
    
    
}

void lcd_dis_menu_40(){
    
    
}

void lcd_dis_menu_41(){
    
    
}

void lcd_dis_menu_43(){
    
    
}

void lcd_dis_menu_44(){
    
    
}

void lcd_dis_menu_5(){
    
    
}

void lcd_dis_menu_50(){
    
    
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