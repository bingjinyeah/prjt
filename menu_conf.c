#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"
#include "menu.h"
#include "lcd.h"
#include "relay.h"
#include "code.h"


void (*lcd_dis_saved[])() = {
    lcd_dis_saved00,
    lcd_dis_saved0,
    lcd_dis_saved1,
#ifndef LANGUAGE_EN
    lcd_dis_saved2,
    lcd_dis_saved3,
#endif
    lcd_dis_saved4,
#ifndef LANGUAGE_EN
    lcd_dis_saved5,
    lcd_dis_saved6,
    lcd_dis_saved7,
    lcd_dis_saved8,
    lcd_dis_saved9,
    lcd_dis_saved10,
    lcd_dis_saved11,
    lcd_dis_saved12,
 #endif   
    lcd_dis_saved13,
#ifndef LANGUAGE_EN
    lcd_dis_saved14,
    lcd_dis_saved15,
    lcd_dis_saved16,
    lcd_dis_saved17,
#endif
    lcd_dis_saved18
};

void (*lcd_dis_menu[])() = {
    lcd_dis_menu_0,
    lcd_dis_menu_1,
    lcd_dis_menu_2,
    lcd_dis_menu_3,
    lcd_dis_menu_4,
    lcd_dis_menu_5,
    lcd_dis_menu_300,
    lcd_dis_menu_300a,
    lcd_dis_menu_300b,
    lcd_dis_menu_310,
    lcd_dis_menu_311,
    lcd_dis_menu_312,
    lcd_dis_menu_profibus,
    lcd_dis_menu_modbus,
    lcd_dis_menu_posals,
    lcd_dis_menu_aux1,
    lcd_dis_menu_aux2,
    lcd_dis_menu_aux3,
    lcd_dis_menu_aux4,
    lcd_dis_menu_aux5,
    lcd_dis_menu_aux6,
    lcd_dis_menu_aux7,
    lcd_dis_menu_aux8,
    lcd_dis_menu_redudant,
    lcd_dis_menu_320,
    lcd_dis_menu_321,
    lcd_dis_menu_3210,
    lcd_dis_menu_322,
    lcd_dis_menu_3220,
    lcd_dis_menu_3221,
    lcd_dis_menu_323,
    lcd_dis_menu_3230,
    lcd_dis_menu_32301,
    lcd_dis_menu_32302,
    lcd_dis_menu_324,
    lcd_dis_menu_330,
    lcd_dis_menu_331,
    lcd_dis_menu_40,
    lcd_dis_menu_41,
    lcd_dis_menu_43,
    lcd_dis_menu_44,
    lcd_dis_menu_50    
};

void menu_conf_exit(Uint8 saved, Uint16 menu){

        lcd_dis_saved[saved]();
        delayms(200);
        lcd_dis_menu[menu]();
        delayms(300);
        lcd_dis_saved[saved]();
        delayms(200);
        lcd_dis_menu[menu]();
}

void menu_conf_0(){
    Uint16 res;
    
    eedata_read(_Code_Orde, res);
    if (_Menu0Count0==res){
        lcd_dis_menu_1();
        return;
    }
    menu_conf_exit(SAVED13,MENU_0);

    return;
}

void menu_conf_1(){
    
    switch(_uintCur){
        case 0: 
            _EmRead = 1;
            lcd_dis_menu_2();
            break;
        case 1: 
            _uintCur = 0;
            _RmRead = 0;
            _RmReadS = 0;
            lcd_dis_menu_3();
            break;
        case 2: 
            _uintCur = 0;
            lcd_dis_menu_4();
            break;
        case 3: 
            _uintCur = 0;
            _EmRead = 1;
            lcd_dis_menu_5();
            break;       
    }
    return;
}

