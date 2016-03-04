#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"
#include "menu_conf.h"
#include "lcd.h"

void menu_add_0(){
    
    if(++_Menu0Count0>255){
        _Menu0Count0 = 0;
    }
    lcd_dis_menu_0();
    return;
}

void menu_add_2(){
    
    if(_uintCur>6){
        return;
    }
    switch(_uintCur){
        case 0:
        case 1:
        case 3:
        case 5:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 2:
            if(++_Menu2Count0>100){
                _Menu2Count0 = 30;
            }
            break;
        case 4:
            if(++_Menu2Count1>100){
                _Menu2Count1 = 30;
            }
            break;     
    }
    lcd_dis_menu_2();
    return;
}

void menu_add_3(){
    Uint16 res;
    
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
             if(++_RmRead>4){
                _RmRead = 0;
            }
            break;
        case 1:
            eedata_read(_Card,res);
            if(res==0xaa){
                res = 1;
            }else if(res==16){
                res = 2;
            }else{
                res = 3;
            }
            if(++_RmRead>res){
                _RmRead = 0;
            }            
            break;
        case 2:
            if(++_RmRead>3){
                _RmRead = 0;
            }            
            break; 
        case 3:
            _RmRead = (_RmRead==0) ? 1:0;           
            break; 
    }
    lcd_dis_menu_3();
    return;
}

void menu_add_5(){
    
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:
            if(++_Menu5Count0>255){
                _Menu5Count0 = 0;
            }
            break;     
    }
    lcd_dis_menu_5();
    return;
}

void menu_add_8(){
#ifdef  LANGUAGE_EN
#else
    _RmReadS = (_RmReadS==0) ? 1:0;
    lcd_dis_menu_300();
#endif
    return;
}

void menu_add_9(){
#ifndef LANGUAGE_EN
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
             if(++_Menu300ACount>99){
                _Menu300ACount = 1;
            }
            break;
        case 1:
            _RmReadS = (_RmReadS==0) ? 1:0;
            break;     
    }
    lcd_dis_menu_300a();
#endif
    return;
}

