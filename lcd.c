#include "includes.h"
#include "char.h"

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
void lcd_dis_clr_all(){
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
    lcd_dis_clr_all();
    lcd_dis_string(0,4,data,8,0);
    lcd_dis_string(1,4,data1,7,0); 
    row = 3;
#else
    lcd_dis_clr_all();
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
    lcd_dis_clr_all();
    lcd_dis_string(0,5,data,4,0);
    lcd_dis_string(1,0,data1,8,0); 
    lcd_dis_control(1,8,0);
    lcd_dis_string(2,3,data2,9,0); 
    lcd_dis_string(3,3,data3,8,0); 
#else
    lcd_dis_clr_all();
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

void lcd_dis_clr_position(){
    lcd_dis_clr_l00();
    lcd_dis_clr_l0();
}

void bin_to_bcd(Uint16 num){
    _BCD_Qian = 0;
    _BCD_Bai = 0;
    _BCD_Shi = 0;
    _BCD_Ge = 0;
    
    if(num>=1000){
        _BCD_Qian = num /1000;
        num -= _BCD_Qian*1000;
    }
    if(num>=100){
        _BCD_Bai = num /100;
        num -= _BCD_Bai*100;
    }
    if(num>=10){
        _BCD_Shi = num /10;
        num -= _BCD_Shi*10;
    }
    _BCD_Ge = num;    
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
    lcd_dis_char(0,4,data[1],0);
}

void lcd_dis_stop(){
    Uint8 *data[2];
    lcd_dis_clr_position();
#ifdef LANGUAGE_EN
    
#else    
    data[0] = _S_ucharTabTing;
    data[1] = _S_ucharTabZhi;
    lcd_dis_status_out(data);
#endif    
}

void lcd_dis_local(){
    Uint8 *data[2];
    lcd_dis_clr_position();
#ifdef LANGUAGE_EN
    
#else    
    data[0] = _S_ucharTabJiu;
    data[1] = _S_ucharTabDi;
    lcd_dis_status_out(data);
#endif
}

void lcd_dis_remote(){
    Uint8 *data[2];
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
    lcd_dis_clr_all();
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
    lcd_dis_clr_all();
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
            bin_to_bcd(99);
        }else if(_VPPercent==0){
            bin_to_bcd(1);
        }else{
            bin_to_bcd(_VPPercent);
        }
    }
    if(_BCD_Shi){
        lcd_dis_bigchar(1,2,_ucharTabBigNum[_BCD_Shi],0);
    }
    lcd_dis_bigchar(1,4,_ucharTabBigNum[_BCD_Ge],0);
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

void lcd_dis_num_qian(Uint8 row, Uint8 cloumn, Uint16 num, Uint8 reverse){
    Uint8 *pchar;
    
    bin_to_bcd(num);
    if((_BCD_Qian>9)||(_BCD_Qian==0)){
        pchar = _ucharTabClrx;
    }else{
        pchar = _ucharTabNum[_BCD_Qian];
    }
    lcd_dis_smallchar(row,cloumn,pchar,reverse);
}
void lcd_dis_num_bai(Uint8 row, Uint8 cloumn, Uint16 num, Uint8 reverse){
    Uint8 *pchar;
    
    bin_to_bcd(num);
    if(_BCD_Bai>9){
        pchar = _ucharTabClrx;
    }else if(_BCD_Bai==0){
        if(_BCD_Qian==0){
            pchar = _ucharTabClrx;
        }else{
            pchar = _ucharTab0;
        }
    }else{
        pchar = _ucharTabNum[_BCD_Bai];
    }
    lcd_dis_smallchar(row,cloumn,pchar,reverse);
}

void lcd_dis_num_shi(Uint8 row, Uint8 cloumn, Uint16 num, Uint8 reverse){
    Uint8 *pchar;
    
    bin_to_bcd(num);
    if(_BCD_Shi>9){
        pchar = _ucharTabClrx;
    }else if(_BCD_Shi==0){
        if((_BCD_Qian)||(_BCD_Bai)){
            pchar = _ucharTab0;
        }else{
            pchar = _ucharTabClrx;
        }
    }else{
        pchar = _ucharTabNum[_BCD_Shi];
    }
    lcd_dis_smallchar(row,cloumn,pchar,reverse);
}

void lcd_dis_num_shi0(Uint8 row, Uint8 cloumn, Uint16 num, Uint8 reverse){
    Uint8 *pchar;
    
    bin_to_bcd(num);
    if(_BCD_Shi>9){
        pchar = _ucharTabClrx;
    }else{
        pchar = _ucharTabNum[_BCD_Shi];
    }
    lcd_dis_smallchar(row,cloumn,pchar,reverse);
}

void lcd_dis_num_ge(Uint8 row, Uint8 cloumn, Uint16 num, Uint8 reverse){
    Uint8 *pchar;
    
    bin_to_bcd(num);
    if(_BCD_Ge>9){
        pchar = _ucharTabClrx;
    }else{
        pchar = _ucharTabNum[_BCD_Ge];
    }
    lcd_dis_smallchar(row,cloumn,pchar,reverse);
}
#ifndef LANGUAGE_EN
void lcd_dis_yunxu(Uint8 row, Uint8 cloumn, Uint8 reverse){
    lcd_dis_char(row,cloumn,_ucharTabYun1,reverse);
    lcd_dis_char(row,++cloumn,_ucharTabXu,reverse);
}
void lcd_dis_buyunxu(Uint8 row, Uint8 cloumn, Uint8 reverse){
    lcd_dis_char(row,cloumn,_ucharTabYun1,reverse);
    lcd_dis_char(row,++cloumn,_ucharTabYun1,reverse);
    lcd_dis_char(row,++cloumn,_ucharTabXu,reverse);
}
void lcd_dis_kaiyunxu(Uint8 reverse){
    lcd_dis_char(3,2,_ucharTabKai,reverse);
    lcd_dis_char(3,3,_ucharTabXiang1,reverse);
    lcd_dis_char(3,4,_ucharTabYun1,reverse);
    lcd_dis_char(3,5,_ucharTabXu,reverse);
}
void lcd_dis_guanyunxu(Uint8 reverse){
    lcd_dis_char(2,2,_ucharTabGuan,reverse);
    lcd_dis_char(2,3,_ucharTabXiang1,reverse);
    lcd_dis_char(2,4,_ucharTabYun1,reverse);
    lcd_dis_char(2,5,_ucharTabXu,reverse);
}
void lcd_dis_jinru(Uint8 row){
    lcd_dis_char(row,5,_ucharTabJin,0);
    lcd_dis_char(row,6,_ucharTabRu,0);
    lcd_dis_smallchar(row,14,_ucharTabWh,0);
}
#endif
void lcd_dis_menu_0(){
    
    _WriteEEPROMFlag = 0x55aa;
    _Menu = 1;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabQing;
    _DisWord2 = _ucharTabShu1;
    _DisWord3 = _ucharTabRu;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabKou;
    _DisWord1 = _ucharTabLing;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);      
#endif
    lcd_dis_num_bai(2,5,_Menu0Count0,0);
    //lcd_dis_smallchar(2,5,pchar,0);
    lcd_dis_num_shi(2,6,_Menu0Count0,0);
    //lcd_dis_smallchar(2,6,pchar,0);
    lcd_dis_num_ge(2,7,_Menu0Count0,0);
    //lcd_dis_smallchar(2,7,pchar,0);
    
}

void lcd_dis_menu_1(){
    
    _WriteEEPROMFlag = 0x55aa;
    _Menu = 2;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabYi;
    _DisWord1 = _ucharTabJi;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabDing;
    lcd_dis_chinese_left(0,0);
    
    _DisWord0 = _ucharTabEr;
    _DisWord1 = _ucharTabJi;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabDing;
    lcd_dis_chinese_left(1,0);
    
    _DisWord0 = _ucharTabXin;
    _DisWord1 = _ucharTabHao;
    _DisWord2 = _ucharTabCha;
    _DisWord3 = _ucharTabXun;
    lcd_dis_chinese_left(2,0);
    
    _DisWord0 = _ucharTabXi;
    _DisWord1 = _ucharTabTong;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(3,0);
    
    lcd_dis_jinru(_uintCur);
#endif    
}

#ifndef  LANGUAGE_EN
void lcd_dis_menu_2_0(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabBi;
    _DisWord2 = _ucharTabFang;
    _DisWord3 = _ucharTabXiang1;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_2_1(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabXing;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabJi5;
    _DisWord3 = _ucharTabXian1;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_2_2(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabGuo;
    _DisWord2 = _ucharTabJu;
    _DisWord3 = _ucharTabZhi3;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_2_3(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabWei;
    _DisWord2 = _ucharTabBao;
    _DisWord3 = _ucharTabHu;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_2_4(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabGuo;
    _DisWord2 = _ucharTabJu;
    _DisWord3 = _ucharTabZhi3;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_2_5(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabWei;
    _DisWord2 = _ucharTabBao;
    _DisWord3 = _ucharTabHu;
    lcd_dis_chinese_left(row,reverse);
}

void lcd_dis_menu_2_8(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabShun;
    _DisWord2 = _ucharTabShi;
    _DisWord3 = _ucharTabZhen;
    lcd_dis_chinese_right(0,0);
}

void lcd_dis_menu_2_9(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabNi;
    _DisWord2 = _ucharTabShi;
    _DisWord3 = _ucharTabZhen;
    lcd_dis_chinese_right(0,0);
}

void lcd_dis_menu_2_12(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabGuan;
    _DisWord2 = _ucharTabDao5;
    _DisWord3 = _ucharTabWei;
    lcd_dis_chinese_right(1,0);
}

void lcd_dis_menu_2_13(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabKai;
    _DisWord2 = _ucharTabDao5;
    _DisWord3 = _ucharTabWei;
    lcd_dis_chinese_right(1,0);
}

void lcd_dis_menu_2_30(){
    _RmRead = 0;
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabClr;
    _DisWord2 = _ucharTabXian1;
    _DisWord3 = _ucharTabWei;
    lcd_dis_chinese_right(3,0);
}

void lcd_dis_menu_2_31(){
    _RmRead = 1;
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabClr;
    _DisWord2 = _ucharTabLi5;
    _DisWord3 = _ucharTabJu;
    lcd_dis_chinese_right(3,0);
}

void lcd_dis_menu_2_shu(Uint8 row,Uint16 num){
    lcd_dis_num_bai(row,11,num,0);
    //lcd_dis_smallchar(row,11,pchar,0);
    lcd_dis_num_shi(row,12,num,0);
    //lcd_dis_smallchar(row,12,pchar,0);
    lcd_dis_num_ge(row,13,num,0);
    //lcd_dis_smallchar(row,13,pchar,0);
    lcd_dis_smallchar(row,14,_ucharTabBfhx,0);
}
#endif
void lcd_dis_menu_2(){
    Uint16 res;
    _Menu = 3;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>5){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_2_0(0,1);
            lcd_dis_menu_2_1(1,0);
            lcd_dis_menu_2_2(2,0);
            lcd_dis_menu_2_3(3,0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_CL_Dir,res);
                _RmRead = ((res==0x69) ? 1:0);
            }
            if(_RmRead){
                lcd_dis_menu_2_9();
            }else{
                lcd_dis_menu_2_8();
            }
            break;
        case 1:
            lcd_dis_menu_2_0(0,0);
            lcd_dis_menu_2_1(1,1);
            lcd_dis_menu_2_2(2,0);
            lcd_dis_menu_2_3(3,0);
            if((_Length_Check_Flag==0x69)&&(_Length_Error_Flag==0x69)){
                lcd_dis_alarm_lengtherror();
            }
            if(_EmRead==1){
                _EmRead = 0;
                _RmRead = 0;
            }
            if(_RmRead){
                lcd_dis_menu_2_13();
            }else{
                lcd_dis_menu_2_12();
            }
            break;
        case 2:
            lcd_dis_menu_2_0(0,0);
            lcd_dis_menu_2_1(1,0);
            lcd_dis_menu_2_2(2,1);
            lcd_dis_menu_2_3(3,0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_CL_TorProtect,res);
                _Menu2Count0 = res;
            }
            lcd_dis_menu_2_shu(2,_Menu2Count0);
            break;
        case 3:
            lcd_dis_menu_2_0(0,0);
            lcd_dis_menu_2_1(1,0);
            lcd_dis_menu_2_2(2,0);
            lcd_dis_menu_2_3(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_CLDir_Protect,res);
                _RmRead = ((res==0x69) ? 1:0);
            }
            if(_RmRead){
               lcd_dis_menu_2_31();
            }else{
                lcd_dis_menu_2_30();
            }
            break;
        case 4:
            lcd_dis_menu_2_1(0,0);
            lcd_dis_menu_2_2(1,0);
            lcd_dis_menu_2_3(2,0);
            lcd_dis_menu_2_4(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_OP_TorProtect,res);
                _Menu2Count1 = res; 
            }
            lcd_dis_menu_2_shu(3,_Menu2Count1);
            break;
        case 5:
            lcd_dis_menu_2_2(0,0);
            lcd_dis_menu_2_3(1,0);
            lcd_dis_menu_2_4(2,0);
            lcd_dis_menu_2_5(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_OPDir_Protect,res);
                _RmRead = ((res==0x69) ? 1:0);
            }
            if(_RmRead){
               lcd_dis_menu_2_31();
            }else{
                lcd_dis_menu_2_30();
            }
            break;
    }
#endif    
}