void menu_conf_2(){
    Uint16  res,res1;
    Uint16 opl,cll,sub;
    Uint32 mul;
    
    switch(_uintCur){
    case 0: 
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_CL_Dir,0xff);
        case 1:
            eedata_write(_CL_Dir,0x69);
        }
        menu_conf_exit(SAVED,MENU_2);
        break;
    case 1: 
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            if(_SetOPLimitFlag==0x69){
                eedata_read(_L_Zero,res);
                eedata_read(_OP_Limit,res1);
                if(res1!=_CodeVP){
                    cal_zero(_CodeVP,res1);
                    opl = circle_to_line(res1);
                    cll = circle_to_line(_CodeVP);
                    sub = opl - cll;
                    if(sub > (65535-512)){
                        eedata_write(_L_Zero,res);
                        lcd_dis_clr_alarm();
                        lcd_dis_alarm_lengtherror();
                        delayms(400);
                        lcd_dis_clr_alarm();
                        delayms(200);
                        lcd_dis_alarm_lengtherror();
                        delayms(400);
                        lcd_dis_clr_alarm();
                        lcd_dis_menu_2();
                        return;
                    }else{
                        eedata_write(_Limit_Length,sub);
                        eedata_write(_L_OP_Limit,opl);
                        eedata_write(_L_CL_Limit,cll);
                        eedata_read(_POSMIN,res);
                        mul = res * sub;
                        res = mul/100;
                        res += cll;
                        eedata_write(_POSMIN_Code,res);
                        eedata_read(_POSMAX,res);
                        mul = res * sub;
                        res = mul/100;
                        res += cll;
                        eedata_write(_POSMAX_Code,res);
                    }  
                }else{
                    lcd_dis_clr_alarm();
                    lcd_dis_alarm_cllimitover();
                    delayms(400);
                    lcd_dis_clr_alarm();
                    delayms(200);
                    lcd_dis_alarm_cllimitover();
                    delayms(400);
                    lcd_dis_clr_alarm();
                    return;
                }
            }
            eedata_write(_CL_Limit,_CodeVP);
            _SetCLLimitFlag = 0x69;
            _strAlarmFlag |= _CSFlag;
            _DP_IDATA1 |= BIT1;
            _strAlarmFlag &= ~_OSFlag;
            _DP_IDATA1 &= ~BIT2;
            LED_G_Tris = 0;
            LED_R_Tris = 0;
            LED_G_Write = 1;
            LED_R_Write = 0;
            relay_position_judge();
            rush_relays();
            menu_conf_exit(SAVED,MENU_2);                
            break;
        case 1:
            if(_SetCLLimitFlag==0x69){
                eedata_read(_L_Zero,res);
                eedata_read(_CL_Limit,res1);
                if(res1!=_CodeVP){
                    cal_zero(res1,_CodeVP);
                    cll = circle_to_line(res1);
                    opl = circle_to_line(_CodeVP);
                    sub = opl - cll;
                    if(sub > (65535-512)){
                        eedata_write(_L_Zero,res);
                        lcd_dis_clr_alarm();
                        lcd_dis_alarm_lengtherror();
                        delayms(400);
                        lcd_dis_clr_alarm();
                        delayms(200);
                        lcd_dis_alarm_lengtherror();
                        delayms(400);
                        lcd_dis_clr_alarm();
                        lcd_dis_menu_2();
                        return;
                    }else{
                        eedata_write(_Limit_Length,sub);
                        eedata_write(_L_OP_Limit,opl);
                        eedata_write(_L_CL_Limit,cll);
                        eedata_read(_POSMIN,res);
                        mul = res * sub;
                        res = mul/100;
                        res += cll;
                        eedata_write(_POSMIN_Code,res);
                        eedata_read(_POSMAX,res);
                        mul = res * sub;
                        res = mul/100;
                        res += cll;
                        eedata_write(_POSMAX_Code,res);
                    }  
                }else{
                    lcd_dis_clr_alarm();
                    lcd_dis_alarm_oplimitover();
                    delayms(400);
                    lcd_dis_clr_alarm();
                    delayms(200);
                    lcd_dis_alarm_oplimitover();
                    delayms(400);
                    lcd_dis_clr_alarm();
                    return;
                }
            }
            eedata_write(_OP_Limit,_CodeVP);
            _SetOPLimitFlag = 0x69;
            _strAlarmFlag |= _OSFlag;
            _DP_IDATA1 |= BIT2;
            _strAlarmFlag &= ~_CSFlag;
            _DP_IDATA1 &= ~BIT1;
            LED_G_Tris = 0;
            LED_R_Tris = 0;
            LED_G_Write = 0;
            LED_R_Write = 1;
            relay_position_judge();
            rush_relays();
            menu_conf_exit(SAVED,MENU_2);                
            break;
        }
        break;
    case 2: 
        eedata_write(_CL_TorProtect,_Menu2Count0);
        _strAlarmFlag &= ~_CTFlag;
        _DP_DIAGR0 &= BIT3;
        menu_conf_exit(SAVED,MENU_2);
        break;
    case 3: 
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
            case 0:
                eedata_write(_CLDir_Protect,0xff);
                break;
            case 1:
                eedata_write(_CLDir_Protect,0x69);
                break;
        }
        menu_conf_exit(SAVED,MENU_2);
        break; 
    case 4: 
        eedata_write(_OP_TorProtect,_Menu2Count1);
        _strAlarmFlag &= ~_OTFlag;
        _DP_DIAGR0 &= BIT4;
        menu_conf_exit(SAVED,MENU_2);
        break;
    case 5: 
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
            case 0:
                eedata_write(_OPDir_Protect,0xff);
                break;
            case 1:
                eedata_write(_OPDir_Protect,0x69);
                break;
        }
        menu_conf_exit(SAVED,MENU_2);
        break; 
    }
    return;
}

