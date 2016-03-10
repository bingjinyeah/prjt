#include <xc.h>
#include "basic.h"
#include "eedata.h"
#include "flag.h"
#include "para.h"
#include "lcd.h"
#include "pincfg.h"
#include "relay.h"
#include "power.h"
#include "esd.h"
#include "port.h"
#include "timer.h"
#include "adc.h"
#include "di.h"
#include "action.h"
#include "code.h"
#include "spi.h"

void motor_run_clock(){
    OP_Tris = 0;
    Nop();
    OP_Write = 0;
    OP_Write = 0;
    CL_Tris = 0;
    Nop();
    CL_Write = 1;
    CL_Write = 1;
    _Movement_Dire = 0x6996;
}
void motor_run_antic(){
    OP_Tris = 0;
    Nop();
    OP_Write = 1;
    OP_Write = 1;
    CL_Tris = 0;
    Nop();
    CL_Write = 0;
    CL_Write = 0;
    _Movement_Dire = 0x9669;
}

Uint8 open_phase1(){
    Uint16 res;
    
    if(_strAlarmFlag & _PowerDownFlag){
        return E_ERR;
    }
    if(_strAlarmFlag & _PhaseLostedFlag){
        return E_ERR;
    }
    if(com_esd()){
        return E_ERR;
    }
    if(check_hot()){
        return E_ERR;
    }
    if(_strAlarmFlag & _OTFlag){
        lcd_dis_clr_alarm();
        lcd_dis_alarm_opovertor();
        return E_ERR;
    }
    if((_Menu==3)&&(_uintCur==1)){
        return E_OK;
    }
    if(_L_CodeVP>(65535-100)){
        _strAlarmFlag |= _VPOver;
        _DP_DIAGR1 |= BIT6;
        return E_ERR;
    } 
    _strAlarmFlag &= ~_VPOver;
    _DP_DIAGR1 &= ~BIT6;
    eedata_read(_OPDir_Protect,res);
    if(res==0x69){
        return E_OK;
    }
    if(_strAlarmFlag & _OSFlag){
        return E_ERR;
    }
    
    return E_OK;
}

Uint8 open_phase2(){
    Uint16 res;
    Uint16 ord,dir;
    
#ifndef PHASE1
    if(_PhOrderFlag!=0xa569){
        return E_ERR;
    }
#endif
    _StatusBack |= _OpeningFlag;
    _DP_IDATA2 |= BIT1;
    _StatusBack |= _RunningFlag;
    _ByteRunningFlag = 0x55;
    _L_CodePreVP = _L_CodeVP;
    _L_CodePreVP2 = _L_CodeVP;
    _DirPreVP = _L_CodeVP;
    _L_CodePPreVP = _L_CodeVP;
    _JamCount = 0;
    
    eedata_read(_PhaseOrder,ord);
    eedata_read(_CL_Dir,dir);
    
    if(((ord==wtrue)&&(dir==ufalse))||((ord==wfalse)&&(dir==utrue))){
        motor_run_clock();
    }else{
        motor_run_antic();
    }
    t1_init(_conT1Time);
    rush_relay_open();
    rush_relay_run();
    _JamCount = 0;
    while(1){
        if((_L_CodeVP==_L_CodePreVP)||(_L_CodeVP==_L_CodePPreVP)){
            spi_init_dummy();
            adc12_init_dummy();
            t1_init_dummy();
            di_init_dummy();
            delayms(2);
            if(_strAlarmFlag & _PowerDownFlag){
                stop();
                return E_ERR;
            }
            if(_strAlarmFlag & _PhaseLostedFlag){
                stop();
                return E_ERR;
            }
            _L_CodePreVP = _L_CodeVP;
            get_code_vp();
            _L_CodeVP = circle_to_line(_CodeVP);
            if(_JamCount>=1000){
                res = 1.2*_NJADLength;
                stop();
                if(_OPNJ[10] > res){
                    _strAlarmFlag |= _JamFlag;
                    _DP_DIAGR1 |= BIT0;
                    rush_relay_jam();
                    lcd_dis_clr_alarm();
                    lcd_dis_alarm_jam();
                    delayms(5000);
                    rush_relay_conjam(); 
                }else{
                    _strAlarmFlag |= _NoLoadFlag;
                    _DP_DIAGR1 |= BIT2;
                    lcd_dis_clr_alarm();
                    lcd_dis_alarm_noload();
                    delayms(1000);
                }
                return E_ERR;
            }
        }else{
            _strAlarmFlag &= ~_JamFlag;
            _DP_DIAGR1 &= ~BIT0;
            _strAlarmFlag &= ~_NoLoadFlag;
            _DP_DIAGR1 &= ~BIT2;
            _strAlarmFlag &= ~_TimeStopFlag;
            _DP_IDATA2 &= ~BIT2;
            rush_relay_conjam();
            eedata_read(_Interim_Ctrl,res);
            if((_Interim_Ctrl==0x69)||(_Interim_Ctrl==0x96)){
                _MoveCount = 0;
                _JamCount = 0;
            }
            _Count2S = 0;
            return E_OK;
        }
    }
}

