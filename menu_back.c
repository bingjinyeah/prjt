#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"
#include "menu_conf.h"
#include "lcd.h"
#include "code.h"

void menu_back_1(){
    _Menu = 0;
    lcd_dis_clr_all();
    _System_Back = true;
}

void menu_back_2(){
    cal_limit_length();
    _uintCur = 0;
    lcd_dis_menu_1();
}

void menu_back_3(){
    _uintCur = 1;
    lcd_dis_menu_1();
}

void menu_back_4(){
    _uintCur = 2;
    lcd_dis_menu_1();
}

void menu_back_5(){
    _uintCur = 3;
    lcd_dis_menu_1();
}

void menu_back_8(){
    _RmRead = _Menu300Atemp;
    _uintCur = 0;
    lcd_dis_menu_3();
}

void menu_back_9(){
    _uintCur = 10;
    lcd_dis_menu_300();
}

void menu_back_10(){
    _uintCur = 1;
    _RmRead = 0;
    lcd_dis_menu_3();
}

void menu_back_11(){
    _uintCur = 1;
    _RmRead = 1;
    lcd_dis_menu_3();
}

void menu_back_12(){
    Uint16 res,res1;
    
    _uintCur = 1;
    _RmRead = 2;
    eedata_read(_IC_Low_VP,res);
    eedata_read(_IC_High_VP,res1);
    if(res>=res1){
        res = 0x69;
    }else{
        res = 0xff;
    }
    eedata_write(_IC_Logic,res);
    lcd_dis_menu_3();
}

void menu_back_13(){
    _uintCur = 1;
    _RmRead = 3;
    lcd_dis_menu_3();
}

void menu_back_14(){
    _uintCur = 2;
    _RmRead = 0;
    lcd_dis_menu_3();
}

void menu_back_15(){
    _uintCur = 2;
    _RmRead = 1;
    lcd_dis_menu_3();
}

void menu_back_16(){
    _uintCur = 0;
    lcd_dis_menu_321();
}

void menu_back_17(){
    _uintCur = 2;
    _RmRead = 2;
    lcd_dis_menu_3();
}

void menu_back_18(){
    _uintCur = 1;
    lcd_dis_menu_322();
}

void menu_back_19(){
    _uintCur = 2;
    lcd_dis_menu_322();
}

void menu_back_20(){
    _uintCur = 2;
    _RmRead = 3;
    lcd_dis_menu_3();
}

void menu_back_45(){
    _uintCur = 2;
    _RmRead = 4;
    lcd_dis_menu_3();
}

void menu_back_21(){
    _uintCur = 0;
    lcd_dis_menu_324();
}

void menu_back_22(){
    _uintCur = 0;
    lcd_dis_menu_3230();
}

void menu_back_23(){
    _uintCur = 1;
    lcd_dis_menu_3230();
}

void menu_back_24(){
    _uintCur = 3;
    _RmRead = 0;
    lcd_dis_menu_3();
}

void menu_back_25(){
    _uintCur = 3;
    _RmRead = 1;
    lcd_dis_menu_3();
}
void menu_back_26(){
    menu_back_13();
}

void menu_back_30(){
    _uintCur = 0;
    lcd_dis_menu_4();
}

void menu_back_31(){
    _uintCur = 1;
    lcd_dis_menu_4();
}

void menu_back_32(){
    _uintCur = 2;
    lcd_dis_menu_4();
}

void menu_back_33(){
    _uintCur = 2;
    lcd_dis_menu_5();
}

void menu_back_35(){
    
    if(_Pre_Menu==14){
        _uintCur = 2;
        _RowWord2 = 2;
        _RowWord1 = 1;
        _RowWord0 = 0;
        _EmRead = 1;
        _RmRead = 4;
        lcd_dis_menu_profibus();        
    }else if(_Pre_Menu==27){
        _uintCur = 4;
        _RowWord2 = 4;
        _RowWord1 = 3;
        _RowWord0 = 2;
        _EmRead = 1;
        _RmRead = 4;
        lcd_dis_menu_modbus();        
    }else{
        _uintCur = 1;
        _EmRead = 0;
        _RmRead = 3;
        lcd_dis_menu_312();  
    }
}