void menu_conf_3(){
    
    Uint16 res;
    switch(_uintCur){
    case 0: 
        if(_RmRead==4){
            _EmRead = 1;
            lcd_dis_menu_300b();
        }else{
            _Menu300Atemp = _RmRead;
            _EmRead = 1;
            if(_RmRead>3){
                break;
            }
            get_eedata_snfun(_RmRead,&res);
            /*
            switch(_RmRead){
            case 0:
                eedata_read(_S1_Fun,res);
                break;
            case 1:
                eedata_read(_S2_Fun,res);
                break;
            case 2:
                eedata_read(_S3_Fun,res);
                break;
            case 3:
                eedata_read(_S4_Fun,res);
                break;
            }*/
            _uintCur = (res > 10)? 0:res;
            lcd_dis_menu_300();
        }
        break;
    case 1:         
        switch(_RmRead){
        case 0:
            eedata_read(_LocalCtrl,res);
            _uintCur = (res==0x69) ? 0:1;
            lcd_dis_menu_310();
            break;
        case 1:
            eedata_read(_TwoLinesCtrl,res);
            _uintCur = (res==0x69) ? 0:(((res==0x96) ? 1:2));
            lcd_dis_menu_311();
            break;
        case 2:
            _uintCur = 0;
            _EmRead = 1;
            lcd_dis_menu_312();
            break;
        }
        if(_RmRead>2){
            eedata_read(_Card,res);
            _uintCur = 0;
            _RowWord0 = 0;
            _RowWord1 = 1;
            _RowWord2 = 2;
            _EmRead = 1;
            _BusCount0 = 0;
            _BusCount2 = 0;
            _BusCount3 = 0;
            _BusCount4 = 3;
            _BusCount5 = 0;
            if(res==8){
                _BusCount1 = 1;
                lcd_dis_menu_profibus();
            }else if(res==2){
                lcd_dis_menu_modbus();
            }
        }
        break;
    case 2: 
        if(_RmRead>3){
            break;
        }
        switch(_RmRead){
        case 0:
            _uintCur = 0;
            _EmRead = 1;
            lcd_dis_menu_320();
            break;
        case 1:
            eedata_read(_AUXMSK,res);
            if(res & BIT7){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_321();
            break;
        case 2:
            eedata_read(_Interim_Ctrl,res);
            _uintCur = (res==0x69) ? 2:(((res==0x96) ? 1:0));
            lcd_dis_menu_322();
            break;
        case 3:
            _EmRead = 1;
            lcd_dis_menu_323();
            break;
        case 4:
            eedata_read(_VarSpeedEnable,res);
            _uintCur = (res==0x69) ? 0:1;
            lcd_dis_menu_324();
            break;
        }
        break;
    case 3: 
        if(_FB_Temp==0xffff){
            break;
        }
        _uintCur = 0;
        _EmRead = 1;
        if(_RmRead==0){
            lcd_dis_menu_330();
        }else{
            lcd_dis_menu_331();
        }
        break;       
    }
    return;
}

void menu_conf_4(){
    
    switch(_uintCur){
        case 0: 
            _uintCur = 0;
            lcd_dis_menu_40();
            break;
        case 1: 
            _uintCur = 0;
            lcd_dis_menu_41();
            break;
        case 2: 
            _uintCur = 0;
            _EmRead = 1;
            lcd_dis_menu_43();
            break;
#ifdef LANGUAGE_EN
        case 3: lcd_dis_menu_46();break;
#endif
    }
    return;
}

void menu_conf_5(){
    
    switch(_uintCur){
        case 0: 
            if(_RmRead){
                eedata_write(_InverseDisEnable,0x69);
            }else{
                eedata_write(_InverseDisEnable,0xff);
            }
            RESETB_Tris = 0;
            Nop();
            RESETB_Write = 0;
            delayus(500);
            RESETB_Write = 1;
            dis_init();
            menu_conf_exit(SAVED15,MENU_5);
            break;
        case 1: 
            eedata_write(_Code_Orde,_Menu5Count0);
            menu_conf_exit(SAVED15,MENU_5);
            break;
        case 2: 
            _uintCur = 0;
            lcd_dis_menu_50();
            break;
    }
    return;
}

void menu_conf_8_exit1(){
    
#ifdef  LANGUAGE_EN
    
#else
    _EmRead = 1;
    _uintCur = 0;
    lcd_dis_menu_300a();
#endif
}

void menu_conf_8_exit0(){

    if(_uintCur==10){
        menu_conf_8_exit1();
        return;
    }
    menu_conf_exit(SAVED1,MENU_300);
}
//relay output set
void menu_conf_8(){
    Uint16 res;
    
    if(_uintCur>10){
        return;
    }
    if(_uintCur==0){
        res = 0xff;
    }
#ifdef  LANGUAGE_EN
    
#endif
    else{
        res = _uintCur;
    }    
    switch(_Menu300Atemp){
        case 0: 
            eedata_write(_Sn_Fun[0],res);
            if(_RmReadS!=0){
                eedata_write(_Sn_Status[0],0x69);
            }else{
                eedata_write(_Sn_Status[0],0xff);
            }
            menu_conf_8_exit0();
            break;
        case 1: 
            eedata_write(_Sn_Fun[1],res);
            if(_RmReadS!=0){
                eedata_write(_Sn_Status[1],0x69);
            }else{
                eedata_write(_Sn_Status[1],0xff);
            }
            menu_conf_8_exit0();
            break;
        case 2: 
            eedata_write(_Sn_Fun[2],res);
            if(_RmReadS!=0){
                eedata_write(_Sn_Status[2],0x69);
            }else{
                eedata_write(_Sn_Status[2],0xff);
            }
            menu_conf_8_exit0();
            break;
        case 3: 
            eedata_write(_Sn_Fun[3],res);
            if(_RmReadS!=0){
                eedata_write(_Sn_Status[3],0x69);
            }else{
                eedata_write(_Sn_Status[3],0xff);
            }
            menu_conf_8_exit0();
            break;
    }
    return;
}

void menu_conf_9(){

#ifdef  LANGUAGE_EN
 
#endif
    return;
}
//local control menu
void menu_conf_10(){
    
    switch(_uintCur){
    case 0:
        eedata_write(_LocalCtrl,0x69);
        menu_conf_exit(SAVED17,MENU_310);
        break;
    case 1:
        eedata_write(_LocalCtrl,0xff);
        menu_conf_exit(SAVED18,MENU_310);
        break;
    }
    return;
}
//two line control control menu
void menu_conf_11(){
    
    switch(_uintCur){
    case 0:
        eedata_write(_TwoLinesCtrl,0x69);
        menu_conf_exit(SAVED4,MENU_311);
        break;
    case 1:
        eedata_write(_TwoLinesCtrl,0x96);
        menu_conf_exit(SAVED5,MENU_311); 
        break;
    case 2:
        eedata_write(_TwoLinesCtrl,0xff);  
        break;
    }
    return;
}

//proportion control menu
void menu_conf_12(){
    
    switch(_uintCur){
    case 0:
        eedata_write(_IC_Dbd,_Menu312Count0);
        menu_conf_exit(SAVED1,MENU_312);
        break;
    case 1:
        if(_RmRead>3){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_POSALS,0x05);
            break;
        case 1:
            eedata_write(_POSALS,0x01);
            break;
        case 2:
            eedata_write(_POSALS,0x03);
            break;
        case 3:
            eedata_write(_POSALS,0x07);
            _uintCur = 0;
            _RmRead = 0;
            _BusCount5 = 0;
            _EmRead = 1;
            lcd_dis_menu_posals();
            return; 
        }
        menu_conf_exit(SAVED1,MENU_312);
        break;
    case 2:
        eedata_write(_IC_Low_VP,_Menu312Count1);
        menu_conf_exit(SAVED1,MENU_312);
        break;
    case 3:
        eedata_write(_IC_High_VP,_Menu312Count2);
        menu_conf_exit(SAVED1,MENU_312);
        break;
    case 4:
        eedata_write(_IC_Low,_IC[10]);
        menu_conf_exit(SAVED1,MENU_312);
        break;
    case 5:
        eedata_write(_IC_High,_IC[10]);
        menu_conf_exit(SAVED1,MENU_312);
        break;
    }
    return;
}