void menu_add_10(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_11(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_12(){
    
    if(_uintCur>5){
        return;
    }
    switch(_uintCur){
        case 0:
            if(++_Menu312Count0>99){
                _Menu312Count0 = 0;
            }
            break;
        case 1:
            if(++_RmRead>3){
                _RmRead = 0;
            }
            break;
        case 2:
            if(++_Menu312Count1>100){
                _Menu312Count1 = 0;
            }
            break;
        case 3:
            if(++_Menu312Count2>100){
                _Menu312Count2 = 0;
            }
            break;
        case 4:   
        case 5:
            delayms(10);
            break; //in source code ,it is bra to menuloop,here dont do that
                    //in future, if it take errors, then check it 
    }
    lcd_dis_menu_312();
    return;
}

void menu_add_13(){
    
    if(_uintCur>12){
        return;
    }
    switch(_uintCur){
        case 0:
            if(++_BusCount0>126){
                _BusCount0 = 0;
            }
            break;
        case 1:
            if(++_BusCount1>255){
                _BusCount1 = 1;
            }
            break;
        case 2:
            if(++_RmRead>4){
                _RmRead = 0;
            }
            break;
        case 3:
            if(++_RmRead>2){
                _RmRead = 0;
            }
            break;
        case 4:  
            if(++_BusCount2>100){
                _BusCount2 = 0;
            }
            break;
        case 5:
             if(++_BusCount3>100){
                _BusCount3 = 0;
            }
            break; 
        case 6:
             if(++_BusCount4>99){
                _BusCount4 = 3;
            }
            break; 
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 12:
            _RmRead = (_RmRead==0x69) ? 0:0x69;
            break;
    }
    lcd_dis_menu_profibus();
    
    return;
}

void menu_add_14(){

    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:
            _RmRead1 = (_RmRead1==0) ? 1:0;
            break;     
    }
    lcd_dis_menu_320();

    return;
}

void menu_add_15(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_16(){
    
    if(_uintCur>5){
        return;
    }
    switch(_uintCur){
        case 0:
            if(++_RmRead>2){
                _RmRead = 0;
            }
            break;
        case 1:   
        case 2:
        case 3:
        case 4:
        case 5:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
    }
    lcd_dis_menu_3210();
    
    return;
}

void menu_add_17(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_18(){
    
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            if(++_Menu3220Count0>100){
                _Menu3220Count0 = 0;
            }
            break;
        case 1:   
            if(++_Menu3220Count1>100){
                _Menu3220Count1 = 0;
            }
            break;
        case 2:
            if(++_Menu3220Count2>99){
                _Menu3220Count2 = 1;
            }
            break;
        case 3:
            if(++_Menu3220Count3>99){
                _Menu3220Count3 = 1;
            }
            break;
    }
    lcd_dis_menu_3220();
    
    return;
}

void menu_add_19(){
    
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            if(++_Menu3221Count0>100){
                _Menu3221Count0 = 0;
            }
            break;
        case 1:   
            if(++_Menu3221Count1>100){
                _Menu3221Count1 = 0;
            }
            break;
        case 2:
            if(++_Menu3221Count2>99){
                _Menu3221Count2 = 1;
            }
            break;
        case 3:
            if(++_Menu3221Count3>99){
                _Menu3221Count3 = 1;
            }
            break;
    }
    lcd_dis_menu_3221();
    
    return;
}

void menu_add_20(){
    
    if(++_Menu323Count>50){
        _Menu323Count = 0;
    }
    lcd_dis_menu_323();
    return;
}

void menu_add_45(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_21(){
    
    if(++_Menu3230Count0>200){
        _Menu3230Count0 = 0;
    }
    lcd_dis_menu_3230();
    return;
}

void menu_add_22(){
    Uint16 res;
    
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            if(_Menu22_ConfCount>=10){
                _Menu32301Count1 = 100;
                break;
            }
            if(++_Menu32301Count1<=100){
                break;
            }
            switch(_Menu22_ConfCount-1){
                case 0:
                    res = 0;
                    break;
                case 1:
                    eedata_read(_OP_Position1,res);
                    break;
                case 2:
                    eedata_read(_OP_Position2,res);
                    break;
                case 3:
                    eedata_read(_OP_Position3,res);
                    break;
                case 4:
                    eedata_read(_OP_Position4,res);
                    break;
                case 5:
                    eedata_read(_OP_Position5,res);
                    break;
                case 6:
                    eedata_read(_OP_Position6,res);
                    break;
                case 7:
                    eedata_read(_OP_Position7,res);
                    break;
                case 8:
                    eedata_read(_OP_Position8,res);
                    break;
            }
            _Menu32301Count1 = ++res;
            break;
        case 1:   
            if(++_Menu32301Count2>100){
                _Menu32301Count2 = 0;
            }
            break;
    }
    lcd_dis_menu_32301();
    
    return;
}

void menu_add_23(){
    Uint16 res;
    
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            if(_Menu23_ConfCount>=10){
                _Menu32302Count1 = 0;
                break;
            }
            
            switch(_Menu23_ConfCount-1){
                case 0:
                    res = 100;
                    break;
                case 1:
                    eedata_read(_CL_Position1,res);
                    break;
                case 2:
                    eedata_read(_CL_Position2,res);
                    break;
                case 3:
                    eedata_read(_CL_Position3,res);
                    break;
                case 4:
                    eedata_read(_CL_Position4,res);
                    break;
                case 5:
                    eedata_read(_CL_Position5,res);
                    break;
                case 6:
                    eedata_read(_CL_Position6,res);
                    break;
                case 7:
                    eedata_read(_CL_Position7,res);
                    break;
                case 8:
                    eedata_read(_CL_Position8,res);
                    break;
            }
            if(++_Menu32302Count1>=res){
                _Menu32302Count1 = 0;
            }
            break;
        case 1:   
            if(++_Menu32302Count2>100){
                _Menu32302Count2 = 0;
            }
            break;
    }
    lcd_dis_menu_32302();
    
    return;
}