#ifndef LANGUAGE_EN
void lcd_dis_menu_3_0(Uint8 reverse){
    _DisWord0 = _ucharTabZhuang;
    _DisWord1 = _ucharTabTai;
    _DisWord2 = _ucharTabShu1;
    _DisWord3 = _ucharTabChu;
    lcd_dis_chinese_left(0,reverse);
}
void lcd_dis_menu_3_1(Uint8 reverse){
    _DisWord0 = _ucharTabKong;
    _DisWord1 = _ucharTabZhi2;
    _DisWord2 = _ucharTabLei;
    _DisWord3 = _ucharTabBie;
    lcd_dis_chinese_left(1,reverse);
}
void lcd_dis_menu_3_2(Uint8 reverse){
    _DisWord0 = _ucharTabTe;
    _DisWord1 = _ucharTabBie;
    _DisWord2 = _ucharTabKong;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese_left(2,reverse);
}
void lcd_dis_menu_3_3(Uint8 reverse){
    _DisWord0 = _ucharTabFan;
    _DisWord1 = _ucharTabKui;
    _DisWord2 = _ucharTabDian4;
    _DisWord3 = _ucharTabLiu;
    lcd_dis_chinese_left(3,reverse);
}
#endif
void lcd_dis_menu_3_wz(){
    _DisWord0 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    _DisWord1 = _ucharTabWei;
    _DisWord2 = _ucharTabZhi1;
    lcd_dis_chinese_right(3,0);
}
void lcd_dis_menu_3_jz(){
    _DisWord0 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    _DisWord1 = _ucharTabZhuan;
    _DisWord2 = _ucharTabJu;
    lcd_dis_chinese_right(3,0);
}


void lcd_dis_menu_3(){
    Uint16 res;
    
    _Menu = 4;
    lcd_dis_clr_all();
#ifndef  LANGUAGE_EN
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_3_0(1);
            lcd_dis_menu_3_1(0);
            lcd_dis_menu_3_2(0);
            lcd_dis_menu_3_3(0);
            if(_RmRead==4){
                lcd_dis_char(0,5,_ucharTabJian3,0);
                lcd_dis_char(0,6,_ucharTabShi4,0);
            }else{
                lcd_dis_smallchar(0,10,_ucharTabS,0);
                lcd_dis_smallchar(0,11,_ucharTabNum[_RmRead+1],0);
                lcd_dis_char(0,6,_ucharTabChu1,0);
                lcd_dis_char(0,7,_ucharTabDian,0);
            }
            break;
        case 1:
            lcd_dis_menu_3_0(0);
            lcd_dis_menu_3_1(1);
            lcd_dis_menu_3_2(0);
            lcd_dis_menu_3_3(0);
            if(_RmRead>3){
                break;
            }
            _DisWord0 = _ucharTabClr;
            _DisWord3 = _ucharTabClr;
            switch(_RmRead){
                case 0:
                    _DisWord1 = _ucharTabJiu;
                    _DisWord2 = _ucharTabDi2;
                    lcd_dis_chinese_right(1,0);
                    break;
                case 1:
                    _DisWord1 = _ucharTabLiang;
                    _DisWord2 = _ucharTabXian3;
                    lcd_dis_chinese_right(1,0);
                    break;
                case 2:
                    _DisWord1 = _ucharTabBi1;
                    _DisWord2 = _ucharTabLi;
                    lcd_dis_chinese_right(1,0);
                    break;
                case 3:
                    eedata_read(_Card,res);
                    if(res==8){
                        _DisWord1 = _ucharTabP0;
                        _DisWord2 = _ucharTabZong;
                        _DisWord3 = _ucharTabXian3;
                        lcd_dis_chinese_right(1,0);
                    }else if(res==2){
                        _DisWord1 = _ucharTabM0;
                        _DisWord2 = _ucharTabZong;
                        _DisWord3 = _ucharTabXian3;
                        lcd_dis_chinese_right(1,0);
                    }
                    break;
            }
            break;
        case 2:
            lcd_dis_menu_3_0(0);
            lcd_dis_menu_3_1(0);
            lcd_dis_menu_3_2(1);
            lcd_dis_menu_3_3(0);
            if(_RmRead>4){
                break;
            }
            _DisWord0 = _ucharTabClr;
            _DisWord3 = _ucharTabClr;
            switch(_RmRead){
                case 0:
                    _DisWord1 = _ucharTabLian;
                    _DisWord2 = _ucharTabSuo;
                    lcd_dis_chinese_right(2,0);
                    break;
                case 1:
                    _DisWord1 = _ucharTabES;
                    _DisWord2 = _ucharTabD0;
                    lcd_dis_chinese_right(2,0);
                    break;
                case 2:
                    _DisWord1 = _ucharTabZhong1;
                    _DisWord2 = _ucharTabDuan;
                    lcd_dis_chinese_right(2,0);
                    break;
                case 3:
                    _DisWord1 = _ucharTabZhi2;
                    _DisWord2 = _ucharTabDong;
                    lcd_dis_chinese_right(2,0);
                    break;
                case 4:
                    _DisWord1 = _ucharTabBian;
                    _DisWord2 = _ucharTabSu;
                    lcd_dis_chinese_right(2,0);
                    break;
            }
            break;
        case 3:
            if(fb_fw_read()){
                if(fb_tq_read()){
                    _FB_Temp = 0;
                    if(_RmRead==0){
                        lcd_dis_menu_3_wz();
                    }else{
                        lcd_dis_menu_3_jz();
                    }
                }else{
                    _RmRead = 0;
                    _FB_Temp = 0;
                    lcd_dis_menu_3_wz();
                }
            }else if(fb_tq_read()){
                _RmRead = 1;
                _FB_Temp = 0;
                lcd_dis_menu_3_jz();
            }else{
                _FB_Temp = 0xffff;
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabWu;
                _DisWord2 = _ucharTabFan;
                _DisWord3 = _ucharTabKui;
                lcd_dis_chinese_right(3,0);
            }
            break;
    }
#endif    
}

void lcd_dis_sxxx(Uint8 row,Uint8 num){
    Uint8 *pchar;
    
    if(num>4){
        return;
    }
    pchar = _ucharTabNum[num+1];
    lcd_dis_smallchar(row,2,_ucharTabS,0);
    lcd_dis_smallchar(row,3,pchar,0);
    lcd_dis_smallchar(row,12,_ucharTabMh,0);
    lcd_dis_char(row,2,_DisWord0,0);
    lcd_dis_char(row,3,_DisWord1,0);
    lcd_dis_char(row,4,_DisWord2,0);
    lcd_dis_char(row,5,_DisWord3,0);
}


