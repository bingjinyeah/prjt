#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"
#include "menu_conf.h"
#include "lcd.h"

Uint8 menu_down_1(){
    
    if(++_uintCur>=4){
        _uintCur = 0;
    }
    lcd_dis_menu_1();
    return E_OK;
}

Uint8 menu_down_2(){
    
    cal_limit_length();
    if(++_uintCur>=6){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_2();
    return E_OK;
}

Uint8 menu_down_3(){
    
    if(++_uintCur>=4){
        _uintCur = 0;
    }
    _RmRead = 0;
    lcd_dis_menu_3();
    return E_OK;
}

Uint8 menu_down_4(){
    
    if(++_uintCur>=4){
        _uintCur = 0;
    }
    lcd_dis_menu_4();
    return E_OK;
}

Uint8 menu_down_5(){
    
    if(++_uintCur>=3){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_5();
    return E_OK;
}

Uint8 menu_down_8(){
    
    if(++_uintCur>=11){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_300();
    return E_OK;
}

Uint8 menu_down_9(){
#ifndef  LANGUAGE_EN
    if(++_uintCur>=2){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_300a();
#endif
    return E_OK;
}

Uint8 menu_down_10(){
#ifndef  LANGUAGE_EN
    if(++_uintCur>=2){
        _uintCur = 0;
    }
    lcd_dis_menu_310();
#endif
    return E_OK;
}

Uint8 menu_down_11(){
#ifndef  LANGUAGE_EN
    if(++_uintCur>=3){
        _uintCur = 0;
    }
    lcd_dis_menu_311();
#endif
    return E_OK;
}

Uint8 menu_down_12(){
    
    if(++_uintCur>=6){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_312();
    return E_OK;
}

Uint8 menu_down_13(){
    
    if(_RowWord2==_uintCur){
        _RowWord0 = _RowWord1;
        _RowWord1 = _RowWord2;
        if(_RowWord2>11){
            _RowWord0 = 0;
            _RowWord1 = 1;
            _RowWord2 = 2;
        }else{
            _RowWord2 = _uintCur+1;
        }
    }
    
    if(++_uintCur>=13){
        _uintCur = 0;
    }
    _EmRead = 1;
    _RmRead = 0;
    lcd_dis_menu_profibus();
    return E_OK;
}

Uint8 menu_down_14(){
    
    if(++_uintCur>=2){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_320();
    return E_OK;
}

Uint8 menu_down_15(){
#ifndef  LANGUAGE_EN
    if(++_uintCur>=2){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_321();
#endif
    return E_OK;
}

Uint8 menu_down_16(){

    if(++_uintCur>=6){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_3210();
    
    return E_OK;
}

Uint8 menu_down_17(){
#ifndef  LANGUAGE_EN
    if(++_uintCur>=3){
        _uintCur = 0;
    }
    lcd_dis_menu_322();
#endif
    return E_OK;
}

Uint8 menu_down_18(){

    if(++_uintCur>=4){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_3220();
    
    return E_OK;
}

Uint8 menu_down_18(){

    if(++_uintCur>=4){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_3221();
    
    return E_OK;
}

Uint8 menu_down_45(){
#ifndef  LANGUAGE_EN
    if(++_uintCur>=2){
        _uintCur = 0;
    }
    lcd_dis_menu_324();
#endif
    return E_OK;
}

Uint8 menu_down_21(){

    if(++_uintCur>=3){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_3230();
    
    return E_OK;
}

Uint8 menu_down_22(){
    Uint16 res;
    
    if(++_uintCur>=2){
        
        if(_Menu22_ConfCount>10){
            return E_OK;
        }
        switch(_Menu22_ConfCount-1){
            case 0:
                eedata_read(_OP_Position1,res);
                break;
            case 1:
                eedata_read(_OP_Position2,res);
                break;
            case 2:
                eedata_read(_OP_Position3,res);
                break;
            case 3:
                eedata_read(_OP_Position4,res);
                break;
            case 4:
                eedata_read(_OP_Position5,res);
                break;
            case 5:
                eedata_read(_OP_Position6,res);
                break;
            case 6:
                eedata_read(_OP_Position7,res);
                break;
            case 7:
                eedata_read(_OP_Position8,res);
                break;
            case 8:
                eedata_read(_OP_Position9,res);
                break;
            case 9:
                eedata_read(_OP_Position10,res);
                break;    
        }
        if(res<100){
            if(++_Menu22_ConfCount>10){
                _Menu22_ConfCount = 1;
            }
        }
        _EmRead = 1;
        _uintCur = 0;
    }
    lcd_dis_menu_32301();
    
    return E_OK;
}

Uint8 menu_down_23(){

    Uint16 res;
    if(++_uintCur>=2){
        
        if(_Menu23_ConfCount>10){
            return E_OK;
        }
        switch(_Menu23_ConfCount-1){
            case 0:
                eedata_read(_CL_Position1,res);
                break;
            case 1:
                eedata_read(_CL_Position2,res);
                break;
            case 2:
                eedata_read(_CL_Position3,res);
                break;
            case 3:
                eedata_read(_CL_Position4,res);
                break;
            case 4:
                eedata_read(_CL_Position5,res);
                break;
            case 5:
                eedata_read(_CL_Position6,res);
                break;
            case 6:
                eedata_read(_CL_Position7,res);
                break;
            case 7:
                eedata_read(_CL_Position8,res);
                break;
            case 8:
                eedata_read(_CL_Position9,res);
                break;
            case 9:
                eedata_read(_CL_Position10,res);
                break;    
        }
        if(res<100){
            if(++_Menu23_ConfCount>10){
                _Menu23_ConfCount = 1;
            }
        }
        _EmRead = 1;
        _uintCur = 0;
    }
    lcd_dis_menu_32302();
    
    return E_OK;
}

Uint8 menu_down_24(){

    if(++_uintCur>=3){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_330();
    
    return E_OK;
}

Uint8 menu_down_25(){

    if(++_uintCur>=3){
        _uintCur = 0;
    }
    _EmRead = 1;
    lcd_dis_menu_331();
    
    return E_OK;
}

Uint8 menu_down_26(){
    
    if(_RowWord2==_uintCur){
        _RowWord0 = _RowWord1;
        _RowWord1 = _RowWord2;
        if(_RowWord2>12){
            _RowWord0 = 0;
            _RowWord1 = 1;
            _RowWord2 = 2;
        }else{
            _RowWord2 = _uintCur+1;
        }
    }
    
    if(++_uintCur>=14){
        _uintCur = 0;
    }
    _EmRead = 1;
    _RmRead = 0;
    lcd_dis_menu_modbus();
    return E_OK;
}