void menu_add_24(){
    Uint16 res;
    
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:   
            if(++_Menu330Count>800){
                eedata_read(_Pos_BackL,res);
                _Menu330Count = res;
            }
            _VPDA = _Menu330Count;
            break;
        case 2:
            if(++_Menu330Count>2500){
                eedata_read(_Pos_BackH,res);
                _Menu330Count = res;
            }
            _VPDA = _Menu330Count;
            break;
    }
    lcd_dis_menu_330();
    
    return;
}

void menu_add_25(){
    Uint16 res;
    
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:   
            if(++_Menu331Count>800){
                eedata_read(_Tor_BackL,res);
                _Menu331Count = res;
            }
            _NJDA = _Menu331Count;
            break;
        case 2:
            if(++_Menu331Count>2500){
                eedata_read(_Tor_BackH,res);
                _Menu331Count = res;
            }
            _NJDA = _Menu331Count;
            break;
    }
    lcd_dis_menu_331();
    
    return;
}

void menu_add_26(){
    
    if(_uintCur>13){
        return;
    }
    switch(_uintCur){
        case 0:
            if(++_BusCount0>247){
                _BusCount0 = 0;
            }
            break;
        case 1:
            if(++_RmRead>7){
                _RmRead = 0;
            }
            break;
        case 2:
            if(++_RmRead>2){
                _RmRead = 0;
            }
            break;
        case 3:
            if(++_BusCount1>255){
                _BusCount1 = 1;
            }
            break;
        case 4:  
            if(++_RmRead>4){
                _RmRead = 0;
            }
            break;
        case 5:
            if(++_RmRead>2){
                _RmRead = 0;
            }
            break; 
        case 6:
            if(++_BusCount2>100){
                _BusCount2 = 0;
            }
            break; 
        case 7:
            if(++_BusCount3>100){
                _BusCount3 = 0;
            }
            break;
        case 8:
            if(++_BusCount4>99){
                _BusCount4 = 3;
            }
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
    }
    lcd_dis_menu_modbus();
    
    return;
}

void menu_add_33(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_35(){
    
    if(++_BusCount5>100){
        _BusCount5 = 0;
    }
    lcd_dis_menu_posals();
    return;
}

void menu_add_36(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_37(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_38(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_39(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_40(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_41(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_42(){
#ifdef LANGUAGE_EN
#endif
    return;
}
void menu_add_43(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_add_44(){
    
    _RmRead = (_RmRead==0) ? 1:0;
    lcd_dis_menu_44();
    return;
}

void menu_add_46(){
    Uint16 res;
    
    eedata_read(_Card,res);
    if(res==8){
        res = 126;
    }else{
        res = 247;
    }
    if(++_BusCount6>res){
        _BusCount6 = 0;
    }   
    lcd_dis_menu_redudant();
    
    return;
}

void menu_add_48(){
    
    _RmRead = (_RmRead==0) ? 1:0;
    lcd_dis_menu_300b();
    return;
}














void (*menu_add_func[])() = {
    NULL,
    menu_add_0,
    NULL,
    menu_add_2,
    menu_add_3,
    NULL,
    menu_add_5,
    NULL,
    NULL,
    menu_add_8,
    menu_add_9,
    menu_add_10,
    menu_add_11,
    menu_add_12,
    menu_add_13,
    menu_add_14,
    menu_add_15,
    menu_add_16,
    menu_add_17,
    menu_add_18,
    menu_add_19,
    menu_add_20,
    menu_add_21,
    menu_add_22,
    menu_add_23,
    menu_add_24,
    menu_add_25,
    menu_add_26,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    menu_add_33,
    menu_add_35,
    menu_add_36,
    menu_add_37,
    menu_add_38,
    menu_add_39,
    menu_add_40,
    menu_add_41,
    menu_add_42,
    menu_add_43,
    menu_add_44,
    menu_add_45,
    menu_add_46,
    NULL,
    menu_add_48   
};

void menu_add(){
    
    if(_Menu > 48){
        return;
    }
    if(menu_add_func[_Menu]==NULL){
        return;
    }
    menu_add_func[_Menu]();
}