#ifndef  LANGUAGE_EN
void lcd_dis_menu_300_1(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabDao5;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_2(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabDao5;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_3(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabZheng;
    _DisWord1 = _ucharTabZai;
    _DisWord2 = _ucharTabDa;
    _DisWord3 = _ucharTabKai;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_4(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabZheng;
    _DisWord1 = _ucharTabZai;
    _DisWord2 = _ucharTabGuan;
    _DisWord3 = _ucharTabBi;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_5(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabZheng;
    _DisWord1 = _ucharTabZai;
    _DisWord2 = _ucharTabYun;
    _DisWord3 = _ucharTabXing;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_6(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabGuo;
    _DisWord2 = _ucharTabJu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_7(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabGuo;
    _DisWord2 = _ucharTabJu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
}

void lcd_dis_menu_300_8(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabZhong1;
    _DisWord1 = _ucharTabTu;
    _DisWord2 = _ucharTabGuo;
    _DisWord3 = _ucharTabJu;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_9(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabDian4;
    _DisWord1 = _ucharTabJi1;
    _DisWord2 = _ucharTabDu;
    _DisWord3 = _ucharTabZhuan;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_10(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabYou;
    _DisWord3 = _ucharTabXiao;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_11(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabZhong1;
    _DisWord1 = _ucharTabTu;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_300_bh(Uint8 row){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabBi;
    _DisWord2 = _ucharTabHe;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,0);
}
void lcd_dis_menu_300_dk(Uint8 row){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabDuan;
    _DisWord2 = _ucharTabKai;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,0);
}
#endif
void lcd_dis_menu_300(){
    //Uint16 res;
    Uint8 r;
    
    _Menu = 9;
    lcd_dis_clr_all();
    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>10){
        return;
    }
    _DisWord0 = _ucharTabChu1;
    _DisWord1 = _ucharTabDian;
    _DisWord2 = _ucharTabXuan1;
    _DisWord3 = _ucharTabXiang;
    lcd_dis_sxxx(0,_Menu300Atemp);
    if((_uintCur>=0)&&(_uintCur<=9)){
        r = (_uintCur>=2) ? 3:(_uintCur+1);
        if(_EmRead==1){
            _EmRead = 0;
            sx_status(_Menu300Atemp);
        }
        if(_RmReadS){
            lcd_dis_menu_300_dk(r);
        }else{
            lcd_dis_menu_300_bh(r);
        }
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_300_1(1,1);
            lcd_dis_menu_300_2(2,0);
            lcd_dis_menu_300_3(3,0);
            break;
        case 1:
            lcd_dis_menu_300_1(1,0);
            lcd_dis_menu_300_2(2,1);
            lcd_dis_menu_300_3(3,0);
            break;
        case 2:
            lcd_dis_menu_300_1(1,0);
            lcd_dis_menu_300_2(2,0);
            lcd_dis_menu_300_3(3,1);
            break;
        case 3:
            lcd_dis_menu_300_2(1,0);
            lcd_dis_menu_300_3(2,0);
            lcd_dis_menu_300_4(3,1);
            break;
        case 4:
            lcd_dis_menu_300_3(1,0);
            lcd_dis_menu_300_4(2,0);
            lcd_dis_menu_300_5(3,1);
            break;
        case 5:
            lcd_dis_menu_300_4(1,0);
            lcd_dis_menu_300_5(2,0);
            lcd_dis_menu_300_6(3,1);
            break;
        case 6:
            lcd_dis_menu_300_5(1,0);
            lcd_dis_menu_300_6(2,0);
            lcd_dis_menu_300_7(3,1);
            break;
        case 7:
            lcd_dis_menu_300_6(1,0);
            lcd_dis_menu_300_7(2,0);
            lcd_dis_menu_300_8(3,1);
            break;
        case 8:
            lcd_dis_menu_300_7(1,0);
            lcd_dis_menu_300_8(2,0);
            lcd_dis_menu_300_9(3,1);
            break;
        case 9:
            lcd_dis_menu_300_8(1,0);
            lcd_dis_menu_300_9(2,0);
            lcd_dis_menu_300_10(3,1);
            break;
        case 10:
            lcd_dis_menu_300_9(1,0);
            lcd_dis_menu_300_10(2,0);
            lcd_dis_menu_300_11(3,1);
            lcd_dis_jinru(3);
            break;
    }
#endif
}

void lcd_dis_menu_300a(){
    Uint16 res;
    Uint8 reverse;
    
    _Menu = 10;
    lcd_dis_clr_all();
    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>1){
        return;
    }
    if(_Menu300Atemp>3){
        return;
    }
    _DisWord0 = _ucharTabWei;
    _DisWord1 = _ucharTabZhi1;
    _DisWord2 = _ucharTabXuan1;
    _DisWord3 = _ucharTabZe;
    lcd_dis_sxxx(0,_Menu300Atemp);
    if(_EmRead==1){
        get_eedata_snpos(_Menu300Atemp,&res);
        /*
        switch(_Menu300Atemp){
            case 0:
                eedata_read(_S1_Position,res);
                break;
            case 1:
                eedata_read(_S2_Position,res);
                break;
            case 2:
                eedata_read(_S3_Position,res);
                break;
            case 3:
                eedata_read(_S4_Position,res);
                break;
        }*/
        _Menu300ACount = res;
    }
    lcd_dis_char(1,0,_ucharTabDayu,0);
    lcd_dis_num_bai(1,2,_Menu300ACount,0);
    //lcd_dis_smallchar(1,2,pchar,0);
    lcd_dis_num_shi(1,3,_Menu300ACount,0);
    //lcd_dis_smallchar(1,3,pchar,0);
    lcd_dis_num_ge(1,4,_Menu300ACount,0);
    //lcd_dis_smallchar(1,4,pchar,0);
    lcd_dis_smallchar(1,5,_ucharTabBfhx,0);
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_char(1,3,_ucharTabKai,reverse);
    lcd_dis_char(1,4,_ucharTabDu1,reverse);
    
    _DisWord0 = _ucharTabChu1;
    _DisWord1 = _ucharTabDian;
    _DisWord2 = _ucharTabXuan1;
    _DisWord3 = _ucharTabZe;
    lcd_dis_sxxx(2,_Menu300Atemp);
    //reverse = (_uintCur==0) ? 0:1;
    reverse = _uintCur;
    if(_EmRead){
        _EmRead = 0;
        sx_status(_Menu300Atemp);
    }
    if(_RmReadS){
        _DisWord0 = _ucharTabClr;
        _DisWord1 = _ucharTabClr;
        _DisWord2 = _ucharTabDuan;
        _DisWord3 = _ucharTabKai;
        lcd_dis_chinese(3,1,reverse);
    }else{
        _DisWord0 = _ucharTabClr;
        _DisWord1 = _ucharTabClr;
        _DisWord2 = _ucharTabBi;
        _DisWord3 = _ucharTabHe;
        lcd_dis_chinese(3,1,reverse);
    }
#endif
}

//monitor relay option
void lcd_dis_menu_300b(){
    Uint16 res;
    Uint8 reverse;
    
    _Menu = 48;
    lcd_dis_clr_all();
    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>1){
        return;
    }
    _DisWord0 = _ucharTabJian3;
    _DisWord1 = _ucharTabShi4;
    _DisWord2 = _ucharTabJi6;
    _DisWord3 = _ucharTabDian4;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabQi2;
    _DisWord1 = _ucharTabXuan1;
    _DisWord2 = _ucharTabXiang;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
    
    reverse = (_uintCur==0) ? 1:0;
    _DisWord0 = _ucharTabBao1;
    _DisWord1 = _ucharTabHan;
    _DisWord2 = _ucharTabGuo;
    _DisWord3 = _ucharTabJu;
    lcd_dis_chinese_left(1,reverse);
    _DisWord0 = _ucharTabZhi6;
    _DisWord1 = _ucharTabShi1;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(1,reverse);
    
    reverse = _uintCur;
    _DisWord0 = _ucharTabBao1;
    _DisWord1 = _ucharTabHan;
    _DisWord2 = _ucharTabYuan;
    _DisWord3 = _ucharTabCheng;
    lcd_dis_chinese_left(2,reverse);
    _DisWord0 = _ucharTabZhi6;
    _DisWord1 = _ucharTabShi1;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(2,reverse);
    if(_uintCur){
        if(_EmRead==1){
            _EmRead = 0;
            eedata_read(_Monitor_With_Remote,res);
            if(res==0x69){
                _RmRead = 0;
            }else{
                _RmRead = 1;
            }
        }
    }else{
        if(_EmRead==1){
            _EmRead = 0;
            eedata_read(_Monitor_With_OverTorque,res);
            if(res==0x69){
                _RmRead = 0;
            }else{
                _RmRead = 1;
            }
        }
    }
    if(_RmRead){
        lcd_dis_char(_uintCur+1,7,_ucharTabFou,0);
    }else{
        lcd_dis_char(_uintCur+1,7,_ucharTabShi6,0);
    }
#endif   
}

void lcd_dis_menu_310(){
    Uint8 reverse;
    
    _Menu = 11;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>1){
        return;
    }
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabJiu;
    _DisWord2 = _ucharTabDi2;
    _DisWord3 = _ucharTabKong;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabZhi2;
    _DisWord1 = _ucharTabFang;
    _DisWord2 = _ucharTabShi2;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
    
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_char(1,3,_ucharTabBao,reverse);
    lcd_dis_char(1,3,_ucharTabChi,reverse);
    
    reverse = _uintCur;
    lcd_dis_char(2,3,_ucharTabDian,reverse);
    lcd_dis_char(2,3,_ucharTabDong,reverse);
#endif
}


void lcd_dis_menu_311(){
    Uint8 reverse;
    
    _Menu = 12;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>2){
        return;
    }
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabLiang;
    _DisWord2 = _ucharTabXian3;
    _DisWord3 = _ucharTabKong;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabZhi2;
    _DisWord1 = _ucharTabFang;
    _DisWord2 = _ucharTabShi2;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
    
    reverse = (_uintCur==0) ? 1:0;
    _DisWord0 = _ucharTabYou;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabKai;
    _DisWord3 = _ucharTabDh0;
    lcd_dis_chinese_left(1,reverse);
    _DisWord0 = _ucharTabWu;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabGuan;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(1,reverse);
    
    reverse = (_uintCur==1) ? 1:0;
    _DisWord0 = _ucharTabYou;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabGuan;
    _DisWord3 = _ucharTabDh0;
    lcd_dis_chinese_left(2,reverse);
    _DisWord0 = _ucharTabWu;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabKai;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(2,reverse);
    
    reverse = (_uintCur==2) ? 1:0;
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabJin1;
    _DisWord2 = _ucharTabYong;
    _DisWord3 = _ucharTabLiang;
    lcd_dis_chinese_left(3,reverse);
    _DisWord0 = _ucharTabXian3;
    _DisWord1 = _ucharTabKong;
    _DisWord2 = _ucharTabZhi2;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(3,reverse);
#endif    
}


#ifndef LANGUAGE_EN
void lcd_dis_menu_312_0(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabSi;
    _DisWord1 = _ucharTabQu;
    _DisWord2 = _ucharTabZhi3;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_312_1(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabDiu;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabDong;
    _DisWord3 = _ucharTabZuo;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_312_2(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabDi3;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabFa;
    _DisWord3 = _ucharTabWei;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_312_3(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGao;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabFa;
    _DisWord3 = _ucharTabWei;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_312_4(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabDi3;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabJiao0;
    _DisWord3 = _ucharTabZhun;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_312_5(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabGao;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabJiao0;
    _DisWord3 = _ucharTabZhun;
    lcd_dis_chinese_left(row,reverse);
}
#endif

void lcd_dis_menu_312(){
    Uint16 res;
    _Menu = 13;
    _Pre_Menu = 13;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>5){
        return;
    }
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabBi1;
    _DisWord2 = _ucharTabLi;
    _DisWord3 = _ucharTabKong;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabZhi2;
    _DisWord1 = _ucharTabXuan1;
    _DisWord2 = _ucharTabXiang;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
    while(1){
        switch(_uintCur){
            case 0:
                lcd_dis_menu_312_0(1,1);
                lcd_dis_menu_312_1(2,0);
                lcd_dis_menu_312_2(3,0);
                if(_EmRead){
                    _EmRead = 0;
                    eedata_read(_IC_Dbd,res);
                    _Menu312Count0 = res;
                }
                lcd_dis_num_shi(1,11,_Menu312Count0,0);
                //lcd_dis_smallchar(1,11,pchar,0);
                lcd_dis_smallchar(1,12,_ucharTabXd,0);
                lcd_dis_num_ge(1,13,_Menu312Count0,0);
                //lcd_dis_smallchar(1,13,pchar,0);
                lcd_dis_smallchar(1,14,_ucharTabBfhx,0);
                return;
            case 1:
                lcd_dis_menu_312_0(1,0);
                lcd_dis_menu_312_1(2,1);
                lcd_dis_menu_312_2(3,0);
                if(_EmRead){
                    _EmRead = 0;
                    eedata_read(_POSALS,res);
                    if(res==1){
                        _RmRead = 1;
                    }else if(res==3){
                        _RmRead = 2;
                    }else if(res==7){
                        _RmRead = 3;
                    }else{
                        _RmRead = 0;
                    }
                }
                if(_RmRead>3){
                    return;
                }
                switch(_RmRead){
                    case 0:
                        _DisWord0 = _ucharTabBao;
                        _DisWord1 = _ucharTabWei;
                        break;
                    case 1:
                        _DisWord0 = _ucharTabQuan;
                        _DisWord1 = _ucharTabKai;
                        break; 
                    case 2:
                        _DisWord0 = _ucharTabQuan;
                        _DisWord1 = _ucharTabGuan;
                        break;
                    case 3:
                        _DisWord0 = _ucharTabWei;
                        _DisWord1 = _ucharTabZhi1;
                        break;
                }
                lcd_dis_char(2,5,_DisWord0,0);
                lcd_dis_char(2,6,_DisWord1,0);
                return;
            case 2:
                lcd_dis_menu_312_0(1,0);
                lcd_dis_menu_312_1(2,0);
                lcd_dis_menu_312_2(3,1);
                if(_EmRead){
                    _EmRead = 0;
                    eedata_read(_IC_Low_VP,res);
                    if(res>100){
                        _Menu312Count1 = 100;
                    }else{
                        _Menu312Count1 = res;
                    }
                }
                lcd_dis_num_bai(3,11,_Menu312Count1,0);
                //lcd_dis_smallchar(3,11,pchar,0);
                lcd_dis_num_shi(3,12,_Menu312Count1,0);
                //lcd_dis_smallchar(3,12,pchar,0);
                lcd_dis_num_ge(3,13,_Menu312Count1,0);
                //lcd_dis_smallchar(3,13,pchar,0);
                lcd_dis_smallchar(3,14,_ucharTabBfhx,0);
                return;
            case 3:
                lcd_dis_menu_312_1(1,0);
                lcd_dis_menu_312_2(2,0);
                lcd_dis_menu_312_3(3,1);
                if(_EmRead){
                    _EmRead = 0;
                    eedata_read(_IC_High_VP,res);
                    if(res>100){
                        _Menu312Count2 = 100;
                    }else{
                        _Menu312Count2 = res;
                    }
                }
                lcd_dis_num_bai(3,11,_Menu312Count2,0);
                //lcd_dis_smallchar(3,11,pchar,0);
                lcd_dis_num_shi(3,12,_Menu312Count2,0);
                //lcd_dis_smallchar(3,12,pchar,0);
                lcd_dis_num_ge(3,13,_Menu312Count2,0);
                //lcd_dis_smallchar(3,13,pchar,0);
                lcd_dis_smallchar(3,14,_ucharTabBfhx,0);
                return;
            case 4:
                lcd_dis_menu_312_2(1,0);
                lcd_dis_menu_312_3(2,0);
                lcd_dis_menu_312_4(3,1);
                if(_EmRead){
                    _EmRead = 0;
                    _Menu312Count3 = alu_dis_ic();
                    if(_uchar_SignalPre1==_Menu312Count3){
                        break;
                    }
                    _uchar_SignalPre1 = _Menu312Count3;
                    _uintMenuCount = 0;
                }else{
                    _Menu312Count3 = alu_dis_ic();
                }
                lcd_dis_num_bai(3,9,_Menu312Count3,0);
                //lcd_dis_smallchar(3,9,pchar,0);
                lcd_dis_num_shi0(3,10,_Menu312Count3,0);
                //lcd_dis_smallchar(3,10,pchar,0);
                lcd_dis_smallchar(3,11,_ucharTabXd,0);
                lcd_dis_num_ge(3,12,_Menu312Count3,0);
                //lcd_dis_smallchar(3,12,pchar,0);
                lcd_dis_smallchar(3,13,_ucharTabm,0);
                lcd_dis_smallchar(3,14,_ucharTabA,0);
                break;
            case 5:
                lcd_dis_menu_312_3(1,0);
                lcd_dis_menu_312_4(2,0);
                lcd_dis_menu_312_5(3,1);
                if(_EmRead){
                    _EmRead = 0;
                    _Menu312Count4 = alu_dis_ic();
                    if(_uchar_SignalPre2==_Menu312Count4){
                        break;
                    }
                    _uchar_SignalPre2 = _Menu312Count4;
                    _uintMenuCount = 0;
                }else{
                    _Menu312Count4 = alu_dis_ic();
                }
                lcd_dis_num_bai(3,9,_Menu312Count4,0);
                //lcd_dis_smallchar(3,9,pchar,0);
                lcd_dis_num_shi0(3,10,_Menu312Count4,0);
                //lcd_dis_smallchar(3,10,pchar,0);
                lcd_dis_smallchar(3,11,_ucharTabXd,0);
                lcd_dis_num_ge(3,12,_Menu312Count4,0);
                //lcd_dis_smallchar(3,12,pchar,0);
                lcd_dis_smallchar(3,13,_ucharTabm,0);
                lcd_dis_smallchar(3,14,_ucharTabA,0);
                break;
        }
        clr_wdt();
        if(_uintMenuCount>=12000){
            return;
        }
        if((_ucharBackKey)||(_ucharConfKey)||(_ucharDownKey)){
            return;
        }
    }
 #endif
}

void lcd_dis_menu_buslist_0(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabBen;
    _DisWord1 = _ucharTabJi1;
    _DisWord2 = _ucharTabDi2;
    _DisWord3 = _ucharTabZhi4;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_Card,res);
        if(res==8){
            eedata_read(_DP_Adress,res);
            if(res>126){
                res = 0;
                eedata_write(_DP_Adress,0);
            }
            _BusCount0 = res;
        }else{
            eedata_read(_DP_Adress,res);
            if(res>247){
                res = 0;
                eedata_write(_DP_Adress,0);
            }
            _BusCount0 = res;
        }
    } 
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(1,10,_BusCount0,0);
    //lcd_dis_smallchar(1,10,pchar,0);
    lcd_dis_num_shi(1,11,_BusCount0,0);
    //lcd_dis_smallchar(1,11,pchar,0);
    lcd_dis_num_ge(1,12,_BusCount0,0);
    //lcd_dis_smallchar(1,12,pchar,0);
#endif
}
void lcd_dis_menu_buslist_1(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabBo8;
    _DisWord1 = _ucharTabTe8;
    _DisWord2 = _ucharTabLv8;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_BANDRT,res);
        if(res>7){
            res = 7;
            eedata_write(_BANDRT,7);
        }
        _RmRead = res;
    } 
    if(_RmRead>7){
        return;
    }
    switch(_RmRead){
        case 0:
            _DisWord0 = _ucharTabclr;
            _DisWord1 = _ucharTab0;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab3;
            break;
        case 1:
            _DisWord0 = _ucharTabclr;
            _DisWord1 = _ucharTab0;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab6;
            break;
        case 2:
            _DisWord0 = _ucharTabclr;
            _DisWord1 = _ucharTab1;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab2;
            break;
        case 3:
            _DisWord0 = _ucharTabclr;
            _DisWord1 = _ucharTab2;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab4;
            break;
        case 4:
            _DisWord0 = _ucharTabclr;
            _DisWord1 = _ucharTab4;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab8;
            break;
         case 5:
            _DisWord0 = _ucharTabclr;
            _DisWord1 = _ucharTab9;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab6;
            break;
        case 6:
            _DisWord0 = _ucharTab1;
            _DisWord1 = _ucharTab9;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab2;
            break;
        case 7:
            _DisWord0 = _ucharTab3;
            _DisWord1 = _ucharTab8;
            _DisWord2 = _ucharTabXd;
            _DisWord3 = _ucharTab4;
            break;
    }
#ifdef  LANGUAGE_EN
#else
    lcd_dis_smallchar(2,11,_DisWord0,0);
    lcd_dis_smallchar(2,12,_DisWord1,0);
    lcd_dis_smallchar(2,13,_DisWord2,0);
    lcd_dis_smallchar(2,14,_DisWord3,0);
    lcd_dis_smallchar(2,15,_ucharTabK,0);
#endif
}
void lcd_dis_menu_buslist_2(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabJiao;
    _DisWord1 = _ucharTabYan8;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_PARITY,res);
        if(res>2){
            res = 1;
            eedata_write(_PARITY,1);
        }
        _RmRead = res;
    } 
    if(_RmRead>2){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabQi8;
            _DisWord2 = _ucharTabJiao;
            _DisWord3 = _ucharTabYan8;
#endif
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabOu8;
            _DisWord2 = _ucharTabJiao;
            _DisWord3 = _ucharTabYan8;
#endif
            break;
        case 2:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabWu;
            _DisWord2 = _ucharTabJiao;
            _DisWord3 = _ucharTabYan8;
#endif
            break;
    }
#ifdef  LANGUAGE_EN
#else
    lcd_dis_chinese_right(3,0);
#endif
}

void lcd_dis_menu_buslist_3(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabDiu;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabShi;
    _DisWord3 = _ucharTabJian;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    eedata_read(_Card,res);
    if(res==8){
        if(_EmRead==1){
            _EmRead = 0;
            eedata_read(_DPSLTO,res);
            if(res>255){
                res = 255;
                eedata_write(_DPSLTO,res);
            }else if(res<1){
                res = 1;
                eedata_write(_DPSLTO,res);
            }
            _BusCount1 = res;
        }      
    }else{
        if(_EmRead==1){
            _EmRead = 0;
            eedata_read(_MODSLTO,res);
            if(res>255){
                res = 255;
                eedata_write(_MODSLTO,res);
            }else if(res<1){
                res = 1;
                eedata_write(_MODSLTO,res);
            }
            _BusCount1 = res;
        }       
    }
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(3,10,_BusCount1,0);
    //lcd_dis_smallchar(3,10,pchar,0);
    lcd_dis_num_shi(3,11,_BusCount1,0);
    //lcd_dis_smallchar(3,11,pchar,0);
    lcd_dis_num_ge(3,12,_BusCount1,0);
    //lcd_dis_smallchar(3,12,pchar,0);
    lcd_dis_smallchar(3,13,_ucharTabS,0);
#endif
}
void lcd_dis_menu_buslist_bw(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabBao;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(3,0);
}
void lcd_dis_menu_buslist_qk(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabQuan;
    _DisWord2 = _ucharTabKai;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(3,0);
}
void lcd_dis_menu_buslist_qg(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabQuan;
    _DisWord2 = _ucharTabGuan;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(3,0);
}
void lcd_dis_menu_buslist_4(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabDiu;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabDong;
    _DisWord3 = _ucharTabZuo;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_POSALS,res);
        _RmRead = (res+1)>>1;
    } 
    if(_RmRead>4){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabJin1;
            _DisWord2 = _ucharTabYong;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            
            lcd_dis_menu_buslist_qk();
#endif            
            break;
        case 2:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_qg();
#endif            
            break;
        case 3:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_bw();
#endif            
            break;
        case 4:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabWei;
            _DisWord2 = _ucharTabZhi1;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}
