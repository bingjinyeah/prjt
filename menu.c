#include "includes.h"

extern void local_thread();

void menu_idle_env(){
    Uint8 i;
    
    clr_wdt();
    Idle();
    for(i=0;i<100;i++){
        if(_ucharKey){
            return;
        }
    }
}

void menu_idle(){
    
    menu_idle_env();
    if((_Menu==33)||((_Menu==3)&&(_uintCur==1))){
        Local_Tris = 1;
        Nop();
        if(Local_Read==0){
            delayus(100);
            if(Local_Read==0){
                local_thread();
            }
        }
    }
    _ucharOpenKey = 0;
    _ucharCloseKey = 0;
    if(_Menu!=34){
        _L_OP_Count = 0;
    }else{
        L_OP_Tris = 1;
        Nop();
        if(L_OP_Read!=0){
            _L_OP_Count = 0;
        }else{
            delayus(100);
            if(L_OP_Read!=0){
                _L_OP_Count = 0;
            }else if(_L_OP_Count>=1000){
                _uintMenuCount = 0;
                _ucharMenuKey = 0;
                _ucharAddKey = 0;
                _ucharSubKey = 0;
                _ucharDownKey = 0;
                _ucharBackKey = 0;
                _ucharConfKey = 0;
                _ucharOpenKey = 0;
                _ucharCloseKey = 0;
                _RmRead = 0;
                _EmRead = 1;
                lcd_dis_menu_44();
                return;
            }
        }
    }   
    if(_VPCount<5){
        return;
    }
    _VPCount = 0;
    _SPI2_DA = false;
    get_code_vp();
    _SPI2_DA = true;
    get_code_vp();
    _L_CodeVP = circle_to_line(_CodeVP);
    if(_L_CodePreVP==_L_CodeVP){
        return;
    }
    if(_L_CodePreVP==_L_CodePPreVP){
        _L_CodePreVP = _L_CodeVP;
        return;
    }
    _L_CodePreVP = _L_CodeVP;
    _L_CodePPreVP = _L_CodePreVP;
    _uintMenuCount = 0;
    
    return;
}

void menu_loop(){
    while (1) {
        if (_ucharBackKey) {
            _uintMenuCount = 0;
            _ucharBackKey = 0;
            _ucharMenuKey = 0;
            menu_back();
            if(_System_Back){
                para_init();
                return;
            }
        }else if (_ucharConfKey) {
            _uintMenuCount = 0;
            _ucharConfKey = 0;
            _ucharMenuKey = 0;
            menu_conf();
        }else if (_ucharSubKey) {
            _uintMenuCount = 0;
            _ucharSubKey = 0;
            _ucharMenuKey = 0;
            menu_sub();
        }else if (_ucharDownKey) {
            _uintMenuCount = 0;
            _ucharDownKey = 0;
            _ucharMenuKey = 0;
            menu_down();
        }else if (_ucharAddKey) {
            _uintMenuCount = 0;
            _ucharAddKey = 0;
            _ucharMenuKey = 0;
            menu_add();
        }
        if(_uintMenuCount>12000){
            cal_limit_length();
            lcd_dis_clr_all();
            para_init();
            return;
        }
        check_remote_aux();
        if(_strAlarmFlag & _PowerDownFlag){
            process_power_down();
            return;
        }
        
        menu_idle();
    }
}

void menu_thread() {
    Uint16 res;

    _uintMenuCount = 0;
    _ucharKey = 0;
    _ucharAddKey = 0;
    _ucharSubKey = 0;
    _ucharDownKey = 0;
    _ucharBackKey = 0;
    _ucharConfKey = 0;
    _ucharIdentKey = 0;
    _ucharReadIdentKey = 0;
    _EmRead = 0;
    _RmRead = 0;
    set_t1(_conT1Time);
    lcd_dis_clr_all();
    _uintCur = 0;
    _Menu0Count0 = 0;
    eedata_read(_Code_Orde, res);
    if ((_Menu0Count0 != res)&&(res <= 255)) {
        lcd_dis_menu_0();
    } else {
        lcd_dis_menu_1();
    }
    _L_CodePreVP = _L_CodeVP;
    _L_CodePreVP2 = _L_CodeVP;
    _L_CodePPreVP = _L_CodeVP;
    menu_loop();
    
}


