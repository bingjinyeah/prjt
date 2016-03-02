#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"

void flash_saved13(){
    lcd_dis_saved13();
    delayms(200);
}

Uint8 menu_conf_0(){
    Uint16 res;
    
    eedata_read(_Code_Orde, res);
    if (_Menu0Count0==res){
        lcd_dis_menu_1();
        return E_OK;
    }
    flash_saved13();
    lcd_dis_menu_0();
    delayms(300);
    flash_saved13();
    lcd_dis_menu_0();
    return E_OK;
}

Uint8 menu_conf_1(){
    
    switch(_uintCur){
        case 0: enter_menu2();break;
        case 1: enter_menu3();break;
        case 2: enter_menu4();break;
        case 3: enter_menu5();break;       
    }
    return E_OK;
}

Uint8 menu_conf_2(){
    
    switch(_uintCur){
        case 0: enter_menu20();break;
        case 1: enter_menu21();break;
        case 2: enter_menu22();break;
        case 3: enter_menu23();break; 
        case 4: enter_menu24();break;
        case 5: enter_menu25();break;
    }
    return E_OK;
}

Uint8 menu_conf_3(){
    
    
    switch(_uintCur){
        case 0: 
            if(_RmRead==4){
                _EmRead = 1;
                lcd_dis_menu_300b();
            }else{
                enter_menu30();
            }
            break;
        case 1: enter_menu31();break;
        case 2: enter_menu32();break;
        case 3: enter_menu33();break;       
    }
    return E_OK;
}

Uint8 menu_conf_4(){
    
    switch(_uintCur){
        case 0: enter_menu40();break;
        case 1: enter_menu41();break;
        case 2: enter_menu43();break;
#ifdef LANGUAGE_EN
        case 3: lcd_dis_menu_46();break;
#endif
    }
    return E_OK;
}

Uint8 menu_conf_5(){
    
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
#ifdef  LANGUAGE_EN
            flash_saved();
            lcd_dis_menu_5();
            delayms(300);
            flash_saved();
#else
            flash_saved15();
            lcd_dis_menu_5();
            delayms(300);
            flash_saved15();
#endif
            lcd_dis_menu_5();
            break;
        case 1: 
            eedata_write(_Code_Orde,_Menu5Count0);
#ifdef  LANGUAGE_EN
            flash_saved();
            lcd_dis_menu_5();
            delayms(300);
            flash_saved();
#else
            flash_saved15();
            lcd_dis_menu_5();
            delayms(300);
            flash_saved15();
#endif
            lcd_dis_menu_5();
            break;
        case 2: enter_menu50();break;
        
    }
    return E_OK;
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
    
#ifdef  LANGUAGE_EN
    
#else
    if(_uintCur==10){
        menu_conf_8_exit1();
        return;
    }else if(_uintCur==11){
        return;
    }
    flash_saved1();
    lcd_dis_menu_300();
    delayms(300);
    flash_saved1();
    lcd_dis_menu_300();
#endif
}
//relay output set
Uint8 menu_conf_8(){
    Uint16 res;
    
    if(_uintCur>=11){
        return E_OK;
    }
    if(_uintCur==0){
        res = 0xff;
    }
#ifdef  LANGUAGE_EN
    
#endif
    else{
        res = _uintCur;
    }    
    switch(para_w7){
        case 0: 
            eedata_write(_S1_Fun,res);
            if(_RmReadS!=0){
                eedata_write(_S1_Status,0x69);
            }else{
                eedata_write(_S1_Status,0xff);
            }
            menu_conf_8_exit0();
            break;
        case 1: 
            eedata_write(_S2_Fun,res);
            if(_RmReadS!=0){
                eedata_write(_S2_Status,0x69);
            }else{
                eedata_write(_S2_Status,0xff);
            }
            menu_conf_8_exit0();
            break;
        case 2: 
            eedata_write(_S3_Fun,res);
            if(_RmReadS!=0){
                eedata_write(_S3_Status,0x69);
            }else{
                eedata_write(_S3_Status,0xff);
            }
            menu_conf_8_exit0();
            break;
        case 3: 
            eedata_write(_S4_Fun,res);
            if(_RmReadS!=0){
                eedata_write(_S4_Status,0x69);
            }else{
                eedata_write(_S4_Status,0xff);
            }
            menu_conf_8_exit0();
            break;
    }
    return E_OK;
}