void lcd_dis_menu_buslist_5(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabZong;
    _DisWord1 = _ucharTabXian3;
    _DisWord2 = _ucharTabES;
    _DisWord3 = _ucharTabD0;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_ESD_Action,res);
        if(res==0x69){
            _RmRead = 0;
        }else if(res==0x96){
            _RmRead = 1;
        }else{
            _RmRead = 2;
        }
    } 
    if(_RmRead>2){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_qk();
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_qg();
#endif            
            break;
        case 2:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_bw();
#endif            
            break;
    }    
}
void lcd_dis_menu_buslist_6(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabDiao;
    _DisWord1 = _ucharTabJie;
    _DisWord2 = _ucharTabDi3;
    _DisWord3 = _ucharTabXian1;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_POSMIN,res);
        if(res>100){
            res = 0;
        }
        _BusCount2 = res;
    } 
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(3,10,_BusCount2,0);
    //lcd_dis_smallchar(3,10,pchar,0);
    lcd_dis_num_shi(3,11,_BusCount2,0);
    //lcd_dis_smallchar(3,11,pchar,0);
    lcd_dis_num_ge(3,12,_BusCount2,0);
    //lcd_dis_smallchar(3,12,pchar,0);
    lcd_dis_smallchar(3,13,_ucharTabBfhx,0);
#endif
}
void lcd_dis_menu_buslist_7(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabDiao;
    _DisWord1 = _ucharTabJie;
    _DisWord2 = _ucharTabGao;
    _DisWord3 = _ucharTabXian1;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_POSMAX,res);
        if(res>100){
            res = 0;
        }
        _BusCount3 = res;
    } 
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(3,10,_BusCount3,0);
    //lcd_dis_smallchar(3,10,pchar,0);
    lcd_dis_num_shi(3,11,_BusCount3,0);
    //lcd_dis_smallchar(3,11,pchar,0);
    lcd_dis_num_ge(3,12,_BusCount3,0);
    //lcd_dis_smallchar(3,12,pchar,0);
    lcd_dis_smallchar(3,13,_ucharTabBfhx,0);
#endif
}
void lcd_dis_menu_buslist_8(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabDiao;
    _DisWord1 = _ucharTabJie;
    _DisWord2 = _ucharTabSi;
    _DisWord3 = _ucharTabQu;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_IC_Dbd,res);
        if((res>99)||(res<3)){
            res = 3;
        }
        _BusCount4 = res;
    } 
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_shi0(3,11,_BusCount4,0);
    //lcd_dis_smallchar(3,11,pchar,0);
    lcd_dis_smallchar(3,12,_ucharTabXd,0);
    lcd_dis_num_ge(3,13,_BusCount4,0);
    //lcd_dis_smallchar(3,13,pchar,0);
    lcd_dis_smallchar(3,14,_ucharTabBfhx,0);
#endif
}
#ifndef  LANGUAGE_EN
void lcd_dis_menu_buslist_sr(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabShu1;
    _DisWord2 = _ucharTabRu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(3,0);
}
#endif
void lcd_dis_menu_buslist_9(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabFu1;
    _DisWord1 = _ucharTabZhu;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
    lcd_dis_smallchar(row,4,_ucharTab1,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_AUXMSK,res);
        _RmRead = (res&BIT4) ? 1:0;
    } 
    if(_RmRead>1){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_sr();
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabYuan;
            _DisWord2 = _ucharTabKai;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}
void lcd_dis_menu_buslist_10(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabFu1;
    _DisWord1 = _ucharTabZhu;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
    lcd_dis_smallchar(row,4,_ucharTab2,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_AUXMSK,res);
        _RmRead = (res&BIT5) ? 1:0;
    } 
    if(_RmRead>1){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_sr();
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabYuan;
            _DisWord2 = _ucharTabGuan;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}

void lcd_dis_menu_buslist_11(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabFu1;
    _DisWord1 = _ucharTabZhu;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
    lcd_dis_smallchar(row,4,_ucharTab3,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_AUXMSK,res);
        _RmRead = (res&BIT6) ? 1:0;
    } 
    if(_RmRead>1){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_sr();;
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabBao;
            _DisWord2 = _ucharTabChi;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}
void lcd_dis_menu_buslist_12(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabFu1;
    _DisWord1 = _ucharTabZhu;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(row,reverse);
    lcd_dis_smallchar(row,4,_ucharTab4,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_AUXMSK,res);
        _RmRead = (res&BIT7) ? 1:0;
    } 
    if(_RmRead>1){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_sr();
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabES;
            _DisWord2 = _ucharTabD0;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}
void lcd_dis_menu_buslist_13(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabRong;
    _DisWord1 = _ucharTabYu1;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_Redundancy,res);
        _RmRead = (res==0x69) ? 1:0;
    } 
    if(_RmRead>1){
        return;
    }
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabJin1;
            _DisWord2 = _ucharTabYong;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabYun1;
            _DisWord2 = _ucharTabXu;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}
void lcd_dis_menu_buslist_15(Uint8 row, Uint8 reverse){
    Uint16 res;

#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabZong;
    _DisWord1 = _ucharTabXian3;
    _DisWord2 = _ucharTabKong;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese_left(row,reverse);
#endif
    if(_uintCur!=_RowTemp){
        return;
    }
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_DPCtrl,res);
        _RmRead = (res==0x69) ? 0x69:0;
    } 
    switch(_RmRead){
        case 0:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabDian;
            _DisWord2 = _ucharTabDong;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
        case 0x69:
#ifdef  LANGUAGE_EN
#else
            _DisWord0 = _ucharTabClr;
            _DisWord1 = _ucharTabBao;
            _DisWord2 = _ucharTabChi;
            _DisWord3 = _ucharTabClr;
            lcd_dis_chinese_right(3,0);
#endif            
            break;
    }    
}
void (*lcd_dis_menu_buslist[])(Uint8 , Uint8 ) = {
    lcd_dis_menu_buslist_0,
    lcd_dis_menu_buslist_1,
    lcd_dis_menu_buslist_2,
    lcd_dis_menu_buslist_3,
    lcd_dis_menu_buslist_4,
    lcd_dis_menu_buslist_5,
    lcd_dis_menu_buslist_6,
    lcd_dis_menu_buslist_7,
    lcd_dis_menu_buslist_8,
    lcd_dis_menu_buslist_9,
    lcd_dis_menu_buslist_10,
    lcd_dis_menu_buslist_11,
    lcd_dis_menu_buslist_12,
    lcd_dis_menu_buslist_13,
    lcd_dis_menu_buslist_15
};
void lcd_dis_menu_profibus_list(Uint8 row, Uint8 reverse){
    
    if(_RowTemp>12){
        return;
    }
    switch(_RowTemp){
        case 0:
            lcd_dis_menu_buslist_0(row,reverse);
            break;
        case 1:
            lcd_dis_menu_buslist_3(row,reverse);
            break;
        case 2:
            lcd_dis_menu_buslist_4(row,reverse);
            break;
        case 3:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_buslist_5(row,reverse);
#endif
            break;
        case 4:
            lcd_dis_menu_buslist_6(row,reverse);
            break;
        case 5:
            lcd_dis_menu_buslist_7(row,reverse);
            break;
        case 6:
            lcd_dis_menu_buslist_8(row,reverse);
            break;
        case 7:
            lcd_dis_menu_buslist_9(row,reverse);
            break;
        case 8:
            lcd_dis_menu_buslist_10(row,reverse);
            break;
        case 9:
            lcd_dis_menu_buslist_11(row,reverse);
            break;
        case 10:
            lcd_dis_menu_buslist_12(row,reverse);
            break;
        case 11:
            lcd_dis_menu_buslist_13(row,reverse);
            break;
        case 12:
            lcd_dis_menu_buslist_15(row,reverse);
            break;
    }
}
//menu 313
void lcd_dis_menu_profibus(){
    Uint8 reverse;
    
    _Menu = 14;
    _Pre_Menu = 14;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>12){
        return;
    }
    lcd_dis_smallchar(0,0,_ucharTabP,0);
    lcd_dis_smallchar(0,1,_ucharTabxr,0);
    lcd_dis_smallchar(0,2,_ucharTabxo,0);
    lcd_dis_smallchar(0,3,_ucharTabxf,0);
    lcd_dis_smallchar(0,4,_ucharTabxi,0);
    lcd_dis_smallchar(0,5,_ucharTabxb,0);
    lcd_dis_smallchar(0,6,_ucharTabxu,0);
    lcd_dis_smallchar(0,7,_ucharTabxs,0);
    lcd_dis_char(0,4,_ucharTabShe,0);
    lcd_dis_char(0,5,_ucharTabZhi1,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    
    reverse = (_RowWord0==_uintCur) ? 1:0;
    _RowTemp = _RowWord0;
    lcd_dis_menu_profibus_list(1,reverse);
    
    reverse = (_RowWord1==_uintCur) ? 1:0;
    _RowTemp = _RowWord1;
    lcd_dis_menu_profibus_list(2,reverse);
    
    reverse = (_RowWord2==_uintCur) ? 1:0;
    _RowTemp = _RowWord2;
    lcd_dis_menu_profibus_list(3,reverse);
#endif
}


void lcd_dis_menu_modbus_list(Uint8 row, Uint8 reverse){
    
    if(_RowTemp>13){
        return;
    }
#ifdef  LANGUAGE_EN
    if(_RowTemp==5){
        
    }else{
        lcd_dis_menu_buslist[_RowTemp](row,reverse);
    }
#else
    lcd_dis_menu_buslist[_RowTemp](row,reverse);
#endif
    
}
void lcd_dis_menu_modbus(){
    Uint8 reverse;
    
    _Menu = 27;
    _Pre_Menu = 27;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>13){
        return;
    }
    lcd_dis_smallchar(0,2,_ucharTabM,0);
    lcd_dis_smallchar(0,3,_ucharTabxo,0);
    lcd_dis_smallchar(0,4,_ucharTabxd,0);
    lcd_dis_smallchar(0,5,_ucharTabxb,0);
    lcd_dis_smallchar(0,6,_ucharTabxu,0);
    lcd_dis_smallchar(0,7,_ucharTabxs,0);
    lcd_dis_char(0,4,_ucharTabShe,0);
    lcd_dis_char(0,5,_ucharTabZhi1,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    
    reverse = (_RowWord0==_uintCur) ? 1:0;
    _RowTemp = _RowWord0;
    lcd_dis_menu_modbus_list(1,reverse);
    
    reverse = (_RowWord1==_uintCur) ? 1:0;
    _RowTemp = _RowWord1;
    lcd_dis_menu_modbus_list(2,reverse);
    
    reverse = (_RowWord2==_uintCur) ? 1:0;
    _RowTemp = _RowWord2;
    lcd_dis_menu_modbus_list(3,reverse);
#endif
}