Uint8 open_phase3(){
    Uint16 res;
    
    rush_status();
    check_remote_aux();
    relay_position_judge();
    rush_relay_main();
    if(judge_open_dir()==E_ERR){
        return E_ERR;
    }
    if(_Menu==3){
        if(cal_length()==E_ERR){
            return E_ERR;
        }
    }
#ifdef  PHASE1
    res = 400;
#else
    res = 100;
#endif
    if(_JamCount>=res){
        _JamCount = 101;
        eedata_read(_OP_TorProtect,res);
        if(_NJPercent>=res){
            _strAlarmFlag |= _OTFlag;
            _DP_DIAGR0 |= BIT4;
            _WriteEEPROMFlag = 0x55aa;
            eedata_write(_OP_OverTorPos,_VPPercent);
            _WriteEEPROMFlag = 0;
            lcd_dis_alarm_opovertor();
            return E_ERR;
        }
    }
    if(open_phase1()==E_ERR){
        return E_ERR;
    }
    if((_StatusBack & _OpeningFlag)==0){
        return E_ERR;
    }
    eedata_read(_Interim_Ctrl,res);
    if(res==0x69){
        eedata_read(_Start_Pos,res);
        if(_VPPercent < res){
            return E_OK;
        }
        if(_StatusBack & _RunOver){
            _StatusBack &= ~_RunOver;
            stop();
            _StatusBack |= _TimeStopFlag;
            _DP_IDATA2 |= BIT2;
            eedata_read(_StopTime,res);
            if(res>99){
                res = 99;
            }
            _StopTimer = 5*res;
            while(--_StopTimer){
                if(in_stop()){
                    return E_ERR;
                }
                rush_status();
                relay_position_judge();
                rush_relay_main();
                delayms(200);
            }
            eedata_read(_OPDir_Protect,res);
            if(res==0x69){
                return open_phase2();
            }
            if(_strAlarmFlag & _OSFlag){
                return E_ERR;
            }
            return open_phase2();
            
        }else{
            eedata_read(_MoveTime,res);
            if(res>99){
                res = 99;
            }
            res *= 200;
            if(_MoveCount <= res){
                return E_OK;
            }
            _StatusBack &= ~_RunOver;
            stop();
            _StatusBack |= _TimeStopFlag;
            _DP_IDATA2 |= BIT2;
            eedata_read(_StopTime,res);
            if(res>99){
                res = 99;
            }
            _StopTimer = 5*res;
            while(--_StopTimer){
                if(in_stop()){
                    return E_ERR;
                }
                rush_status();
                relay_position_judge();
                rush_relay_main();
                delayms(200);
            }
        }
    }
    
    
    return E_OK;
}

Uint8 open_phase4(){
    return E_OK;
}

Uint8 close_phase1(){
        Uint16 res;
    
    if(_strAlarmFlag & _PowerDownFlag){
        return E_ERR;
    }
    if(_strAlarmFlag & _PhaseLostedFlag){
        return E_ERR;
    }
    if(com_esd()){
        return E_ERR;
    }
    if(check_hot()){
        return E_ERR;
    }
    if(_strAlarmFlag & _CTFlag){
        lcd_dis_clr_alarm();
        lcd_dis_alarm_clovertor();
        return E_ERR;
    }
    if((_Menu==3)&&(_uintCur==1)){
        return E_OK;
    }
    if(_L_CodeVP<100){
        _strAlarmFlag |= _VPOver;
        _DP_DIAGR1 |= BIT6;
        return E_ERR;
    } 
    _strAlarmFlag &= ~_VPOver;
    _DP_DIAGR1 &= ~BIT6;
    eedata_read(_CLDir_Protect,res);
    if(res==0x69){
        return E_OK;
    }
    if(_strAlarmFlag & _CSFlag){
        return E_ERR;
    }
    
    return E_OK;
}