Uint8 menu_conf_9(){

#ifdef  LANGUAGE_EN
 
#endif
    return E_OK;
}
//local control menu
Uint8 menu_conf_10(){
    
    switch(_uintCur){
    case 0:
        eedata_write(_LocalCtrl,0x69);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_310();
        delayms(300);
        flash_saved();
#else
        flash_saved17();
        lcd_dis_menu_310();
        delayms(300);
        flash_saved17();
#endif         
        lcd_dis_menu_310();
        break;
    case 1:
        eedata_write(_LocalCtrl,0xff);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_310();
        delayms(300);
        flash_saved();
#else
        flash_saved18();
        lcd_dis_menu_310();
        delayms(300);
        flash_saved18();
#endif         
        lcd_dis_menu_310();
        break;
    }
    return E_OK;
}
//two line control control menu
Uint8 menu_conf_11(){
    
    switch(_uintCur){
    case 0:
        eedata_write(_TwoLinesCtrl,0x69);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_311();
        delayms(300);
        flash_saved();
#else
        flash_saved4();
        lcd_dis_menu_311();
        delayms(300);
        flash_saved4();
#endif         
        lcd_dis_menu_311();
        break;
    case 1:
        eedata_write(_TwoLinesCtrl,0x96);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_311();
        delayms(300);
        flash_saved();
#else
        flash_saved5();
        lcd_dis_menu_311();
        delayms(300);
        flash_saved5();
#endif         
        lcd_dis_menu_311();  
        break;
    case 2:
        eedata_write(_TwoLinesCtrl,0xff);  
        break;
    }
    return E_OK;
}

void menu_conf_12_exit(){
    _EmRead = 1;
#ifdef  LANGUAGE_EN
    flash_saved();
    lcd_dis_menu_312();
    delayms(300);
    flash_saved();
#else
    flash_saved1();
    lcd_dis_menu_312();
    delayms(300);
    flash_saved1();
#endif   
    lcd_dis_menu_312(); 
}
//proportion control menu
Uint8 menu_conf_12(){
    
    switch(_uintCur){
    case 0:
        eedata_write(_IC_Dbd,_Menu312Count0);
        menu_conf_12_exit();
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
            return E_OK; 
        }
        menu_conf_12_exit();
        break;
    case 2:
        eedata_write(IC_Low_VP,_Menu312Count1);
        menu_conf_12_exit();
        break;
    case 3:
        eedata_write(_IC_High_VP,_Menu312Count2);
        menu_conf_12_exit();
        break;
    case 4:
        eedata_write(_IC_Low,_IC[10]);
        menu_conf_12_exit();
        break;
    case 5:
        eedata_write(_IC_High,_IC[10]);
        menu_conf_12_exit();
        break;
    }
    return E_OK;
}