void lcd_dis_menu_posals(){
    Uint16 res;
    
    _Menu = 35;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else
    /*
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabClr;
    _DisWord2 = _ucharTabDiu;
    _DisWord3 = _ucharTabXin;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabWei;
    _DisWord1 = _ucharTabZhi1;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
     */
    lcd_dis_char(0,2,_ucharTabDiu,0);
    lcd_dis_char(0,3,_ucharTabXin,0);
    lcd_dis_char(0,4,_ucharTabWei,0);
    lcd_dis_char(0,5,_ucharTabZhi1,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
#endif   
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_LOSPOS,res);
        if(res>100){
            res = 0;
        }
        _BusCount5 = res;
    } 
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(2,6,_BusCount5,0);
    //lcd_dis_smallchar(2,6,pchar,0);
    lcd_dis_num_shi(2,7,_BusCount5,0);
    //lcd_dis_smallchar(2,7,pchar,0);
    lcd_dis_num_ge(2,8,_BusCount5,0);
    //lcd_dis_smallchar(2,8,pchar,0);
    lcd_dis_smallchar(2,9,_ucharTabBfhx,0);
#endif
}
#ifndef LANGUAGE_EN
void lcd_dis_aux_in(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabFu1;
    _DisWord2 = _ucharTabZhu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabWei7;
    _DisWord1 = _ucharTabShu1;
    _DisWord2 = _ucharTabRu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
}

void lcd_dis_aux_out(){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabFu1;
    _DisWord2 = _ucharTabZhu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_left(0,0);
}
void lcd_dis_aux_out0(){
    _DisWord0 = _ucharTabWei7;
    _DisWord1 = _ucharTabYuan;
    _DisWord2 = _ucharTabKai;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
}
void lcd_dis_aux_out1(){
    _DisWord0 = _ucharTabWei7;
    _DisWord1 = _ucharTabYuan;
    _DisWord2 = _ucharTabGuan;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
}
void lcd_dis_aux_out2(){
    _DisWord0 = _ucharTabWei7;
    _DisWord1 = _ucharTabBao;
    _DisWord2 = _ucharTabChi;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
}
void lcd_dis_aux_out3(){
    _DisWord0 = _ucharTabWei7;
    _DisWord1 = _ucharTabES;
    _DisWord2 = _ucharTabD0;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,13,_ucharTabMh,0);
}
#endif

void lcd_dis_high_feedback(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else   
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabGao;
    _DisWord2 = _ucharTabDian4;
    _DisWord3 = _ucharTabPing;
    lcd_dis_chinese_left(1,reverse);
    _DisWord0 = _ucharTabFan;
    _DisWord1 = _ucharTabKui;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(1,reverse);
    lcd_dis_smallchar(1,12,_ucharTabClr,reverse);
    lcd_dis_smallchar(1,13,_ucharTab1,reverse);
#endif
}
void lcd_dis_low_feedback(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else   
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabDi3;
    _DisWord2 = _ucharTabDian4;
    _DisWord3 = _ucharTabPing;
    lcd_dis_chinese_left(2,reverse);
    _DisWord0 = _ucharTabFan;
    _DisWord1 = _ucharTabKui;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(2,reverse);
    lcd_dis_smallchar(2,12,_ucharTabClr,reverse);
    lcd_dis_smallchar(2,13,_ucharTab1,reverse);
#endif
}
void lcd_dis_high_effect(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else   
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabGao;
    _DisWord2 = _ucharTabDian4;
    _DisWord3 = _ucharTabPing;
    lcd_dis_chinese_left(1,reverse);
    _DisWord0 = _ucharTabYou;
    _DisWord1 = _ucharTabXiao;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(1,reverse);
#endif
}
void lcd_dis_low_effect(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else   
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabDi3;
    _DisWord2 = _ucharTabDian4;
    _DisWord3 = _ucharTabPing;
    lcd_dis_chinese_left(2,reverse);
    _DisWord0 = _ucharTabYou;
    _DisWord1 = _ucharTabXiao;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(2,reverse);
#endif
}
void lcd_dis_menu_aux_com(){
    Uint8 reverse;
#ifdef  LANGUAGE_EN
#else  
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_high_feedback(reverse);
    
    reverse = (_uintCur==1) ? 1:0;
    lcd_dis_low_feedback(reverse);
#endif   
}
void lcd_dis_menu_aux_com0(){
    Uint8 reverse;
#ifdef  LANGUAGE_EN
#else  
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_high_effect(reverse);
    
    reverse = (_uintCur==1) ? 1:0;
    lcd_dis_low_effect(reverse);
#endif   
}
void lcd_dis_menu_aux1(){
   
    _Menu = 36;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_in();
    lcd_dis_smallchar(0,7,_ucharTab1,0);
#endif
    lcd_dis_menu_aux_com();    
}

void lcd_dis_menu_aux2(){
   
    _Menu = 37;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_in();
    lcd_dis_smallchar(0,7,_ucharTab2,0);
#endif
    lcd_dis_menu_aux_com(); 
}
void lcd_dis_menu_aux3(){
   
    _Menu = 38;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_in();
    lcd_dis_smallchar(0,7,_ucharTab3,0);
#endif
    lcd_dis_menu_aux_com(); 
}
void lcd_dis_menu_aux4(){
   
    _Menu = 39;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_in();
    lcd_dis_smallchar(0,7,_ucharTab4,0);
#endif
    lcd_dis_menu_aux_com(); 
}

void lcd_dis_menu_aux5(){
   
    _Menu = 40;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_out();
    lcd_dis_smallchar(0,7,_ucharTab1,0);
    lcd_dis_aux_out0();
#endif
    lcd_dis_menu_aux_com0(); 
}
void lcd_dis_menu_aux6(){
   
    _Menu = 41;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_out();
    lcd_dis_smallchar(0,7,_ucharTab2,0);
    lcd_dis_aux_out1();
#endif
    lcd_dis_menu_aux_com0(); 
}
void lcd_dis_menu_aux7(){
   
    _Menu = 42;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_out();
    lcd_dis_smallchar(0,7,_ucharTab3,0);
    lcd_dis_aux_out2();
#endif
    lcd_dis_menu_aux_com0(); 
}
void lcd_dis_menu_aux8(){
   
    _Menu = 43;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    lcd_dis_aux_out();
    lcd_dis_smallchar(0,7,_ucharTab4,0);
    lcd_dis_aux_out3();
#endif
    lcd_dis_menu_aux_com0(); 
}

void lcd_dis_menu_redudant(){
    Uint16 res,res1;
    _Menu = 46;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    _DisWord0 = _ucharTabRong;
    _DisWord1 = _ucharTabYu1;
    _DisWord2 = _ucharTabDi2;
    _DisWord3 = _ucharTabZhi4;
    lcd_dis_chinese(0,2,0);
#endif
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_Card,res);
        eedata_read(_DP_Adress2,res1);
        if(((res==8)&&(res1>126))||(res1>247)){
                res1 = 0;
        }
        eedata_write(_DP_Adress2,res1);
        _BusCount6 = res1;
    }   
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(2,6,_BusCount6,0);
    lcd_dis_num_shi(2,7,_BusCount6,0);
    lcd_dis_num_ge(2,8,_BusCount6,0);
#endif 
}

#ifndef LANGUAGE_EN
void lcd_dis_menu_320_1(Uint8 reverse){
    _DisWord0 = _ucharTabJiu;
    _DisWord1 = _ucharTabDi2;
    _DisWord2 = _ucharTabLian;
    _DisWord3 = _ucharTabSuo;
    lcd_dis_chinese_left(1,reverse);
}
void lcd_dis_menu_320_2(Uint8 reverse){
    _DisWord0 = _ucharTabYuan;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabLian;
    _DisWord3 = _ucharTabSuo;
    lcd_dis_chinese_left(2,reverse);
}
#endif
//menu lock
void lcd_dis_menu_320(){
    Uint16 res;
    
    _Menu = 15;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>1){
        return;
    }
    _DisWord0 = _ucharTabLian;
    _DisWord1 = _ucharTabSuo;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese(0,2,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    switch(_uintCur){
        case 0:
            lcd_dis_menu_320_1(1);
            lcd_dis_menu_320_2(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Local_Lock,res);
                _RmRead = (res==0x69) ? 1:0;
            }   
            if(_RmRead){
                lcd_dis_buyunxu(1,5,0);
            }else{
                lcd_dis_yunxu(1,5,0);
            }
            break;
        case 1:
            lcd_dis_menu_320_1(0);
            lcd_dis_menu_320_2(1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Remote_Lock,res);
                _RmRead1 = (res==0x69) ? 1:0;
            }   
            if(_RmRead1){
                lcd_dis_buyunxu(2,5,0);
            }else{
                lcd_dis_yunxu(2,5,0);
            }
            break;
    }
#endif      
}

void lcd_dis_menu_321(){
    Uint8 reverse;
    _Menu = 16;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>1){
        return;
    }
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabKong;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese(0,2,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_yunxu(1,3,reverse);
    lcd_dis_buyunxu(2,3,!reverse);
#endif    
}
#ifndef LANGUAGE_EN
void lcd_dis_menu_3210_1(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabDong;
    _DisWord3 = _ucharTabZuo;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_3210_2(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabYou;
    _DisWord3 = _ucharTabXiao;
    lcd_dis_chinese_left(row,reverse);
    _DisWord0 = _ucharTabDian4;
    _DisWord1 = _ucharTabPing;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,reverse);
}
void lcd_dis_chaoyue(Uint8 row, Uint8 reverse){
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabChao;
    _DisWord3 = _ucharTabYue;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_3210_3(Uint8 row, Uint8 reverse){
    lcd_dis_chaoyue(row,reverse);
    _DisWord0 = _ucharTabGuo;
    _DisWord1 = _ucharTabRe;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,reverse);
}
void lcd_dis_menu_3210_4(Uint8 row, Uint8 reverse){
    lcd_dis_chaoyue(row,reverse);
    _DisWord0 = _ucharTabTing;
    _DisWord1 = _ucharTabWei;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,reverse);
}
void lcd_dis_menu_3210_5(Uint8 row, Uint8 reverse){
    lcd_dis_chaoyue(row,reverse);
    _DisWord0 = _ucharTabLian;
    _DisWord1 = _ucharTabSuo;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,reverse);
}
void lcd_dis_menu_3210_6(Uint8 row, Uint8 reverse){
    lcd_dis_chaoyue(row,reverse);
    _DisWord0 = _ucharTabDing;
    _DisWord1 = _ucharTabShi;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(row,reverse);
}
#endif
void lcd_dis_menu_3210(){
    Uint16 res;
    _Menu = 17;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>5){
        return;
    }
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese(0,2,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    switch(_uintCur){
        case 0:
            lcd_dis_menu_3210_1(1,1);
            lcd_dis_menu_3210_2(2,0);
            lcd_dis_menu_3210_3(3,0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_ESD_Action,res);
                _RmRead = ((res==0x69)?0:((res==0x96)?1:2));
            }  
            switch(_RmRead){
                case 0:
                    _DisWord0 = _ucharTabClr;
                    _DisWord1 = _ucharTabClr;
                    _DisWord2 = _ucharTabQuan;
                    _DisWord3 = _ucharTabKai;
                    lcd_dis_chinese_right(1,0);
                    break;
                case 1:
                    _DisWord0 = _ucharTabClr;
                    _DisWord1 = _ucharTabClr;
                    _DisWord2 = _ucharTabQuan;
                    _DisWord3 = _ucharTabGuan;
                    lcd_dis_chinese_right(1,0);
                    break;
                case 2:
                    _DisWord0 = _ucharTabClr;
                    _DisWord1 = _ucharTabClr;
                    _DisWord2 = _ucharTabBao;
                    _DisWord3 = _ucharTabWei;
                    lcd_dis_chinese_right(1,0);
                    break;
            }
            break;
        case 1:
            lcd_dis_menu_3210_1(1,0);
            lcd_dis_menu_3210_2(2,1);
            lcd_dis_menu_3210_3(3,0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_AUXMSK,res);
                _RmRead = ((res&BIT3) ? 0:1);
            }  
            switch(_RmRead){
                case 0:
                    lcd_dis_char(2,7,_ucharTabGao,0);
                    break;
                case 1:
                    lcd_dis_char(2,7,_ucharTabDi3,0);
                    break;
            }
            break;
        case 2:
            lcd_dis_menu_3210_1(1,0);
            lcd_dis_menu_3210_2(2,0);
            lcd_dis_menu_3210_3(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_ESD_ExceedHot,res);
                _RmRead = ((res==0x69) ? 1:0);
            }  
            switch(_RmRead){
                case 0:
                    lcd_dis_char(3,7,_ucharTabShi6,0);
                    break;
                case 1:
                    lcd_dis_char(3,7,_ucharTabFou,0);
                    break;
            }
            break;
        case 3:
            lcd_dis_menu_3210_2(1,0);
            lcd_dis_menu_3210_3(2,0);
            lcd_dis_menu_3210_4(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_ESD_ExceedSp,res);
                _RmRead = ((res==0x69) ? 1:0);
            }  
            switch(_RmRead){
                case 0:
                    lcd_dis_char(3,7,_ucharTabShi6,0);
                    break;
                case 1:
                    lcd_dis_char(3,7,_ucharTabFou,0);
                    break;
            }
            break;
        case 4:
            lcd_dis_menu_3210_3(1,0);
            lcd_dis_menu_3210_4(2,0);
            lcd_dis_menu_3210_5(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_ESD_ExceedLock,res);
                _RmRead = ((res==0x69) ? 1:0);
            }  
            switch(_RmRead){
                case 0:
                    lcd_dis_char(3,7,_ucharTabShi6,0);
                    break;
                case 1:
                    lcd_dis_char(3,7,_ucharTabFou,0);
                    break;
            }
            break;
        case 5:
            lcd_dis_menu_3210_4(1,0);
            lcd_dis_menu_3210_5(2,0);
            lcd_dis_menu_3210_6(3,1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_ESD_ExceedTime,res);
                _RmRead = ((res==0x69) ? 1:0);
            }  
            switch(_RmRead){
                case 0:
                    lcd_dis_char(3,7,_ucharTabShi6,0);
                    break;
                case 1:
                    lcd_dis_char(3,7,_ucharTabFou,0);
                    break;
            }
            break;
    }