Uint8 close_phase2(){
    Uint16 res;
    Uint16 ord,dir;
    
#ifndef PHASE1
    if(_PhOrderFlag!=0xa569){
        return E_ERR;
    }
#endif
    _StatusBack |= _ClosingFlag;
    _DP_IDATA2 |= BIT0;
    _StatusBack |= _RunningFlag;
    _ByteRunningFlag = 0x55;
    _L_CodePreVP = _L_CodeVP;
    _L_CodePreVP2 = _L_CodeVP;
    _DirPreVP = _L_CodeVP;
    _L_CodePPreVP = _L_CodeVP;
    _JamCount = 0;
    
    eedata_read(_PhaseOrder,ord);
    eedata_read(_CL_Dir,dir);
    
    if(((ord==wtrue)&&(dir==ufalse))||((ord==wfalse)&&(dir==utrue))){
        motor_run_antic();
    }else{
        motor_run_clock();
    }
    t1_init(_conT1Time);
    rush_relay_close();
    rush_relay_run();
    _JamCount = 0;
    while(1){
        if((_L_CodeVP==_L_CodePreVP)||(_L_CodeVP==_L_CodePPreVP)){
            spi_init_dummy();
            adc12_init_dummy();
            t1_init_dummy();
            di_init_dummy();
            delayms(2);
            if(_strAlarmFlag & _PowerDownFlag){
                stop();
                return E_ERR;
            }
            if(_strAlarmFlag & _PhaseLostedFlag){
                stop();
                return E_ERR;
            }
            _L_CodePreVP = _L_CodeVP;
            get_code_vp();
            _L_CodeVP = circle_to_line(_CodeVP);
            if(_JamCount>=1000){
                res = 1.2*_NJADLength;
                stop();
                if(_CLNJ[10] > res){
                    _strAlarmFlag |= _JamFlag;
                    _DP_DIAGR1 |= BIT0;
                    rush_relay_jam();
                    lcd_dis_clr_alarm();
                    lcd_dis_alarm_jam();
                    delayms(5000);
                    rush_relay_conjam(); 
                }else{
                    _strAlarmFlag |= _NoLoadFlag;
                    _DP_DIAGR1 |= BIT2;
                    lcd_dis_clr_alarm();
                    lcd_dis_alarm_noload();
                    delayms(1000);
                }
                return E_ERR;
            }
        }else{
            _strAlarmFlag &= ~_JamFlag;
            _DP_DIAGR1 &= ~BIT0;
            _strAlarmFlag &= ~_NoLoadFlag;
            _DP_DIAGR1 &= ~BIT2;
            _strAlarmFlag &= ~_TimeStopFlag;
            _DP_IDATA2 &= ~BIT2;
            rush_relay_conjam();
            eedata_read(_Interim_Ctrl,res);
            if((_Interim_Ctrl==0x69)||(_Interim_Ctrl==0x96)){
                _MoveCount = 0;
                _JamCount = 0;
            }
            _Count2S = 0;
            return E_OK;
        }
    }
}

Uint8 close_phase3(){
    return E_OK;
}

Uint8 close_phase4(){
    
    return E_OK;
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

Uint8 judge_opdir_protect(){
    Uint16 res;
    
    eedata_read(_OPDir_Protect,res);
    if(res==utrue){
        if(_strAlarmFlag & _OSFlag){
            return true;
        }
    }
    
    return false;
}

Uint8 judge_optor_protect(){
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

Uint8 judge_cldir_protect(){
    Uint16 res;
    
    eedata_read(_CLDir_Protect,res);
    if(res==utrue){
        if(_strAlarmFlag & _CSFlag){
            return true;
        }
    }
    
    return false;
}

Uint8 judge_cltor_protect(){
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