void menu_conf_13_exit(){
    
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_profibus();
        delayms(300);
        flash_saved();
#else
        flash_saved1();
        lcd_dis_menu_profibus();
        delayms(300);
        flash_saved1();
#endif   
        lcd_dis_menu_profibus(); 
}
//profibus control menu
Uint8 menu_conf_13(){
    
    Uint16 res,res1;
    Uint32 mul;
    switch(_uintCur){
    case 0:
        eedata_write(_DP_Adress,_BusCount0);
        menu_conf_13_exit();
        break;
    case 1:
        eedata_write(_DPSLTO,_BusCount1);
        menu_conf_13_exit();
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
        case 2:
            eedata_write(_POSALS,0x05);
            break;
        case 4:
            eedata_write(_POSALS,0x07);
            _uintCur = 0;
            _RmRead = 0;
            _BusCount5 = 0;
            _EmRead = 1;
            lcd_dis_menu_posals();
            break; 
        }
        menu_conf_13_exit();
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
        menu_conf_13_exit();
        break;
    case 4:
        eedata_write(_POSMIN,_BusCount2);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount2;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMIN_Code,res1);;
        menu_conf_13_exit();
        break;
    case 5:
        eedata_write(_POSMAX,_BusCount3);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount3;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMAX_Code,res1);;
        menu_conf_13_exit();
        break;
    case 6:
        eedata_write(_IC_Dbd,_BusCount4);
        menu_conf_13_exit();
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
            menu_conf_13_exit();
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
    return E_OK;
}

void menu_conf_14_exit(){

#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_320();
        delayms(300);
        flash_saved();
#else
        flash_saved7();
        lcd_dis_menu_320();
        delayms(300);
        flash_saved7();
#endif   
        lcd_dis_menu_320(); 
}
//lock set for remote and local
Uint8 menu_conf_14(){
    
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
        menu_conf_14_exit();
        break;
    case 1:
        if(_RmRead>1){
            break;
        }
        switch(_RmRead){
        case 0:
            eedata_write(_Remote_Lock,0xff);
            break;
        case 1:
            eedata_write(_Remote_Lock,0x69);
            break;
        }
        menu_conf_14_exit();
        break;
    }
    return E_OK;
}

//lesd control set
Uint8 menu_conf_15(){
    
    Uint16 res;
    if(_uintCur >1){
        return E_OK;
    }
    eedata_read(_AUXMSK,res);
    switch(_uintCur){
    case 0:
        res |= BIT7;
        eedata_write(_AUXMSK,res);
        _EmRead = 1;
        lcd_dis_menu3210();
        break;
    case 1:
        res &= ~BIT7;
        eedata_write(_AUXMSK,res);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_321();
        delayms(300);
        flash_saved();
#else
        flash_saved5();
        lcd_dis_menu_321();
        delayms(300);
        flash_saved5();
#endif
        lcd_dis_menu_321();
        break;
    }
    return E_OK;
}

void menu_conf_16_exit(){

#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_3210();
        delayms(300);
        flash_saved();
#else
        flash_saved8();
        lcd_dis_menu_3210();
        delayms(300);
        flash_saved8();
#endif   
        lcd_dis_menu_3210(); 
}
//esd forward set
Uint8 menu_conf_16(){
    
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
        menu_conf_16_exit();
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
        menu_conf_16_exit();
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
        menu_conf_16_exit();
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
        menu_conf_16_exit();
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
        menu_conf_16_exit();
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
        menu_conf_16_exit();
        break;        
    }
    return E_OK;
}