#endif   
}

void lcd_dis_menu_322(){
    _Menu = 18;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>2){
        return;
    }
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabZhong1;
    _DisWord2 = _ucharTabDuan;
    _DisWord3 = _ucharTabDing;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabShi;
    _DisWord1 = _ucharTabCao;
    _DisWord2 = _ucharTabZuo;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
    
    switch(_uintCur){
        case 0:
            lcd_dis_buyunxu(1,2,1);
            lcd_dis_guanyunxu(0);
            lcd_dis_kaiyunxu(0);
            break;
        case 1:
            lcd_dis_buyunxu(1,2,0);
            lcd_dis_guanyunxu(1);
            lcd_dis_kaiyunxu(0);
            break;
        case 2:
            lcd_dis_buyunxu(1,2,0);
            lcd_dis_guanyunxu(0);
            lcd_dis_kaiyunxu(1);
            break;
    }
#endif    
}
#ifndef LANGUAGE_EN
void lcd_dis_menu_3220_0(Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabShi;
    _DisWord2 = _ucharTabQi;
    _DisWord3 = _ucharTabDong;
    lcd_dis_chinese_left(0,reverse);
    lcd_dis_char(0,4,_ucharTabWei,reverse);
}
void lcd_dis_menu_3220_1(Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabShi;
    _DisWord2 = _ucharTabTing;
    _DisWord3 = _ucharTabZhi;
    lcd_dis_chinese_left(1,reverse);
    lcd_dis_char(1,4,_ucharTabWei,reverse);
}

void lcd_dis_menu_3220_2(Uint8 reverse){
    _DisWord0 = _ucharTabYun;
    _DisWord1 = _ucharTabXing;
    _DisWord2 = _ucharTabShi;
    _DisWord3 = _ucharTabJian;
    lcd_dis_chinese_left(2,reverse);
}
void lcd_dis_menu_3220_3(Uint8 reverse){
    _DisWord0 = _ucharTabTing;
    _DisWord1 = _ucharTabZhi;
    _DisWord2 = _ucharTabShi;
    _DisWord3 = _ucharTabJian;
    lcd_dis_chinese_left(3,reverse);
}
void lcd_dis_menu_3221_0(Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabShi;
    _DisWord2 = _ucharTabQi;
    _DisWord3 = _ucharTabDong;
    lcd_dis_chinese_left(0,reverse);
    lcd_dis_char(0,4,_ucharTabWei,reverse);
}
void lcd_dis_menu_3221_1(Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabShi;
    _DisWord2 = _ucharTabTing;
    _DisWord3 = _ucharTabZhi;
    lcd_dis_chinese_left(1,reverse);
    lcd_dis_char(1,4,_ucharTabWei,reverse);
}
void lcd_dis_menu_3221_2(Uint8 reverse){
    lcd_dis_menu_3220_2(reverse);
}
void lcd_dis_menu_3221_3(Uint8 reverse){
    lcd_dis_menu_3220_3(reverse);
}
#endif

void lcd_dis_menu_3220(){
    Uint16 res;
    _Menu = 19;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_3220_0(1);
            lcd_dis_menu_3220_1(0);
            lcd_dis_menu_3220_2(0);
            lcd_dis_menu_3220_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Start_Pos,res);
                if(res>100){
                    res = 100;
                    eedata_write(_Start_Pos,res);
                }
                _Menu3220Count0 = res;
            }
            res = _Menu3220Count0;
            break;
        case 1:
            lcd_dis_menu_3220_0(0);
            lcd_dis_menu_3220_1(1);
            lcd_dis_menu_3220_2(0);
            lcd_dis_menu_3220_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Stop_Pos,res);
                if(res>100){
                    res = 100;
                    eedata_write(_Stop_Pos,res);
                }
                _Menu3220Count1 = res;
            }  
            res = _Menu3220Count1;
            break;
        case 2:
            lcd_dis_menu_3220_0(0);
            lcd_dis_menu_3220_1(0);
            lcd_dis_menu_3220_2(1);
            lcd_dis_menu_3220_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_MoveTime,res);
                if((res>99)||(res<1)){
                    res = 99;
                    eedata_write(_MoveTime,res);
                }
                _Menu3220Count2 = res;
            }  
            res = _Menu3220Count2;
            break;
        case 3:
            lcd_dis_menu_3220_0(0);
            lcd_dis_menu_3220_1(0);
            lcd_dis_menu_3220_2(0);
            lcd_dis_menu_3220_3(1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_StopTime,res);
                if((res>99)||(res<1)){
                    res = 99;
                    eedata_write(_StopTime,res);
                }
                _Menu3220Count3 = res;
            }  
            res = _Menu3220Count3;
            break;
    }
    lcd_dis_num_bai(_uintCur,11,res,0);
    lcd_dis_num_shi(_uintCur,12,res,0);
    lcd_dis_num_ge(_uintCur,13,res,0);
    lcd_dis_smallchar(_uintCur,14,_ucharTabBfhx,0);
#endif          
}

void lcd_dis_menu_3221(){
    Uint16 res;
    
    _Menu = 20;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_3221_0(1);
            lcd_dis_menu_3221_1(0);
            lcd_dis_menu_3221_2(0);
            lcd_dis_menu_3221_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Start_Pos,res);
                if(res>100){
                    res = 100;
                    eedata_write(_Start_Pos,res);
                }
                _Menu3221Count0 = res;
            }
            res = _Menu3221Count0;
            break;
        case 1:
            lcd_dis_menu_3221_0(0);
            lcd_dis_menu_3221_1(1);
            lcd_dis_menu_3221_2(0);
            lcd_dis_menu_3221_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Stop_Pos,res);
                if(res>100){
                    res = 100;
                    eedata_write(_Stop_Pos,res);
                }
                _Menu3221Count1 = res;
            }  
            res = _Menu3221Count1;
            break;
        case 2:
            lcd_dis_menu_3221_0(0);
            lcd_dis_menu_3221_1(0);
            lcd_dis_menu_3221_2(1);
            lcd_dis_menu_3221_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_MoveTime,res);
                if((res>99)||(res<1)){
                    res = 99;
                    eedata_write(_MoveTime,res);
                }
                _Menu3221Count2 = res;
            }  
            res = _Menu3221Count2;
            break;
        case 3:
            lcd_dis_menu_3221_0(0);
            lcd_dis_menu_3221_1(0);
            lcd_dis_menu_3221_2(0);
            lcd_dis_menu_3221_3(1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_StopTime,res);
                if((res>99)||(res<1)){
                    res = 99;
                    eedata_write(_StopTime,res);
                }
                _Menu3221Count3 = res;
            }  
            res = _Menu3221Count3;
            break;
    }
    lcd_dis_num_bai(_uintCur,11,res,0);
    lcd_dis_num_shi(_uintCur,12,res,0);
    lcd_dis_num_ge(_uintCur,13,res,0);
    lcd_dis_smallchar(_uintCur,14,_ucharTabBfhx,0);
#endif   
}

void lcd_dis_menu_323(){
    Uint16 res;
    
    _Menu = 21;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabSha7;
    _DisWord2 = _ucharTabChe7;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabDong;
    _DisWord1 = _ucharTabShi;
    _DisWord2 = _ucharTabJian;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
#endif
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_POSMIT,res);
        if(res>50){
            res = 0;
            eedata_write(_POSMIT,res);
        }
        _Menu323Count = res;
    } 
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(2,5,_Menu323Count,0);
    lcd_dis_num_shi(2,6,_Menu323Count,0);
    lcd_dis_num_ge(2,7,_Menu323Count,0);
    lcd_dis_smallchar(2,8,_ucharTabm,0);
    lcd_dis_smallchar(2,9,_ucharTabS,0);
#endif    
}

void lcd_dis_menu_3230_1(Uint8 reverse){
#ifdef  LANGUAGE_EN   
#else
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabXiang1;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(1,reverse);
#endif 
}
void lcd_dis_menu_3230_2(Uint8 reverse){
#ifdef  LANGUAGE_EN   
#else
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabXiang1;
    _DisWord2 = _ucharTabShe;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(2,reverse);
#endif 
}
void lcd_dis_menu_3230_3(Uint8 reverse){
#ifdef  LANGUAGE_EN   
#else
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabSu;
    _DisWord3 = _ucharTabDu1;
    lcd_dis_chinese_left(3,reverse);
#endif 
}

void lcd_dis_menu_3230(){
    Uint16 res;
    
    _Menu = 22;
    lcd_dis_clr_all();
#ifndef  LANGUAGE_EN
    _DisWord0 = _ucharTabBian;
    _DisWord1 = _ucharTabSu;
    _DisWord2 = _ucharTabKong;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabXuan1;
    _DisWord1 = _ucharTabXiang;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
#endif
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_3230_1(1);
            lcd_dis_menu_3230_2(0);
            lcd_dis_menu_3230_3(0);
            lcd_dis_jinru(1);
#endif
            break;
        case 1:
#ifdef  LANGUAGE_EN
#else
            lcd_dis_menu_3230_1(0);
            lcd_dis_menu_3230_2(1);
            lcd_dis_menu_3230_3(0);
            lcd_dis_jinru(2);
#endif
            break;
        case 2:
#ifdef  LANGUAGE_EN      
#endif  
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_ESD_Speed,res);
                _Menu3230Count0 = res;
            }
#ifdef  LANGUAGE_EN  
#else
            lcd_dis_menu_3230_1(0);
            lcd_dis_menu_3230_2(0);
            lcd_dis_menu_3230_3(1);
            lcd_dis_num_bai(3,10,_Menu3230Count0,0);
            lcd_dis_num_shi(3,11,_Menu3230Count0,0);
            lcd_dis_num_ge(3,12,_Menu3230Count0,0);
            lcd_dis_smallchar(3,13,_ucharTabr,0);
            lcd_dis_smallchar(3,14,_ucharTabFxgx,0);
            lcd_dis_smallchar(3,15,_ucharTabm,0);
#endif 
            break;
    }
}