//profibus control menu
void menu_conf_13(){
    
    Uint16 res,res1;
    Uint32 mul;
    switch(_uintCur){
    case 0:
        eedata_write(_DP_Adress,_BusCount0);
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 1:
        eedata_write(_DPSLTO,_BusCount1);
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 2:
        if(_RmRead>4){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_POSALS,0x00);
            break;
        case 1:
            eedata_write(_POSALS,0x01);
            break;
        case 2:
            eedata_write(_POSALS,0x03);
            break;
        case 3:
            eedata_write(_POSALS,0x05);
            break;
        case 4:
            eedata_write(_POSALS,0x07);
            _uintCur = 0;
            _RmRead = 0;
            _BusCount5 = 0;
            _EmRead = 1;
            lcd_dis_menu_posals();
            return; 
        }
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 3:
        if(_RmRead>2){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_Action,0x69);
            break;
        case 1:
            eedata_write(_ESD_Action,0x96);
            break;
        case 2:
            eedata_write(_ESD_Action,0xff);
            break;
        }
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 4:
        eedata_write(_POSMIN,_BusCount2);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount2;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMIN_Code,res1);
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 5:
        eedata_write(_POSMAX,_BusCount3);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount3;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMAX_Code,res1);
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 6:
        eedata_write(_IC_Dbd,_BusCount4);
        menu_conf_exit(SAVED1, MENU_PROFIBUS);
        break;
    case 7:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT4;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT0){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux1();
            break;
        case 1:
            res |= BIT4;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT0){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux5();
            break;
        }
        break; 
    case 8:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT5;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT1){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux2();
            break;
        case 1:
            res |= BIT5;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT1){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux6();
            break;
        }
        break; 
    case 9:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT6;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT2){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux3();
            break;
        case 1:
            res |= BIT6;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT2){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux7();
            break;
        }
        break; 
    case 10:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT7;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT3){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux4();
            break;
        case 1:
            res |= BIT7;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT3){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux8();
            break;
        }
        break;
    case 11:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_Redundancy,0x00);
            eedata_write(_DP_Adress2,0xff);
            _EmRead = 1;
            menu_conf_exit(SAVED1, MENU_PROFIBUS);
            break;
        case 1:
            eedata_write(_Redundancy,0x69);
            _EmRead = 1;
            lcd_dis_menu_redudant();
            break;
        }
        break; 
    case 12:
        eedata_write(_DPCtrl,_RmRead);
        break;
    }
    return;
}

