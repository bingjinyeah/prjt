#include <xc.h>
#include "basic.h"
#include "eedata.h"
#include "flag.h"
#include "para.h"
#include "lcd.h"
#include "pincfg.h"

void open_phase1(){
    
}

void open_phase2(){
    
}

void open_phase3(){
    
}

void open_phase4(){
    
}

void close_phase1(){
    
}

void close_phase2(){
    
}

void close_phase3(){
    
}

void close_phase4(){
    
}

void forbid(){
    
}

void stop(){
    
}

void dis_open_lock(){
    _StatusBack |= _OP_LockFlag;
    _DP_IDATA2 |= BIT4;
    lcd_dis_clr_alarm();
    lcd_dis_alarm_oplock();
    while(_StopTimer--){
        rush_status();
        relay_position_judge();
        rush_relay_main();
        delayms(20);
    }
}


void dis_close_lock(){
    _StatusBack |= _CL_LockFlag;
    _DP_IDATA2 |= BIT5;
    lcd_dis_clr_alarm();
    lcd_dis_alarm_cllock();
    while(_StopTimer--){
        rush_status();
        relay_position_judge();
        rush_relay_main();
        delayms(20);
    }
}

void judge_opdir_protect(){
    Uint16 res;
    
    eedata_read(_OPDir_Protect,res);
    if(res==utrue){
        if(_strAlarmFlag & _OSFlag){
            return true;
        }
    }
    
    return false;
}

void judge_optor_protect(){
    Uint16 res;
    
    eedata_read(_OP_TorProtect,res);
    if(_NJPercent>=res){
        _strAlarmFlag |= _OTFlag;
        _DP_DIAGR0 |= BIT4;
        _WriteEEPROMFlag = 0x55aa;
        eedata_write(_OP_OverTorPos,_VPPercent);
        _WriteEEPROMFlag = 0;
        lcd_dis_clr_alarm();
        lcd_dis_alarm_opovertor();
        return true;
    }
    
    return false;
}

void judge_cldir_protect(){
    Uint16 res;
    
    eedata_read(_CLDir_Protect,res);
    if(res==utrue){
        if(_strAlarmFlag & _CSFlag){
            return true;
        }
    }
    
    return false;
}

void judge_cltor_protect(){
    Uint16 res;
    
    eedata_read(_CL_TorProtect,res);
    if(_NJPercent>=res){
        _strAlarmFlag |= _CTFlag;
        _DP_DIAGR0 |= BIT3;
        _WriteEEPROMFlag = 0x55aa;
        eedata_write(_CL_OverTorPos,_VPPercent);
        _WriteEEPROMFlag = 0;
        lcd_dis_clr_alarm();
        lcd_dis_alarm_clovertor();
        return true;
    }
    
    return false;
}

Uint8 judge_open_dir(){
    
    return E_OK;
}

Uint8 judge_close_dir(){
    
    return E_OK;
}