Uint8 menu_conf_17(){

    if(_uintCur > 2){
        return E_OK;
    }
    switch(_uintCur){
    case 0:
        eedata_write(_Interim_Ctrl,0xff);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_322();
        delayms(300);
        flash_saved();
#else
        flash_saved4();
        lcd_dis_menu_322();
        delayms(300);
        flash_saved4();
#endif   
        lcd_dis_menu_322(); 
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
    return E_OK;
}

void menu_conf_18_exit(){

#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_3220();
        delayms(300);
        flash_saved();
#else
        flash_saved10();
        lcd_dis_menu_3220();
        delayms(300);
        flash_saved10();
#endif   
        lcd_dis_menu_3220();
}

Uint8 menu_conf_18(){

    if(_uintCur > 3){
        return E_OK;
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
    menu_conf_18_exit();
    return E_OK;
}

void menu_conf_19_exit(){

#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_3221();
        delayms(300);
        flash_saved();
#else
        flash_saved10();
        lcd_dis_menu_3221();
        delayms(300);
        flash_saved10();
#endif   
        lcd_dis_menu_3221();
}

Uint8 menu_conf_19(){

    if(_uintCur > 3){
        return E_OK;
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
    menu_conf_19_exit();
    return E_OK;
}

Uint8 menu_conf_20(){
    
    eedata_write(_POSMIT,_Menu323Count);
#ifdef  LANGUAGE_EN
    flash_saved();
    lcd_dis_menu_323();
    delayms(300);
    flash_saved();
#else
    flash_saved5();
    lcd_dis_menu_323();
    delayms(300);
    flash_saved5();
#endif   
    lcd_dis_menu_323();    
    return E_OK;
}

Uint8 menu_conf_21(){

    if(_uintCur > 2){
        return E_OK;
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
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_3230();
        delayms(300);
        flash_saved();
#else
        flash_saved1();
        lcd_dis_menu_3230();
        delayms(300);
        flash_saved1();
#endif   
        lcd_dis_menu_3230(); 
        break;
    }
    return E_OK;
}

void menu_conf_22_exit(){

#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_32301();
        delayms(300);
        flash_saved();
#else
        flash_saved6();
        lcd_dis_menu_32301();
        delayms(300);
        flash_saved6();
#endif   
        lcd_dis_menu_32301(); 
}

void menu_conf_22_exit1(){

#ifdef  LANGUAGE_EN
        flash_saved1();
        lcd_dis_menu_32301();
        delayms(300);
        flash_saved1();
#else
        flash_saved4();
        lcd_dis_menu_32301();
        delayms(300);
        flash_saved4();
#endif   
        lcd_dis_menu_32301(); 
}

Uint8 menu_conf_22(){

    if(_Menu22_ConfCount-- > 10){
        return E_OK;
    }
    switch(_Menu22_ConfCount){
    case 0:
        if(_uintCur){
            eedata_write(_OP_Speed1,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position1,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 1:
        if(_uintCur){
            eedata_write(_OP_Speed2,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position2,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 2:
        if(_uintCur){
            eedata_write(_OP_Speed3,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position3,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 3:
        if(_uintCur){
            eedata_write(_OP_Speed4,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position4,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 4:
        if(_uintCur){
            eedata_write(_OP_Speed5,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position5,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 5:
        if(_uintCur){
            eedata_write(_OP_Speed6,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position6,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 6:
        if(_uintCur){
            eedata_write(_OP_Speed7,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position7,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 7:
        if(_uintCur){
            eedata_write(_OP_Speed8,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position8,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 8:
        if(_uintCur){
            eedata_write(_OP_Speed9,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position9,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    case 9:
        if(_uintCur){
            eedata_write(_OP_Speed10,_Menu32301Count2);
            menu_conf_22_exit();
        }else{
            eedata_write(_OP_Position10,_Menu32301Count1);
            menu_conf_22_exit1();
        }
        break;
    }
    return E_OK;
}

void menu_conf_23_exit(){

#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_32302();
        delayms(300);
        flash_saved();
#else
        flash_saved6();
        lcd_dis_menu_32302();
        delayms(300);
        flash_saved6();
#endif   
        lcd_dis_menu_32302(); 
}

void menu_conf_23_exit1(){

#ifdef  LANGUAGE_EN
        flash_saved1();
        lcd_dis_menu_32302();
        delayms(300);
        flash_saved1();
#else
        flash_saved4();
        lcd_dis_menu_32302();
        delayms(300);
        flash_saved4();
#endif   
        lcd_dis_menu_32302(); 
}

Uint8 menu_conf_23(){

    if(_Menu23_ConfCount-- > 10){
        return E_OK;
    }
    switch(_Menu23_ConfCount){
    case 0:
        if(_uintCur){
            eedata_write(_CL_Speed1,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position1,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 1:
        if(_uintCur){
            eedata_write(_CL_Speed2,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position2,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 2:
        if(_uintCur){
            eedata_write(_CL_Speed3,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position3,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 3:
        if(_uintCur){
            eedata_write(_CL_Speed4,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position4,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 4:
        if(_uintCur){
            eedata_write(_CL_Speed5,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position5,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 5:
        if(_uintCur){
            eedata_write(_CL_Speed6,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position6,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 6:
        if(_uintCur){
            eedata_write(_CL_Speed7,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position7,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 7:
        if(_uintCur){
            eedata_write(_CL_Speed8,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position8,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 8:
        if(_uintCur){
            eedata_write(_CL_Speed9,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position9,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    case 9:
        if(_uintCur){
            eedata_write(_CL_Speed10,_Menu32302Count2);
            menu_conf_23_exit();
        }else{
            eedata_write(_CL_Position10,_Menu32302Count1);
            menu_conf_23_exit1();
        }
        break;
    
    }
    return E_OK;
}

void menu_conf_24_exit(){
    
#ifdef  LANGUAGE_EN
        flash_saved1();
        lcd_dis_menu_330();
        delayms(300);
        flash_saved1();
#else
        flash_saved14();
        lcd_dis_menu_330();
        delayms(300);
        flash_saved14();
#endif   
        lcd_dis_menu_330();
}

Uint8 menu_conf_24(){
    
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
        menu_conf_24_exit();
        break;
    case 1:
        eedata_write(_Pos_BackL,_Menu330Count);
        menu_conf_24_exit();
        break;
    case 2:
        eedata_write(_Pos_BackH,_Menu330Count);
        menu_conf_24_exit();
        break;    
    }
    return E_OK;
}

void menu_conf_25_exit(){
    
#ifdef  LANGUAGE_EN
        flash_saved1();
        lcd_dis_menu_331();
        delayms(300);
        flash_saved1();
#else
        flash_saved14();
        lcd_dis_menu_331();
        delayms(300);
        flash_saved14();
#endif   
        lcd_dis_menu_331();
}

Uint8 menu_conf_25(){
    
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
        menu_conf_25_exit();
        break;
    case 1:
        eedata_write(_Tor_BackL,_Menu331Count);
        menu_conf_25_exit();
        break;
    case 2:
        eedata_write(_Tor_BackH,_Menu331Count);
        menu_conf_25_exit();
        break;    
    }
    return E_OK;
}

void menu_conf_26_exit(){
    
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_modbus();
        delayms(300);
        flash_saved();
#else
        flash_saved1();
        lcd_dis_menu_modbus();
        delayms(300);
        flash_saved1();
#endif   
        lcd_dis_menu_modbus();
}

Uint8 menu_conf_26(){
    Uint16 res,res1;
    Uint32 mul;
    
    switch(_uintCur){
    case 0:
        eedata_write(_DP_Adress,_BusCount0);
        menu_conf_26_exit();
        break;   
    case 1:
        if(_RmRead>7){
            break;
        }
        eedata_write(_BANDRT,_RmRead);
        menu_conf_26_exit();
        break;
    case 2:
        if(_RmRead>2){
            break;
        }
        eedata_write(_PARITY,_RmRead);
        menu_conf_26_exit();
        break;
    case 3:
        eedata_write(_MODSLTO,_BusCount1);
        menu_conf_26_exit();
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
            return E_OK;
        }
        menu_conf_26_exit();
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
        menu_conf_26_exit();
        break;
    case 6:
        eedata_write(_POSMIN,_BusCount2);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount2;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMIN_Code,res1);
        menu_conf_26_exit();
        break;
    case 7:
        eedata_write(_POSMAX,_BusCount3);
        eedata_read(_L_CL_Limit,res);
        eedata_read(_Limit_Length,res1);
        mul = res1 *_BusCount3;
        res1 = mul/100;
        res1 += res;
        eedata_write(_POSMAX_Code,res1);
        menu_conf_26_exit();
        break;
    case 8:
        eedata_write(_IC_Dbd,_BusCount4);
        menu_conf_26_exit();
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
            menu_conf_26_exit();
            break;
        case 1:
            eedata_write(_Redundancy,0x69);
            _EmRead = 1;
            lcd_dis_menu_redudant();
            break;
        }
        break;  
    }
    return E_OK;
}

Uint8 menu_conf_35(){
    Uint16 res,res1;
    Uint32 mul;

    eedata_write(_LOSPOS,_BusCount5);
    eedata_read(_L_CL_Limit,res);
    eedata_read(_Limit_Length,res1);
    mul = res1 *_BusCount5;
    res1 = mul/100;
    res1 += res;
    eedata_write(_LOSPOS_Code,res1);
    menu_conf_exit(SAVED0,SAVED18,DIS_POSALS);
    
    return E_OK;    
}

Uint8 menu_conf_36(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX1);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX1);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_37(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX2);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX2);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_38(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX3);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX3);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_39(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX4);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX4);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_40(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX5);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT0;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX5);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_41(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX6);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT1;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX6);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_42(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX7);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT2;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX7);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_43(){
    Uint16 res;
    
    switch(_uintCur){
    case 0:
        eedata_read(_AUXMSK,res);
        res |= BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED17,DIS_AUX8);
        break;
    case 1:
        eedata_read(_AUXMSK,res);
        res &= ~BIT3;
        eedata_write(_AUXMSK,res);
        menu_conf_exit(SAVED0,SAVED18,DIS_AUX8);
        break;
    }
    
    return E_OK;    
}

Uint8 menu_conf_44(){
    
    switch(_RmRead){
    case 0:
        eedata_write(_BIG_SHUCK,0x00);
        break;
    case 1:
        eedata_write(_BIG_SHUCK,0x69);
        break;
    }
    flash_saved18();
    lcd_dis_menu_44();
    delayms(300);
    flash_saved18();
    lcd_dis_menu_44();
    
    return E_OK;    
}

Uint8 menu_conf_45(){

    if(_uintCur > 1){
        return E_OK;
    }
    switch(_uintCur){
    case 0:
        eedata_write(_VarSpeedEnable,0x69);
        lcd_dis_menu_3230();

        break;
    case 1:
        eedata_write(_VarSpeedEnable,0xff);
#ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_324();
        delayms(300);
        flash_saved();
#else
        flash_saved3();
        lcd_dis_menu_324();
        delayms(300);
        flash_saved3();
#endif   
        lcd_dis_menu_324(); 
        break;
    }
    return E_OK;
}

Uint8 menu_conf_46(){
    
    eedata_write(_DP_Adress2,_BusCount6);
#ifdef  LANGUAGE_EN
    flash_saved();
    lcd_dis_menu_redudant();
    delayms(300);
    flash_saved();
#else
    flash_saved5();
    lcd_dis_menu_redudant();
    delayms(300);
    flash_saved5();
#endif   
    lcd_dis_menu_redudant();    
    return E_OK;
}

Uint8 menu_conf_48(){
    
    Uint16 res;
    if(_uintCur > 1){
        return E_OK;
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
    #ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_300b();
        delayms(300);
        flash_saved();
    #else
        flash_saved4();
        lcd_dis_menu_300b();
        delayms(300);
        flash_saved4();
    #endif   
        lcd_dis_menu_300b();
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
    #ifdef  LANGUAGE_EN
        flash_saved();
        lcd_dis_menu_300b();
        delayms(300);
        flash_saved();
    #else
        flash_saved5();
        lcd_dis_menu_300b();
        delayms(300);
        flash_saved5();
    #endif   
        lcd_dis_menu_300b();
    }
    return E_OK;
}

        
        
    
    
    
    
    
    
    
    

Uint8 (*menu_conf_func[])() = {
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


Uint8 menu_conf(){
    
    if(_Menu > 48){
        return E_OK;
    }
    if(menu_conf_func[_Menu]==NULL){
        return E_OK;
    }
    return menu_conf_func[_Menu]();
}