//lock set for remote and local
void menu_conf_14(){
    
    switch(_uintCur){
    case 0:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_Local_Lock,0xff);
            break;
        case 1:
            eedata_write(_Local_Lock,0x69);
            break;
        }
        menu_conf_exit(SAVED7, MENU_320);
        break;
    case 1:
        if(_RmRead1>1){
            break;
        }
        switch(_RmRead1){
        case 0:
            eedata_write(_Remote_Lock,0xff);
            break;
        case 1:
            eedata_write(_Remote_Lock,0x69);
            break;
        }
        menu_conf_exit(SAVED7, MENU_320);
        break;
    }
    return;
}

//esd control set
void menu_conf_15(){
    
    Uint16 res;
    if(_uintCur >1){
        return;
    }
    eedata_read(_AUXMSK,res);
    switch(_uintCur){
    case 0:
        res |= BIT7;
        eedata_write(_AUXMSK,res);
        _EmRead = 1;
        lcd_dis_menu_3210();
        break;
    case 1:
        res &= ~BIT7;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED5, MENU_321);
        break;
    }
    return;
}

//esd forward set
void menu_conf_16(){
    
    Uint16 res;
    switch(_uintCur){
    case 0:
        if(_RmRead>2){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_Action,0x69);
            break;
        case 1:
            eedata_write(_Local_Lock,0x96);
            break;
        case 2:
            eedata_write(_Local_Lock,0xff);
            break;
        }
        menu_conf_exit(SAVED8, MENU_3210);
        break;
    case 1:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res |= BIT3;
            eedata_write(_AUXMSK,res);
            break;
        case 1:
            res &= ~BIT3;
            eedata_write(_AUXMSK,res);
            break;
        }
        menu_conf_exit(SAVED8, MENU_3210);
        break;
    case 2:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_ExceedHot,0xff);
            break;
        case 1:
            eedata_write(_ESD_ExceedHot,0x69);
            break;
        }
        menu_conf_exit(SAVED8, MENU_3210);
        break;    
    case 3:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_ExceedSp,0xff);
            break;
        case 1:
            eedata_write(_ESD_ExceedSp,0x69);
            break;
        }
        menu_conf_exit(SAVED8, MENU_3210);
        break; 
    case 4:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_ExceedLock,0xff);
            break;
        case 1:
            eedata_write(_ESD_ExceedLock,0x69);
            break;
        }
        menu_conf_exit(SAVED8, MENU_3210);
        break;     
    case 5:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_ExceedTime,0xff);
            break;
        case 1:
            eedata_write(_ESD_ExceedTime,0x69);
            break;
        }
        menu_conf_exit(SAVED8, MENU_3210);
        break;        
    }
    return;
}

void menu_conf_17(){

    if(_uintCur > 2){
        return;
    }
    switch(_uintCur){
    case 0:
        eedata_write(_Interim_Ctrl,0xff);
        menu_conf_exit(SAVED4, MENU_322);
        break;
    case 1:
        eedata_write(_Interim_Ctrl,0x96);
        _uintCur = 0;
        _EmRead = 1;
        lcd_dis_menu_3220();
        break;
    case 2:
        eedata_write(_Interim_Ctrl,0x69);
        _uintCur = 0;
        _EmRead = 1;
        lcd_dis_menu_3221();
        break;
    }
    return;
}

void menu_conf_18(){

    if(_uintCur > 3){
        return;
    }
    switch(_uintCur){
    case 0:
        eedata_write(_Start_Pos,_Menu3220Count0);
        break;
    case 1:
        eedata_write(_Stop_Pos,_Menu3220Count1);
        break;
    case 2:
        eedata_write(_MoveTime,_Menu3220Count2);
        break;
    case 3:
        eedata_write(_StopTime,_Menu3220Count3);
        break;
    }
    menu_conf_exit(SAVED10, MENU_3220);
    return;
}

void menu_conf_19(){

    if(_uintCur > 3){
        return;
    }
    switch(_uintCur){
    case 0:
        eedata_write(_Start_Pos,_Menu3221Count0);
        break;
    case 1:
        eedata_write(_Stop_Pos,_Menu3221Count1);
        break;
    case 2:
        eedata_write(_MoveTime,_Menu3221Count2);
        break;
    case 3:
        eedata_write(_StopTime,_Menu3221Count3);
        break;
    }
    menu_conf_exit(SAVED10, MENU_3221);
    return;
}

void menu_conf_20(){
    
    eedata_write(_POSMIT,_Menu323Count);
    menu_conf_exit(SAVED5, MENU_323);   
    return;
}

void menu_conf_21(){

    if(_uintCur > 2){
        return;
    }
    switch(_uintCur){
    case 0:
        _EmRead = 1;
        _Menu22_ConfCount = 1;
        _uintCur = 0;
        lcd_dis_menu_32301();
        break;
    case 1:
        _EmRead = 1;
        _Menu23_ConfCount = 1;
        _uintCur = 0;
        lcd_dis_menu_32302();
        break;
    case 2:
        eedata_write(_ESD_Speed,_Menu3230Count0);
        menu_conf_exit(SAVED1, MENU_3230); 
        break;
    }
    return;
}