void lcd_dis_menu_32301(){
    Uint16 res;
    Uint8 reverse;
    
    _Menu = 23;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabXiang1;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabQu;
    _DisWord1 = _ucharTabJian;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    
    lcd_dis_num_shi(0,12,_Menu22_ConfCount,0);
    lcd_dis_num_ge(0,13,_Menu22_ConfCount,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
#endif
    if(_EmRead==1){
        _EmRead = 0;
        if(_Menu22_ConfCount==1){
            _Menu32301Count0 = 0;
            eedata_read(_OP_Position[0],res);
            _Menu32301Count1 = res;
            eedata_read(_OP_Speed[0],res);
            _Menu32301Count2 = res;
        }else if(_Menu22_ConfCount==10){
            eedata_read(_OP_Position[8],res);
            _Menu32301Count0 = res;
            _Menu32301Count1 = 100;
            eedata_read(_OP_Speed[9],res);
            _Menu32301Count2 = res;
        }else{
            get_eedata_oppos(_Menu22_ConfCount-2,&res);
            _Menu32301Count0 = res;
            get_eedata_oppos(_Menu22_ConfCount-1,&res);
            _Menu32301Count1 = res;
            get_eedata_opspeed(_Menu22_ConfCount-1,&res);
            _Menu32301Count2 = res;
        }
    }
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(1,2,_Menu32301Count0,0);
    lcd_dis_num_shi(1,3,_Menu32301Count0,0);
    lcd_dis_num_ge(1,4,_Menu32301Count0,0);
    lcd_dis_smallchar(1,5,_ucharTabBfhx,0);
    
    lcd_dis_char(1,3,_ucharTabHl,0);
    lcd_dis_char(1,4,_ucharTabHl,0);
    
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_num_bai(1,10,_Menu32301Count1,reverse);
    lcd_dis_num_shi(1,11,_Menu32301Count1,reverse);
    lcd_dis_num_ge(1,12,_Menu32301Count1,reverse);
    lcd_dis_smallchar(1,13,_ucharTabBfhx,0);
    
    lcd_dis_num_shi(2,0,_Menu22_ConfCount,0);
    lcd_dis_num_ge(2,1,_Menu22_ConfCount,0);
    _DisWord0 = _ucharTabQu;
    _DisWord1 = _ucharTabJian;
    _DisWord2 = _ucharTabSu;
    _DisWord3 = _ucharTabDu1;
    lcd_dis_chinese(2,1,0);
    lcd_dis_smallchar(2,10,_ucharTabMh,0);
    
    reverse = (_uintCur==1) ? 1:0;
    lcd_dis_num_bai(3,3,_Menu32301Count2,reverse);
    lcd_dis_num_shi(3,4,_Menu32301Count2,reverse);
    lcd_dis_num_ge(3,5,_Menu32301Count2,reverse);
    
    lcd_dis_smallchar(3,8,_ucharTabr,0);
    lcd_dis_smallchar(3,9,_ucharTabFxgx,0);
    lcd_dis_smallchar(3,10,_ucharTabm,0);
#endif
}

void lcd_dis_menu_32302(){
    Uint16 res;
    Uint8 reverse;
    
    _Menu = 24;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabXiang1;
    _DisWord2 = _ucharTabWei;
    _DisWord3 = _ucharTabZhi1;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabQu;
    _DisWord1 = _ucharTabJian;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    
    lcd_dis_num_shi(0,12,_Menu23_ConfCount,0);
    lcd_dis_num_ge(0,13,_Menu23_ConfCount,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
#endif
    if(_EmRead==1){
        _EmRead = 0;
        if(_Menu23_ConfCount==1){
            _Menu32302Count0 = 100;
            eedata_read(_CL_Position[0],res);
            _Menu32302Count1 = res;
            eedata_read(_CL_Speed[0],res);
            _Menu32302Count2 = res;
        }else if(_Menu23_ConfCount==10){
            eedata_read(_CL_Position[8],res);
            _Menu32302Count0 = res;
            _Menu32302Count1 = 0;
            eedata_read(_CL_Speed[9],res);
            _Menu32302Count2 = res;
        }else{
            get_eedata_clpos(_Menu23_ConfCount-2,&res);
            _Menu32302Count0 = res;
            get_eedata_clpos(_Menu23_ConfCount-1,&res);
            _Menu32302Count1 = res;
            get_eedata_clspeed(_Menu23_ConfCount-1,&res);
            _Menu32302Count2 = res;
        }
    }
#ifdef  LANGUAGE_EN
#else
    lcd_dis_num_bai(1,2,_Menu32302Count0,0);
    lcd_dis_num_shi(1,3,_Menu32302Count0,0);
    lcd_dis_num_ge(1,4,_Menu32302Count0,0);
    lcd_dis_smallchar(1,5,_ucharTabBfhx,0);
    
    lcd_dis_char(1,3,_ucharTabHl,0);
    lcd_dis_char(1,4,_ucharTabHl,0);
    
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_num_bai(1,10,_Menu32302Count1,reverse);
    lcd_dis_num_shi(1,11,_Menu32302Count1,reverse);
    lcd_dis_num_ge(1,12,_Menu32302Count1,reverse);
    lcd_dis_smallchar(1,13,_ucharTabBfhx,0);
    
    lcd_dis_num_shi(2,0,_Menu23_ConfCount,0);
    lcd_dis_num_ge(2,1,_Menu23_ConfCount,0);
    _DisWord0 = _ucharTabQu;
    _DisWord1 = _ucharTabJian;
    _DisWord2 = _ucharTabSu;
    _DisWord3 = _ucharTabDu1;
    lcd_dis_chinese(2,1,0);
    lcd_dis_smallchar(2,10,_ucharTabMh,0);
    
    reverse = (_uintCur==1) ? 1:0;
    lcd_dis_num_bai(3,3,_Menu32302Count2,reverse);
    lcd_dis_num_shi(3,4,_Menu32302Count2,reverse);
    lcd_dis_num_ge(3,5,_Menu32302Count2,reverse);
    
    lcd_dis_smallchar(3,8,_ucharTabr,0);
    lcd_dis_smallchar(3,9,_ucharTabFxgx,0);
    lcd_dis_smallchar(3,10,_ucharTabm,0);
#endif    
    
}

void lcd_dis_menu_324(){
    Uint8 reverse;
    
    _Menu = 45;
    lcd_dis_clr_all();    
#ifdef  LANGUAGE_EN
#else  
    if(_uintCur>2){
        return;
    }
    _DisWord0 = _ucharTabBian;
    _DisWord1 = _ucharTabSu;
    _DisWord2 = _ucharTabKong;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese(0,2,0);
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_yunxu(1,3,reverse);
    lcd_dis_buyunxu(2,3,!reverse);
#endif   
}
#ifndef  LANGUAGE_EN
void lcd_dis_menu_330_1(Uint8 reverse){
    _DisWord0 = _ucharTabGao;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabHao;
    _DisWord3 = _ucharTabDui;
    lcd_dis_chinese_left(1,0);
    _DisWord0 = _ucharTabYing;
    _DisWord1 = _ucharTabClr;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(1,reverse); 
}
void lcd_dis_menu_330_2(Uint8 reverse){
    _DisWord0 = _ucharTabDi3;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabJiao0;
    _DisWord3 = _ucharTabZhun;
    lcd_dis_chinese_left(2,reverse);
}
void lcd_dis_menu_330_3(Uint8 reverse){
    _DisWord0 = _ucharTabGao;
    _DisWord1 = _ucharTabXin;
    _DisWord2 = _ucharTabJiao0;
    _DisWord3 = _ucharTabZhun;
    lcd_dis_chinese_left(3,reverse);
}
#endif

void lcd_dis_fkma(Uint16 num){
#ifdef  LANGUAGE_EN
#else
    Uint8 row;
    if(_uintCur==1){
        row = 2;
    }else{
        row = 3;
    }
    lcd_dis_num_qian(row,9,num,0);
    lcd_dis_num_bai(row,10,num,0);
    lcd_dis_smallchar(row,11,_ucharTabXd,0);
    lcd_dis_num_shi0(row,12,num,0);
    lcd_dis_num_ge(row,13,num,0);
    lcd_dis_smallchar(row,14,_ucharTabm,0);
    lcd_dis_smallchar(row,15,_ucharTabA,0);
#endif
}
void lcd_dis_menu_330(){
    Uint16 res;
    
    _Menu = 25;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabWei;
    _DisWord2 = _ucharTabZhi1;
    _DisWord3 = _ucharTabFan;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabKui;
    _DisWord1 = _ucharTabDian4;
    _DisWord2 = _ucharTabLiu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);   
   
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_330_1(1);
            lcd_dis_menu_330_2(0);
            lcd_dis_menu_330_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Pos_BackLogic,res);
                _RmRead = ((res==0x69) ? 1:0);
            }
            if(_RmRead){
                lcd_dis_char(1,6,_ucharTabQuan,0);
                lcd_dis_char(1,7,_ucharTabKai,0);
            }else{
                lcd_dis_char(1,6,_ucharTabQuan,0);
                lcd_dis_char(1,7,_ucharTabGuan,0);
            }
            break;
        case 1:
            lcd_dis_menu_330_1(0);
            lcd_dis_menu_330_2(1);
            lcd_dis_menu_330_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Pos_BackL,res);
                _VPDA = res;
                _Menu330Count = res;
            }
            res = alu_dis_position_back();
            lcd_dis_fkma(res);
            break;
        case 2:
            lcd_dis_menu_330_1(0);
            lcd_dis_menu_330_2(0);
            lcd_dis_menu_330_3(1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Pos_BackH,res);
                _VPDA = res;
                _Menu330Count = res;
            }
            res = alu_dis_position_back();
            lcd_dis_fkma(res);
            break;
    }
#endif 
}

void lcd_dis_menu_331(){
    Uint16 res;
    
    _Menu = 26;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabZhuan;
    _DisWord2 = _ucharTabJu;
    _DisWord3 = _ucharTabFan;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabKui;
    _DisWord1 = _ucharTabDian4;
    _DisWord2 = _ucharTabLiu;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);   
   
    if(_uintCur>2){
        return;
    }
    //menu_331 have the same lists as menu_330
    switch(_uintCur){
        case 0:
            lcd_dis_menu_330_1(1);
            lcd_dis_menu_330_2(0);
            lcd_dis_menu_330_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Tor_BackLogic,res);
                _RmRead = ((res==0x69) ? 0:1);
            }
            if(_RmRead){
                lcd_dis_char(1,6,_ucharTabLing6,0);
                lcd_dis_char(1,7,_ucharTabWei,0);
            }else{
                lcd_dis_char(1,6,_ucharTabMan,0);
                lcd_dis_char(1,7,_ucharTabDu6,0);
            }
            break;
        case 1:
            lcd_dis_menu_330_1(0);
            lcd_dis_menu_330_2(1);
            lcd_dis_menu_330_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Tor_BackL,res);
                _NJDA = res;
                _Menu331Count = res;
            }
            res = alu_dis_position_back();
            lcd_dis_fkma(res);
            break;
        case 2:
            lcd_dis_menu_330_1(0);
            lcd_dis_menu_330_2(0);
            lcd_dis_menu_330_3(1);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Tor_BackH,res);
                _NJDA = res;
                _Menu331Count = res;
            }
            res = alu_dis_tor_back();
            lcd_dis_fkma(res);
            break;
    }
#endif     
}
void lcd_dis_menu_4_0(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabXuan;
    _DisWord1 = _ucharTabNiu;
    _DisWord2 = _ucharTabXin;
    _DisWord3 = _ucharTabHao;
    lcd_dis_chinese_left(0,reverse);
#endif
}
void lcd_dis_menu_4_1(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabYuan;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabXin;
    _DisWord3 = _ucharTabHao;
    lcd_dis_chinese_left(1,reverse);
#endif
}
void lcd_dis_menu_4_2(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabZhuan;
    _DisWord1 = _ucharTabJu;
    _DisWord2 = _ucharTabXin;
    _DisWord3 = _ucharTabHao;
    lcd_dis_chinese_left(2,reverse);
#endif
}
void lcd_dis_menu_4_3(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabZong;
    _DisWord1 = _ucharTabXian3;
    _DisWord2 = _ucharTabKong;
    _DisWord3 = _ucharTabZhi2;
    lcd_dis_chinese_left(3,reverse);
#endif
}

void lcd_dis_menu_4(){
     Uint16 res;
    
    _Menu = 5;
    _uchar_SignalPre = 0;
    lcd_dis_clr_all();
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_4_0(1);
            lcd_dis_menu_4_1(0);
            lcd_dis_menu_4_2(0);
            lcd_dis_menu_4_3(0);
#ifndef  LANGUAGE_EN
            lcd_dis_jinru(0);
#endif    
            break;
        case 1:
            lcd_dis_menu_4_0(0);
            lcd_dis_menu_4_1(1);
            lcd_dis_menu_4_2(0);
            lcd_dis_menu_4_3(0);
#ifndef  LANGUAGE_EN
            lcd_dis_jinru(1);
#endif   
            break;
        case 2:
            lcd_dis_menu_4_0(0);
            lcd_dis_menu_4_1(0);
            lcd_dis_menu_4_2(1);
            lcd_dis_menu_4_3(0);
#ifndef  LANGUAGE_EN
            lcd_dis_jinru(2);
#endif   
            break;
        case 3:
            lcd_dis_menu_4_0(0);
            lcd_dis_menu_4_1(0);
            lcd_dis_menu_4_2(0);
            lcd_dis_menu_4_3(1);
            while(1){
                clr_wdt();
#ifndef  LANGUAGE_EN
                eedata_read(_Card,res);
                if(res==0xaa){
                    lcd_dis_char(3,5,_ucharTabWu,0);
                }else{
                    lcd_dis_char(3,5,_ucharTabYou,0);
                }
#endif 
                if(_strAlarmFlag & _PowerDownFlag){
                    return;
                }
                if(_ucharOpenKey){
                    while(1){
                        if(_strAlarmFlag & _PowerDownFlag){
                            return;
                        }
                        _uintMenuCount = 0;
                        ClrWdt();//test inside wdt
                        if((_ucharBackKey)||(_ucharDownKey)){
                            return;
                        }
                    }
                }
                if(_ucharCloseKey){
                    while(1){
                        if(_strAlarmFlag & _PowerDownFlag){
                            return;
                        }
                        _uintMenuCount = 0;
                        clr_wdt();//test outside wdt
                        if((_ucharBackKey)||(_ucharDownKey)){
                            return;
                        }
                    }
                }
                if((_ucharBackKey)||(_ucharDownKey)){
                    return;
                }
                if(_uintMenuCount>12000){
                    return;
                }
            }
            break;
    }       
}
#ifndef  LANGUAGE_EN
void lcd_dis_menu_40_1(Uint8 reverse){
    _DisWord0 = _ucharTabFang;
    _DisWord1 = _ucharTabShi2;
    _DisWord2 = _ucharTabXuan;
    _DisWord3 = _ucharTabNiu;
    lcd_dis_chinese_left(1,reverse);
}
void lcd_dis_menu_40_2(Uint8 reverse){
    _DisWord0 = _ucharTabCao;
    _DisWord1 = _ucharTabZuo;
    _DisWord2 = _ucharTabXuan;
    _DisWord3 = _ucharTabNiu;
    lcd_dis_chinese_left(2,reverse);
}
#endif

void lcd_dis_menu_40(){
    Uint8 reverse;
    
    _Menu = 31;
    _uchar_OpenPre = 0;
    _uchar_ClosePre = 0;
    _uchar_IdlePre = 0;
    _uchar_LocalPre = 0;
    _uchar_RemotePre = 0;	
    _uchar_StopPre = 0;
    lcd_dis_clr_all();
    if(_uintCur>1){
        return;
    }
#ifndef  LANGUAGE_EN
    di_close1();
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabXuan;
    _DisWord2 = _ucharTabNiu;
    _DisWord3 = _ucharTabXin;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabHao;
    _DisWord1 = _ucharTabCha;
    _DisWord2 = _ucharTabXun;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);     
    
    reverse = ((_uintCur==0) ? 1:0);
    lcd_dis_menu_40_1(reverse);
    lcd_dis_menu_40_2(!reverse);
