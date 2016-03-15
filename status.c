#include "includes.h"


void cal_status(){
    Uint16 res;
    register int store;
    
    store = PSVPAG;
    PSVPAG = __builtin_psvpage(&_L_CL_Limit);
    _PSV = 1;
    if(_L_CodeVP>=_L_OP_Limit){
        _VPPercent = 100;
        _DP_RAWPOS = 0xff;
        if(_POSMIN>=_POSMAX){
            _DP_MODPOS = 0;
        }else{
            _DP_MODPOS = 0xff;
        }
        _strAlarmFlag &= ~_CSFlag;
        _DP_IDATA1 &= ~BIT1;
        _strAlarmFlag |= _OSFlag;
        _DP_IDATA1 |= BIT2;
        _Limit_Flag = 0x96;
        _VPDA = _Pos_BackH - _Pos_BackL;
    }else if(_L_CodeVP<=_L_CL_Limit){
        _VPPercent = 0;
        _DP_RAWPOS = 0;
        if(_POSMIN>=_POSMAX){
            _DP_MODPOS = 0xff;
        }else{
            _DP_MODPOS = 0;
        }
        _strAlarmFlag &= ~_OSFlag;
        _DP_IDATA1 &= ~BIT2;
        _strAlarmFlag |= _CSFlag;
        _DP_IDATA1 |= BIT1;
        _Limit_Flag = 0x69;
        _VPDA = 0;
    }else{
        _VPPercent = (_L_CodeVP - _L_CL_Limit)*100/_Limit_Length;
        _DP_RAWPOS = (_L_CodeVP - _L_CL_Limit)*255/_Limit_Length;
        if(_POSMIN>=_POSMAX){
            if(_L_CodeVP>=_POSMIN_Code){
                _DP_MODPOS = 0;
            }else if(_L_CodeVP<=_POSMAX_Code){
                _DP_MODPOS = 0xff;
            }else{
                _DP_MODPOS = (_POSMIN_Code - _L_CodeVP)*255/(_POSMIN_Code - _POSMAX_Code);
            }
        }else{
            if(_L_CodeVP<=_POSMIN_Code){
                _DP_MODPOS = 0;
            }else if(_L_CodeVP>=_POSMAX_Code){
                _DP_MODPOS = 0xff;
            }else{
                _DP_MODPOS = (_L_CodeVP - _POSMIN_Code)*255/(_POSMAX_Code - _POSMIN_Code);
            }
        }
        _VPDA = (_L_CodeVP - _L_CL_Limit)*(_Pos_BackH - _Pos_BackL)/_Limit_Length;
        _strAlarmFlag &= ~_OSFlag;
        _DP_IDATA1 &= ~BIT2;
        _strAlarmFlag &= ~_CSFlag;
        _DP_IDATA1 &= ~BIT1;
        _Limit_Flag = 0;
    }
    if(_Pos_BackLogic==ufalse){
        _VPDA += _Pos_BackL;  
    }else{
        _VPDA = _Pos_BackH - _VPDA;
    }
    if((_StatusBack & _ClosingFlag)||(_StatusBack & _OpeningFlag)){
        if(((_StatusBack & _ClosingFlag)&&(_CL_Dir==_ufalse))||
           ((_StatusBack & _OpeningFlag)&&(_CL_Dir!=_ufalse))){
            res = _OPNJ[10];
        }else{
            res = _CLNJ[10];
        }
        _NJPercent = res*100/_NJADLength;
        _DP_NJ = res*255/_NJADLength;
        _NJDA = res*(_Tor_BackH - _Tor_BackL)/_NJADLength;
        if(_Tor_BackLogic==ufalse){
            _NJDA += _Tor_BackL;  
        }else{
            _NJDA = _Tor_BackH - _NJDA;
        }
    }
    _NJPercent = 0;
    _DP_NJ = 0;
    _NJDA = 0;    
    
    PSVPAG = store;
}

void rush_status(){
    Uint16 res;
    
    clr_wdt();
    spi2_init_dummy();
    adc12_init_dummy();
    di_init_dummy();
    rush_power();
    eedata_read(_Card,res);
    if(res!=0xaa){
        dp_init1();
    }
    t1_init_dummy();
    if(_DisInitCount>2000){
        _DisInitCount = 0;
        _RushCount = 100;
        RESETB_Tris = 0;
        Nop();
        RESETB_Write = 0;
        delayus(4);
        RESETB_Write = 1;
        dis_init();
    }
    rush_monitor();
    _L_CodePreVP = _L_CodeVP;
    _SPI2_DA = ufalse;
    get_code_vp();
    _SPI2_DA = utrue;
    get_code_vp();
    _L_CodeVP = circle_to_line(_CodeVP);
    
    if(_L_CodePreVP>=_L_CodeVP){
        if(_L_CodePreVP>(_L_CodeVP+16)){
            return;
        }
        if((_L_CodeVP>(_L_CodePreVP2+2))||(_L_CodeVP<(_L_CodePreVP2-2))){
            _DP_IDATA1 |= BIT0;
            _RushRuning = 0;
            _L_CodePreVP2 = _L_CodeVP;
        }else{
            if(_RushRuning>=400){
                _DP_IDATA1 &= ~BIT0;
                _RushRuning = 400;
            }
        }
    }else if((_L_CodePreVP+16)<_L_CodeVP){
        return;
    }
    _PreVPPercent = _VPPercent;
    _Pre_Limit_Flag = _Limit_Flag;
    cal_status();
    if(_Menu!=0){
        _uintMenuCount = 0;
        if(_Menu==3){
            led_g_r_set(1,1);
            goto rs_90;
        }else if(_Menu==33){
            if(_ByteRunningFlag==0x55){
                _NJPercent_Temp = _NJPercent;
                lcd_dis_menu_43_content();
            }
            goto rs_60;
        }
    }
    if((_PreVPPercent==_VPPercent)&&(_Pre_Limit_Flag==_Limit_Flag)&&(_RushCount<100)){
        goto rs_90;
    }
    _RushCount = 0;
    lcd_dis_vp();
rs_60:
    if(_strAlarmFlag & _CSFlag){
        led_g_r_set(1,0);
        goto rs_90;
    }
    if(_strAlarmFlag & _OSFlag){
        led_g_r_set(0,1);
        goto rs_90;
    }
    led_g_r_set(1,1);
rs_90:
    if(_strAlarmFlag & _CTFlag){
        eedata_read(_CL_OverTorPos,res);
        if(_VPPercent>(res+2)){
            _strAlarmFlag &= ~_CTFlag;
            _DP_DIAGR0 &= ~BIT3;
        }
    }
    if(_strAlarmFlag & _OTFlag){
        eedata_read(_OP_OverTorPos,res);
        if((_VPPercent+2)<res){
            _strAlarmFlag &= ~_OTFlag;
            _DP_DIAGR0 &= ~BIT4;
        }
    }
    
}

void rush_feedback(){
    Uint16 cll,opl;
    
    spi2_init();
    delayms(10);
    _SPI2_DA = ufalse;
    _NJDA = 0;
    //sample the vpcode when power on,commit for test as no bianmaqi 
    get_code_vp();
    get_code_vp();
    _L_CodeVP = circle_to_line(_CodeVP);
    eedata_read(_L_CL_Limit,cll);
    eedata_read(_L_OP_Limit,opl);
    if(_CodeVP<=cll){
        led_g_r_set(1,0);
    }else if(_CodeVP>=opl){
        led_g_r_set(0,1);
    }else{
        led_g_r_set(1,1);
    }
}