void menu_conf_22(){

    if(_Menu22_ConfCount-- > 10){
        return;
    }
    switch(_Menu22_ConfCount){
    case 0:
        if(_uintCur){
            eedata_write(_OP_Speed[0],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[0],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 1:
        if(_uintCur){
            eedata_write(_OP_Speed[1],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[1],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 2:
        if(_uintCur){
            eedata_write(_OP_Speed[2],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[2],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 3:
        if(_uintCur){
            eedata_write(_OP_Speed[3],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[3],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 4:
        if(_uintCur){
            eedata_write(_OP_Speed[4],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[4],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 5:
        if(_uintCur){
            eedata_write(_OP_Speed[5],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[5],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 6:
        if(_uintCur){
            eedata_write(_OP_Speed[6],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[6],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 7:
        if(_uintCur){
            eedata_write(_OP_Speed[7],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[7],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 8:
        if(_uintCur){
            eedata_write(_OP_Speed[8],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[8],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    case 9:
        if(_uintCur){
            eedata_write(_OP_Speed[9],_Menu32301Count2);
            menu_conf_exit(SAVED6, MENU_32301);
        }else{
            eedata_write(_OP_Position[9],_Menu32301Count1);
            menu_conf_exit(SAVED4, MENU_32301);
        }
        break;
    }
    return;
}

void menu_conf_23(){

    if(_Menu23_ConfCount-- > 10){
        return;
    }
    switch(_Menu23_ConfCount){
    case 0:
        if(_uintCur){
            eedata_write(_CL_Speed[0],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[0],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 1:
        if(_uintCur){
            eedata_write(_CL_Speed[1],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[1],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 2:
        if(_uintCur){
            eedata_write(_CL_Speed[2],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[2],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 3:
        if(_uintCur){
            eedata_write(_CL_Speed[3],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[3],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 4:
        if(_uintCur){
            eedata_write(_CL_Speed[4],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[4],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 5:
        if(_uintCur){
            eedata_write(_CL_Speed[5],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[5],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 6:
        if(_uintCur){
            eedata_write(_CL_Speed[6],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[6],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 7:
        if(_uintCur){
            eedata_write(_CL_Speed[7],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[7],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 8:
        if(_uintCur){
            eedata_write(_CL_Speed[8],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[8],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    case 9:
        if(_uintCur){
            eedata_write(_CL_Speed[9],_Menu32302Count2);
            menu_conf_exit(SAVED6, MENU_32302);
        }else{
            eedata_write(_CL_Position[9],_Menu32302Count1);
            menu_conf_exit(SAVED4, MENU_32302);
        }
        break;
    }
    return;
}

void menu_conf_24(){
    
    switch(_uintCur){
    case 0:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_Pos_BackLogic,0xff);
            break;
        case 1:
            eedata_write(_Pos_BackLogic,0x69);
            break;
        }
        menu_conf_exit(SAVED14, MENU_330);
        break;
    case 1:
        eedata_write(_Pos_BackL,_Menu330Count);
        menu_conf_exit(SAVED14, MENU_330);
        break;
    case 2:
        eedata_write(_Pos_BackH,_Menu330Count);
        menu_conf_exit(SAVED14, MENU_330);
        break;    
    }
    return;
}


void menu_conf_25(){
    
    switch(_uintCur){
    case 0:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_Tor_BackLogic,0x69);
            break;
        case 1:
            eedata_write(_Tor_BackLogic,0xff);
            break;
        }
        menu_conf_exit(SAVED14, MENU_331);
        break;
    case 1:
        eedata_write(_Tor_BackL,_Menu331Count);
        menu_conf_exit(SAVED14, MENU_331);
        break;
    case 2:
        eedata_write(_Tor_BackH,_Menu331Count);
        menu_conf_exit(SAVED14, MENU_331);
        break;    
    }
    return;
}

void menu_conf_26(){
    Uint16 res,res1;
    Uint32 mul;
    
    switch(_uintCur){
    case 0:
        eedata_write(_DP_Adress,_BusCount0);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;   
    case 1:
        if(_RmRead>7){
            break;
        }
        eedata_write(_BANDRT,_RmRead);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 2:
        if(_RmRead>2){
            break;
        }
        eedata_write(_PARITY,_RmRead);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 3:
        eedata_write(_MODSLTO,_BusCount1);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 4:
        if(_RmRead>4){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_POSALS,0x00);
            break;
        case 1:
            eedata_write(_POSALS,0x01);
            break;
        case 2:
            eedata_write(_POSALS,0x03);
            break;
        case 3:
            eedata_write(_POSALS,0x05);
            break;
        case 4:
            eedata_write(_POSALS,0x07);
            _uintCur = 0;
            _RmRead = 0;
            _BusCount5 = 0;
            _EmRead = 1;
            lcd_dis_menu_posals();
            return;
        }
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 5:
        if(_RmRead>2){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_ESD_Action,0x69);
            break;
        case 1:
            eedata_write(_ESD_Action,0x96);
            break;
        case 2:
            eedata_write(_ESD_Action,0xff);
            break;
        }
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 6:
        eedata_write(_POSMIN,_BusCount2);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount2;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMIN_Code,res1);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 7:
        eedata_write(_POSMAX,_BusCount3);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount3;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMAX_Code,res1);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 8:
        eedata_write(_IC_Dbd,_BusCount4);
        menu_conf_exit(SAVED1, MENU_MODBUS);
        break;
    case 9:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT4;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT0){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux1();
            break;
        case 1:
            res |= BIT4;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT0){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux5();
            break;
        }
        break;
    case 10:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT5;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT1){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux2();
            break;
        case 1:
            res |= BIT5;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT1){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux6();
            break;
        }
        break;
    case 11:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT6;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT2){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux3();
            break;
        case 1:
            res |= BIT6;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT2){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux7();
            break;
        }
        break;
    case 12:
        if(_RmRead>1){
            break;
        }
        eedata_read(_AUXMSK,res);
        switch(_RmRead){
        case 0:
            res &= ~BIT7;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT3){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux4();
            break;
        case 1:
            res |= BIT7;
            eedata_write(_AUXMSK,res);
            _EmRead = 1;
            eedata_read(_AUXMSK,res);
            if(res & BIT3){
                _uintCur = 0;
            }else{
                _uintCur = 1;
            }
            lcd_dis_menu_aux8();
            break;
        }
        break;
    case 13:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_Redundancy,0x00);
            eedata_write(_DP_Adress2,0xff);
            _EmRead = 1;
            menu_conf_exit(SAVED1, MENU_MODBUS);
            break;
        case 1:
            eedata_write(_Redundancy,0x69);
            _EmRead = 1;
            lcd_dis_menu_redudant();
            break;
        }
        break;  
    }
    return;
}


void menu_conf_33(){

    if(_uintCur){
        menu_conf_exit(SAVED5, MENU_50);
        return;
    }
    eedata_write(_CL_Dir,_CL_Dir_Init);
    eedata_write(_Code_Orde,_Code_Orde_Init);
    eedata_write(_CLDir_Protect,_CLDir_Protect_Init);
    eedata_write(_OPDir_Protect,_OPDir_Protect_Init);
    eedata_write(_CL_TorProtect,_CL_TorProtect_Init);
    eedata_write(_OP_TorProtect,_OP_TorProtect_Init);
    eedata_write(_Sn_Fun[0],_S1_Fun_Init);  
    eedata_write(_Sn_Status[0],_S1_Status_Init);
    eedata_write(_Sn_Fun[1],_S2_Fun_Init);
    eedata_write(_Sn_Status[1],_S2_Status_Init);
    eedata_write(_Sn_Fun[2],_S3_Fun_Init);
    eedata_write(_Sn_Status[2],_S3_Status_Init);
    eedata_write(_Sn_Fun[3],_S4_Fun_Init);
    eedata_write(_Sn_Status[3],_S4_Status_Init);
    eedata_write(_Monitor_With_OverTorque,_Monitor_With_OverTorque_Init);
    eedata_write(_Monitor_With_Remote,_Monitor_With_Remote_Init);
    eedata_write(_Pos_BackL,_Pos_BackL_Init);
    eedata_write(_Pos_BackH,_Pos_BackH_Init);
    eedata_write(_Tor_BackL,_Tor_BackL_Init);
    eedata_write(_Tor_BackH,_Tor_BackH_Init);
    eedata_write(_LocalCtrl,_LocalCtrl_Init);
    eedata_write(_TwoLinesCtrl,_TwoLinesCtrl_Init);
    eedata_write(_IC_Dbd,_IC_Dbd_Init);
    eedata_write(_IC_Logic,_IC_Logic_Init);
    eedata_write(_IC_Low_VP,_IC_Low_VP_Init);
    eedata_write(_IC_High_VP,_IC_High_VP_Init);
    eedata_write(_Pos_BackLogic,_Pos_BackLogic_Init);
    eedata_write(_Tor_BackLogic,_Tor_BackLogic_Init);
    eedata_write(_Local_Lock,_Local_Lock_Init);
    eedata_write(_Remote_Lock,_Remote_Lock_Init);
    eedata_write(_ESD_Action,_ESD_Action_Init);
    eedata_write(_ESD_ExceedHot,_ESD_ExceedHot_Init);
    eedata_write(_ESD_ExceedSp,_ESD_ExceedSp_Init);
    eedata_write(_ESD_ExceedLock,_ESD_ExceedLock_Init);
    eedata_write(_ESD_ExceedTime,_ESD_ExceedTime_Init);
    eedata_write(_Forbid_ESD,_Forbid_ESD_Init);
    eedata_write(_Interim_Ctrl,_Interim_Ctrl_Init);
    eedata_write(_InverseDisEnable,_InverseDisEnable_Init);
    eedata_write(_DP_Adress,_DP_Adress_Init);
    eedata_write(_POSALS,_POSALS_Init);
    eedata_write(_POSMAX,_POSMAX_Init);
    eedata_write(_POSMIT,_POSMIT_Init);
    eedata_write(_DPSLTO,_DPSLTO_Init);
    eedata_write(_MODSLTO,_MODSLTO_Init);
    eedata_write(_AUXMSK,_AUXMSK_Init);
    eedata_write(_BANDRT,_BANDRT_Init);
    eedata_write(_PARITY,_PARITY_Init);
    eedata_write(_RelayControl,_RelayControl_Init);
    eedata_write(_BIG_SHUCK,_BIG_SHUCK_Init);
    _StatusBack = 0;
    _strAlarmFlag = 0;
    RESETB_Tris = 0;
    Nop();
    RESETB_Write = 0;
    delayus(500);
    RESETB_Write = 1;
    dis_init();
#ifndef LANGUAGE_EN
    menu_conf_exit(SAVED4,MENU_50);
#endif
    return;    
}

void menu_conf_35(){
    Uint16 res,res1;
    Uint32 mul;

    eedata_write(_LOSPOS,_BusCount5);
    eedata_read(_L_CL_Limit,res);
    eedata_read(_Limit_Length,res1);
    mul = res1 *_BusCount5;
    res1 = mul/100;
    res1 += res;
    eedata_write(_LOSPOS_Code,res1);
    menu_conf_exit(SAVED18,MENU_POSALS);
    
    return;    
}

void menu_conf_36(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX1);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX1);
        break;
    }
    
    return;    
}

void menu_conf_37(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX2);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX2);
        break;
    }
    
    return;    
}

void menu_conf_38(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX3);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX3);
        break;
    }
    
    return;    
}

void menu_conf_39(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX4);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX4);
        break;
    }
    
    return;    
}

void menu_conf_40(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX5);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX5);
        break;
    }
    
    return;    
}

void menu_conf_41(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX6);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX6);
        break;
    }
    
    return;    
}

void menu_conf_42(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX7);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX7);
        break;
    }
    
    return;    
}

void menu_conf_43(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED17,MENU_AUX8);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED18,MENU_AUX8);
        break;
    }
    
    return;    
}