#endif
    while(1){
        di_close1();
        clr_wdt();
        
        if(_uintCur==0){
    #ifdef  LANGUAGE_EN
    #endif          
            _CNIE = 1;
            _CN11IE = 1;
            if(in_stop()){
                _uchar_LocalPre = 0;
                _uchar_RemotePre = 0;
                if(_uchar_StopPre==0x69){
                    goto menu_40_end;
                }else{
                    _uintMenuCount = 0;
                    _uchar_StopPre = 0x69;
                }
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabTing;
                _DisWord3 = _ucharTabZhi;
                lcd_dis_chinese_right(1,0);
    #endif     
            }else if(in_local()){
                _uchar_StopPre = 0;
                _uchar_RemotePre = 0;
                if(_uchar_LocalPre==0x69){
                    goto menu_40_end;
                }else{
                    _uintMenuCount = 0;
                    _uchar_LocalPre = 0x69;
                }
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabJiu;
                _DisWord3 = _ucharTabDi2;
                lcd_dis_chinese_right(1,0);
    #endif     
            }else if(in_remote()){
                _uchar_StopPre = 0;
                _uchar_LocalPre = 0;
                if(_uchar_RemotePre==0x69){
                    goto menu_40_end;
                }else{
                    _uintMenuCount = 0;
                    _uchar_RemotePre = 0x69;
                }
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabYuan;
                _DisWord3 = _ucharTabCheng;
                lcd_dis_chinese_right(1,0);
    #endif     
            }else{
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabYou;
                _DisWord3 = _ucharTabWu;
                lcd_dis_chinese_right(1,0);
    #endif                
            }
        }else{
    #ifdef  LANGUAGE_EN
    #endif          
            _T3IE = 1;
            if(l_op_read()){
                _uchar_ClosePre = 0;
                _uchar_IdlePre = 0;
                if(_uchar_OpenPre==0x69){
                    goto menu_40_end;
                }else{
                    _uintMenuCount = 0;
                    _uchar_OpenPre = 0x69;
                }
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabDa;
                _DisWord3 = _ucharTabKai;
                lcd_dis_chinese_right(2,0);
    #endif     
            }else if(l_cl_read()){
                _uchar_OpenPre = 0;
                _uchar_IdlePre = 0;
                if(_uchar_ClosePre==0x69){
                    goto menu_40_end;
                }else{
                    _uintMenuCount = 0;
                    _uchar_ClosePre = 0x69;
                }
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabGuan;
                _DisWord3 = _ucharTabBi;
                lcd_dis_chinese_right(2,0);
    #endif     
            }else{
                _uchar_OpenPre = 0;
                _uchar_ClosePre = 0;
                if(_uchar_IdlePre==0x69){
                    goto menu_40_end;
                }else{
                    _uintMenuCount = 0;
                    _uchar_IdlePre = 0x69;
                }
    #ifdef  LANGUAGE_EN
    #else 
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabClr;
                _DisWord2 = _ucharTabKong1;
                _DisWord3 = _ucharTabWei;
                lcd_dis_chinese_right(2,0);
    #endif                
            }
        }
    menu_40_end:
        clr_wdt();     
        if(_strAlarmFlag & _PowerDownFlag){
            di_open();
            return;
        }
        if(_ucharBackKey){
            di_open();
            return;
        }
        if(_ucharDownKey){
            return;
        }
        if(_uintMenuCount>12000){
            di_open();
            return;
        }
    }
}

#ifndef  LANGUAGE_EN
void lcd_dis_menu_41_1(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabYuan;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabDa;
    _DisWord3 = _ucharTabKai;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_2(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabYuan;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabGuan;
    _DisWord3 = _ucharTabBi;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_3(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabYuan;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabBao;
    _DisWord3 = _ucharTabChi;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_4(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabYuan;
    _DisWord1 = _ucharTabCheng;
    _DisWord2 = _ucharTabZi1;
    _DisWord3 = _ucharTabDong;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_5(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabBi1;
    _DisWord1 = _ucharTabLi;
    _DisWord2 = _ucharTabShu1;
    _DisWord3 = _ucharTabRu;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_6(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabES;
    _DisWord1 = _ucharTabD0;
    _DisWord2 = _ucharTabXin;
    _DisWord3 = _ucharTabHao;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_7(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabKai;
    _DisWord1 = _ucharTabFa;
    _DisWord2 = _ucharTabLian;
    _DisWord3 = _ucharTabSuo;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_8(Uint8 row,Uint8 reverse){
    _DisWord0 = _ucharTabGuan;
    _DisWord1 = _ucharTabFa;
    _DisWord2 = _ucharTabLian;
    _DisWord3 = _ucharTabSuo;
    lcd_dis_chinese_left(row,reverse);
}
void lcd_dis_menu_41_yxh(Uint8 row){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabYou;
    _DisWord2 = _ucharTabXin;
    _DisWord3 = _ucharTabHao;
    lcd_dis_chinese_right(row,0);
}
void lcd_dis_menu_41_wxh(Uint8 row){
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabWu;
    _DisWord2 = _ucharTabXin;
    _DisWord3 = _ucharTabHao;
    lcd_dis_chinese_right(row,0);
}
#endif

void (*lcd_dis_menu_41_list[])(Uint8 ,Uint8 ) = {
    lcd_dis_menu_41_1,
    lcd_dis_menu_41_2,
    lcd_dis_menu_41_3,
    lcd_dis_menu_41_4,
    lcd_dis_menu_41_5,
    lcd_dis_menu_41_6,
    lcd_dis_menu_41_7,
    lcd_dis_menu_41_8
};

void lcd_dis_menu_41(){
    Uint16 res;
    Uint8 sig,row;
    
    _Menu = 32;
    _uchar_SignalPre = 0;
    lcd_dis_clr_all();
    if(_uintCur>7){
        return;
    }
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabYuan;
    _DisWord2 = _ucharTabCheng;
    _DisWord3 = _ucharTabXin;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabHao;
    _DisWord1 = _ucharTabCha;
    _DisWord2 = _ucharTabXun;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);     
    
    if(_uintCur<2){
        lcd_dis_menu_41_list[0](1,(_uintCur==0));
        lcd_dis_menu_41_list[1](2,(_uintCur==1));
        lcd_dis_menu_41_list[2](3,0);
    }else{
        lcd_dis_menu_41_list[_uintCur-2](1,0);
        lcd_dis_menu_41_list[_uintCur-1](2,0);
        lcd_dis_menu_41_list[_uintCur](3,1);
    }
    while(1){
        if(_uintCur==4){
            res = alu_dis_ic();
            _Menu41Count0 = res;
            if(res==_uchar_SignalPre){
                goto menu_41_end;
            }
            _uchar_SignalPre = res;
            _uintMenuCount = 0;
            lcd_dis_num_bai(3,9,_Menu41Count0,0);
            lcd_dis_num_shi0(3,10,_Menu41Count0,0);
            lcd_dis_smallchar(3,11,_ucharTabXd,0);
            lcd_dis_num_ge(3,12,_Menu41Count0,0);
            lcd_dis_smallchar(3,13,_ucharTabm,0);
            lcd_dis_smallchar(3,14,_ucharTabA,0);
            goto menu_41_end;
        }
        row = 3;
        switch(_uintCur){
            case 0:
                sig = r_op_read();
                row = 1;
                break;
            case 1:
                sig = r_cl_read();
                row = 2;
                break;
            case 2:
                sig = r_st_read();
                break;
            case 3:
                sig = r_cv_read();
                break;
            case 5:
                sig = r_esd_read();
                break;
            case 6:
                sig = r_op_hold_read();
                break;
            case 7:
                sig = r_cl_hold_read();
                break;
        }
        if(sig){
            if(_uchar_SignalPre==0x69){
                goto menu_41_end;
            }else{
                _uintMenuCount = 0;
                _uchar_SignalPre = 0x69;
            }
            lcd_dis_menu_41_yxh(row);
        }else{
            if(_uchar_SignalPre==0x96){
                goto menu_41_end;
            }else{
                _uintMenuCount = 0;
                _uchar_SignalPre = 0x96;
            }
            lcd_dis_menu_41_wxh(row);
        }
    menu_41_end:
        clr_wdt();     
        if(_strAlarmFlag & _PowerDownFlag){
            return;
        }
        if(_ucharBackKey){
            return;
        }
        if(_ucharDownKey){
            return;
        }
        if(_uintMenuCount>12000){
            return;
        }          
    }
#endif
    
}
void lcd_dis_menu_43_content(){
    Uint8 skip;
    
    if(((_strAlarmFlag & _CTFlag)==0)&&((_strAlarmFlag & _OTFlag)==0)){
        lcd_dis_clr_alarm();
    }
    if(_EmRead==1){
        skip = 0;
    }else if(_uchar_SignalPre!=_VPPercent){
        _uchar_SignalPre = _VPPercent;
        skip = 0;
    }else{
        skip = 1;
    }
#ifdef  LANGUAGE_EN
#else    
    if(skip==0){
        lcd_dis_num_bai(1,12,_VPPercent,0);
        lcd_dis_num_shi(1,13,_VPPercent,0);
        lcd_dis_num_ge(1,14,_VPPercent,0);
        lcd_dis_smallchar(1,15,_ucharTabBfhx,0);
    }
#endif
    if(_EmRead==1){
        skip = 0;
    }else if(_uchar_SignalPre!=_VPPercent){
        _uchar_SignalPre = _NJPercent_Temp;
        skip = 0;
    }else{
        skip = 1;
    }
#ifdef  LANGUAGE_EN
#else  
    if(skip==0){
        lcd_dis_num_bai(2,12,_NJPercent_Temp,0);
        lcd_dis_num_shi(2,13,_NJPercent_Temp,0);
        lcd_dis_num_ge(2,14,_NJPercent_Temp,0);
        lcd_dis_smallchar(2,15,_ucharTabBfhx,0);
    }
#endif
}
void lcd_dis_menu_43(){

    _Menu = 32;
    _uchar_SignalPre = 0;
    lcd_dis_clr_all();
    if(_uintCur>7){
        return;
    }
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabZhuan;
    _DisWord2 = _ucharTabJu;
    _DisWord3 = _ucharTabXin;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabHao;
    _DisWord1 = _ucharTabCha;
    _DisWord2 = _ucharTabXun;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0); 
    
    _DisWord0 = _ucharTabFa;
    _DisWord1 = _ucharTabWei;
    _DisWord2 = _ucharTabKai;
    _DisWord3 = _ucharTabDu1;
    lcd_dis_chinese_left(1,0);
    _DisWord0 = _ucharTabZhuan;
    _DisWord1 = _ucharTabJu;
    _DisWord2 = _ucharTabShu;
    _DisWord3 = _ucharTabZhi3;
    lcd_dis_chinese_left(2,0);
#endif
    lcd_dis_menu_43_content();
}

void lcd_dis_menu_44(){
    Uint8 res;
    
    _Menu = 44;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabXiang5;
    _DisWord1 = _ucharTabTi;
    _DisWord2 = _ucharTabXuan1;
    _DisWord3 = _ucharTabZe;
    lcd_dis_chinese(0,2,0);  
    lcd_dis_smallchar(0,12,_ucharTabMh,0);
    if(_EmRead==1){
        _EmRead = 0;
        eedata_read(_BIG_SHUCK,res);
        _RmRead = ((res==0x69) ? 1:0);
    }
    if(_RmRead){
        lcd_dis_char(2,3,_ucharTabDa1,0);
    }else{
        lcd_dis_char(2,2,_ucharTabQi1,0);
        lcd_dis_char(2,3,_ucharTabTa,0);
    }
    lcd_dis_char(2,4,_ucharTabXiang5,0);
    lcd_dis_char(2,5,_ucharTabTi,0);
#endif 
}

void lcd_dis_menu_5_1(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabXian;
    _DisWord1 = _ucharTabShi1;
    _DisWord2 = _ucharTabFang;
    _DisWord3 = _ucharTabShi2;
    lcd_dis_chinese_left(0,0);
#endif    
}
void lcd_dis_menu_5_2(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabXiu;
    _DisWord1 = _ucharTabGai;
    _DisWord2 = _ucharTabKou;
    _DisWord3 = _ucharTabLing;
    lcd_dis_chinese_left(1,0);
#endif    
}
void lcd_dis_menu_5_3(Uint8 reverse){
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabHui;
    _DisWord1 = _ucharTabFu;
    _DisWord2 = _ucharTabChu;
    _DisWord3 = _ucharTabChang;
    lcd_dis_chinese_left(2,0);
    _DisWord0 = _ucharTabShe;
    _DisWord1 = _ucharTabZhi1;
    _DisWord2 = _ucharTabClr;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(2,0);
#endif    
}

void lcd_dis_menu_5(){
    Uint16 res;
    
    _Menu = 6;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
            lcd_dis_menu_5_1(1);
            lcd_dis_menu_5_2(0);
            lcd_dis_menu_5_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_InverseDisEnable,res);
                _RmRead = ((res==0x69) ? 1:0);
            }
            if(_RmRead){
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabDao;
                _DisWord2 = _ucharTabXian;
                _DisWord3 = _ucharTabShi1;
                lcd_dis_chinese_right(0,0);
            }else{
                _DisWord0 = _ucharTabClr;
                _DisWord1 = _ucharTabZheng;
                _DisWord2 = _ucharTabXian;
                _DisWord3 = _ucharTabShi1;
                lcd_dis_chinese_right(0,0);
            }
            break;
        case 1:
            lcd_dis_menu_5_1(0);
            lcd_dis_menu_5_2(1);
            lcd_dis_menu_5_3(0);
            if(_EmRead==1){
                _EmRead = 0;
                eedata_read(_Code_Orde,res);
                _Menu5Count0 = res;
            }
            lcd_dis_num_bai(2,12,_Menu5Count0,0);
            lcd_dis_num_shi(2,13,_Menu5Count0,0);
            lcd_dis_num_ge(2,14,_Menu5Count0,0);
            break;
        case 2:
            lcd_dis_menu_5_1(0);
            lcd_dis_menu_5_2(0);
            lcd_dis_menu_5_3(1);
            break;
    } 
#endif  
}

void lcd_dis_menu_50(){
    Uint8 reverse;
    
    _Menu = 34;
    lcd_dis_clr_all();
#ifdef  LANGUAGE_EN
#else
    _DisWord0 = _ucharTabClr;
    _DisWord1 = _ucharTabHui;
    _DisWord2 = _ucharTabFu;
    _DisWord3 = _ucharTabChu;
    lcd_dis_chinese_left(0,0);
    _DisWord0 = _ucharTabChang;
    _DisWord1 = _ucharTabShe;
    _DisWord2 = _ucharTabZhi1;
    _DisWord3 = _ucharTabClr;
    lcd_dis_chinese_right(0,0);
    lcd_dis_smallchar(0,14,_ucharTabMh,0);
    
    reverse = (_uintCur==0) ? 1:0;
    lcd_dis_char(1,4,_ucharTabShi6,reverse);
    lcd_dis_char(2,4,_ucharTabFou,!reverse);
#endif
}

#ifdef TEST
void lcd_test(){
    lcd_init();
    lcd_dis_clr_all();
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