void menu_back_36(){
    Uint16 res;
    
    eedata_read(_Card,res);
    if(res==8){
        _uintCur = 7;
        _RowWord2 = 7;
        _RowWord1 = 6;
        _RowWord0 = 5;
        _EmRead = 1;
        lcd_dis_menu_profibus();
    }else{
        _uintCur = 9;
        _RowWord2 = 9;
        _RowWord1 = 8;
        _RowWord0 = 7;
        _EmRead = 1;
        lcd_dis_menu_modbus(); 
    }
}

void menu_back_37(){
    Uint16 res;
    
    eedata_read(_Card,res);
    if(res==8){
        _uintCur = 8;
        _RowWord2 = 8;
        _RowWord1 = 7;
        _RowWord0 = 6;
        _EmRead = 1;
        lcd_dis_menu_profibus();
    }else{
        _uintCur = 10;
        _RowWord2 = 10;
        _RowWord1 = 9;
        _RowWord0 = 8;
        _EmRead = 1;
        lcd_dis_menu_modbus(); 
    }
}

void menu_back_38(){
    Uint16 res;
    
    eedata_read(_Card,res);
    if(res==8){
        _uintCur = 9;
        _RowWord2 = 9;
        _RowWord1 = 8;
        _RowWord0 = 7;
        _EmRead = 1;
        lcd_dis_menu_profibus();
    }else{
        _uintCur = 11;
        _RowWord2 = 11;
        _RowWord1 = 10;
        _RowWord0 = 9;
        _EmRead = 1;
        lcd_dis_menu_modbus(); 
    }
}

void menu_back_39(){
    Uint16 res;
    
    eedata_read(_Card,res);
    if(res==8){
        _uintCur = 10;
        _RowWord2 = 10;
        _RowWord1 = 9;
        _RowWord0 = 8;
        _EmRead = 1;
        lcd_dis_menu_profibus();
    }else{
        _uintCur = 12;
        _RowWord2 = 12;
        _RowWord1 = 11;
        _RowWord0 = 10;
        _EmRead = 1;
        lcd_dis_menu_modbus(); 
    }
}

void menu_back_40(){
    menu_back_36();
}

void menu_back_41(){
    menu_back_37();
}

void menu_back_42(){
    menu_back_38();
}

void menu_back_43(){
    menu_back_39();
}

void menu_back_44(){
    _L_OP_Count = 0;
    lcd_dis_menu_50();
}

void menu_back_46(){
    Uint16 res;
    
    eedata_read(_Card,res);
    if(res==8){
        _uintCur = 11;
        _RowWord2 = 11;
        _RowWord1 = 10;
        _RowWord0 = 9;
        _EmRead = 0;
        _RmRead = 1;
        lcd_dis_menu_profibus();
    }else{
        _uintCur = 13;
        _RowWord2 = 13;
        _RowWord1 = 12;
        _RowWord0 = 11;
        _EmRead = 0;
        _RmRead = 1;
        lcd_dis_menu_modbus(); 
    }
}

#ifdef  LANGUAGE_EN

void menu_back_47(){
    _uintCur = 3;
    lcd_dis_menu_4();
}
#endif

void menu_back_48(){
    _uintCur = 0;
    _RmRead = 4;
    lcd_dis_menu_3();
}

void (*menu_back_func[])() = {
    NULL,
    menu_back_1,
    menu_back_1,
    menu_back_2,
    menu_back_3,
    menu_back_4,
    menu_back_5,
    NULL,
    NULL,
    menu_back_8,
    menu_back_9,
    menu_back_10,
    menu_back_11,
    menu_back_12,
    menu_back_13,
    menu_back_14,
    menu_back_15,
    menu_back_16,
    menu_back_17,
    menu_back_18,
    menu_back_19,
    menu_back_20,
    menu_back_21,
    menu_back_22,
    menu_back_23,
    menu_back_24,
    menu_back_25,
    menu_back_26,
    NULL,
    NULL,
    NULL,
    menu_back_30,
    menu_back_31,
    menu_back_32,
    menu_back_33,
    menu_back_35,
    menu_back_36,
    menu_back_37,
    menu_back_38,
    menu_back_39,
    menu_back_40,
    menu_back_41,
    menu_back_42,
    menu_back_43,
    menu_back_44,
    menu_back_45,
    menu_back_46,
#ifdef  LANGUAGE_EN
    menu_back_47,
#else
    NULL,
#endif
    menu_back_48   
};


void menu_back(){
    
    if(_Menu > 48){
        return;
    }
    if(menu_back_func[_Menu]==NULL){
        return;
    }
    menu_back_func[_Menu]();
}