void menu_conf_44(){
    
    switch(_RmRead){
    case 0:
        eedata_write(_BIG_SHUCK,0x00);
        break;
    case 1:
        eedata_write(_BIG_SHUCK,0x69);
        break;
    }
    menu_conf_exit(SAVED18,MENU_44);
    
    return;    
}

void menu_conf_45(){

    if(_uintCur > 1){
        return;
    }
    switch(_uintCur){
    case 0:
        eedata_write(_VarSpeedEnable,0x69);
        lcd_dis_menu_3230();

        break;
    case 1:
        eedata_write(_VarSpeedEnable,0xff);
        menu_conf_exit(SAVED3, MENU_324);
        break;
    }
    return;
}

void menu_conf_46(){
    
    eedata_write(_DP_Adress2,_BusCount6);
    menu_conf_exit(SAVED5, MENU_REDUDANT);
    return;
}

void menu_conf_48(){
    
    if(_uintCur > 1){
        return;
    }
    switch(_uintCur){
    case 0:
        _EmRead = 1;
        switch(_RmRead){
        case 0:
            eedata_write(_Monitor_With_OverTorque,0x69);
            break;
        case 1:
            eedata_write(_Monitor_With_OverTorque,0x00);
            break;
        }
        menu_conf_exit(SAVED4, MENU_300B);
        break;
    case 1:
        _EmRead = 1;
        switch(_RmRead){
        case 0:
            eedata_write(_Monitor_With_Remote,0x69);
            break;
        case 1:
            eedata_write(_Monitor_With_Remote,0x00);
            break;
        }
    menu_conf_exit(SAVED5, MENU_300B);
    }
    return;
}

void (*menu_conf_func[])() = {
    NULL,
    menu_conf_0,
    menu_conf_1,
    menu_conf_2,
    menu_conf_3,
    menu_conf_4,
    menu_conf_5,
    NULL,
    NULL,
    menu_conf_8,
    menu_conf_9,
    menu_conf_10,
    menu_conf_11,
    menu_conf_12,
    menu_conf_13,
    menu_conf_14,
    menu_conf_15,
    menu_conf_16,
    menu_conf_17,
    menu_conf_18,
    menu_conf_19,
    menu_conf_20,
    menu_conf_21,
    menu_conf_22,
    menu_conf_23,
    menu_conf_24,
    menu_conf_25,
    menu_conf_26,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    menu_conf_33,
    menu_conf_35,
    menu_conf_36,
    menu_conf_37,
    menu_conf_38,
    menu_conf_39,
    menu_conf_40,
    menu_conf_41,
    menu_conf_42,
    menu_conf_43,
    menu_conf_44,
    menu_conf_45,
    menu_conf_46,
    NULL,
    menu_conf_48   
};


void menu_conf(){
    
    if(_Menu > 48){
        return;
    }
    if(menu_conf_func[_Menu]==NULL){
        return;
    }
    menu_conf_func[_Menu]();
}
