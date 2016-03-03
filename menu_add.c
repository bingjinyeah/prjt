#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"
#include "menu_conf.h"
#include "lcd.h"

Uint8 menu_add_0(){
    
    if(++_Menu0Count0>255){
        _Menu0Count0 = 0;
    }
    lcd_dis_menu_0();
    return E_OK;
}

Uint8 menu_add_2(){
    
    if(_uintCur>6){
        return E_OK;
    }
    switch(_uintCur){
        case 0:
        case 1:
        case 3:
        case 5:
            _RmRead = (_RmRead==0) ? 1:0;
            lcd_dis_menu_2();
            break;
        case 2:
            if(++_Menu2Count0>100){
                _Menu2Count0 = 30;
            }
            lcd_dis_menu_2();
            break;
        case 4:
            if(++_Menu2Count1>100){
                _Menu2Count1 = 30;
            }
            lcd_dis_menu_2();
            break;     
    }
    return E_OK;
}

Uint8 menu_add_3(){
    Uint16 res;
    
    if(_uintCur>4){
        return E_OK;
    }
    switch(_uintCur){
        case 0:
             if(++_RmRead>4){
                _RmRead = 0;
            }
            lcd_dis_menu_3();
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
            lcd_dis_menu_3();
            break;
        case 2:
            if(++_RmRead>3){
                _RmRead = 0;
            }            
            lcd_dis_menu_3();
            break; 
        case 3:
            if(++_RmRead>1){
                _RmRead = 0;
            }            
            lcd_dis_menu_3();
            break; 
    }
    return E_OK;
}

Uint8 menu_add_5(){
    
    if(_uintCur>1){
        return E_OK;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            lcd_dis_menu_5();
            break;
        case 1:
            if(++_Menu5Count0>255){
                _Menu5Count0 = 0;
            }
            lcd_dis_menu_5();
            break;     
    }
    return E_OK;
}

Uint8 menu_add_8(){
#ifdef  LANGUAGE_EN
#else
    _RmReadS = (_RmReadS==0) ? 1:0;
    lcd_dis_menu_300();
#endif
    return E_OK;
}

Uint8 menu_add_9(){
#ifndef LANGUAGE_EN
    if(_uintCur>1){
        return E_OK;
    }
    switch(_uintCur){
        case 0:
             if(++_Menu300ACount>99){
                _Menu300ACount = 1;
            }
            lcd_dis_menu_300a();
            break;
        case 1:
            _RmReadS = (_RmReadS==0) ? 1:0;
            lcd_dis_menu_300a();
            break;     
    }
#endif
    return E_OK;
}

Uint8 menu_add_10(){
#ifdef LANGUAGE_EN
#endif
    return E_OK;
}

Uint8 menu_add_11(){
#ifdef LANGUAGE_EN
#endif
    return E_OK;
}

Uint8 menu_add_12(){
    
    if(_uintCur>5){
        return E_OK;
    }
    switch(_uintCur){
        case 0:
            if(++_Menu312Count0>99){
                _Menu312Count0 = 0;
            }
            lcd_dis_menu_312();
            break;
        case 1:
            if(++_RmRead>3){
                _RmRead = 0;
            }
            lcd_dis_menu_312();
            break;
        case 2:
            if(++_Menu312Count1>100){
                _Menu312Count1 = 0;
            }
            lcd_dis_menu_312();
            break;
        case 3:
            if(++_Menu312Count2>100){
                _Menu312Count2 = 0;
            }
            lcd_dis_menu_312();
            break;
        case 4:   
        case 5:
            delayms(10);
            lcd_dis_menu_312();
            break; //in source code ,it is bra to menuloop,here dont do that
                    //in future, if it take errors, then check it 
    }
    return E_OK;
}











Uint8 (*menu_add_func[])() = {
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
    NULL,
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

Uint8 menu_add(){
    
    if(_Menu > 48){
        return E_OK;
    }
    if(menu_add_func[_Menu]==NULL){
        return E_OK;
    }
    return menu_add_func[_Menu]();
}





