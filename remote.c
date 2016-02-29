#include <xc.h>
#include "basic.h"
#include "eedata.h"
#include "flag.h"
#include "para.h"
#include "lcd.h"
#include "pincfg.h"

extern Uint16 _EEDATA(2) _AUXMSK;
extern Uint16 _EEDATA(2) _Remote_Lock;
extern Uint16 _EEDATA(2) _TwoLinesCtrl;

void check_card(){
    
}

void check_remote_aux(){
    
}

void dp_init0(){
    
}

void dp_init1(){
    
}

void dp_init2(){
    
}

void dp_reset(){
    
}

void dp_app_func(){
    
}

void dp_tx_func(){
    
}

Uint8 judge_aux_open(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    R_OP_Tris = 1;
    if(res & BIT0 ==0){
        b = true;
    }else{
        b = false;
    }
        
    if(R_OP_Read==0){
        return b;
    }
    delayus(100);
    if(R_OP_Read==0){
        return b;
    }
    return ~b;
}

Uint8 judge_aux_close(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    R_CL_Tris = 1;
    if(res & BIT1 ==0){
        b = true;
    }else{
        b = false;
    }
        
    if(R_CL_Read==0){
        return b;
    }
    delayus(100);
    if(R_CL_Read==0){
        return b;
    }
    return ~b;
}

Uint8 judge_r_st(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    R_ST_Tris = 1;
    if(res & BIT2 ==0){
        b = true;
    }else{
        b = false;
    }
        
    if(R_ST_Read==0){
        return b;
    }
    delayus(100);
    if(R_ST_Read==0){
        return b;
    }
    return ~b;
}

Uint8 judge_r_esd(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    R_ESD_Tris = 1;
    if(res & BIT3 ==0){
        b = true;
    }else{
        b = false;
    }
        
    if(R_ESD_Read==0){
        return b;
    }
    delayus(100);
    if(R_ESD_Read==0){
        return b;
    }
    return ~b;
}

void remote_err(){
    _uintMenuCount = 0;
    _ucharMenuKey = 0;
    _ucharOpenKey = 0;
    _ucharCloseKey = 0;
    ir_open(); 
}

Uint8 remote_aux_open(){
    
    Uint16 res_aux,res_rl,res_tc;
    _Thread_Flag = 0x05;
    if(_Thread_Flag!=0x05){
        goto open_end;
    }
    Remote_Tris = 1;
    Nop();
    if(Remote_Read!=0){
        goto open_end;
    }
    delayus(100);
    if(Remote_Read!=0){
        goto open_end;
    }
    eedata_read(_AUXMSK,res_aux);
    if(res_aux & BIT4==0){
        goto open_end;
    }
    if(!judge_aux_open()){
        goto open_end;        
    }
    eedata_read(_Remote_Lock,res_rl);
    
    if(res_rl!=0x69){
        R_OP_Hold_Tris = 1;
        Nop();
        if(R_OP_Hold_Read==0){
            delayus(100);
            if(R_OP_Hold_Read==0){
                _StopTimer = 50;
                dis_open_lock();
                goto open_end;
            }         
        }
    }
    _StatusBack &= ~_OP_LockFlag;
    _DP_IDATA2 &= ~BIT4;
    open_phase1();
    if(_Back_Flag==0x55){
        goto open_end;
    }
    lcd_dis_clralarm();
    open_phase2();
    if(_Back_Flag==0x55){
        goto stop_end;
    }
    open_phase4();
    while(1){
        if(_Thread_Flag!=0x05){
            goto stop_end;
        }
        Remote_Tris = 1;
        Nop();
        if(Remote_Read!=0){
            goto stop_end;
        }
        delayus(100);
        if(Remote_Read!=0){
            goto stop_end;
        }
        if(res_aux & BIT4==0){
            goto stop_end;
        }
        if(res_aux & BIT5!=0){
            if(!judge_aux_open()){
                if(res_aux & BIT6==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }else if(judge_aux_close()){
                eedata_read(_TwoLinesCtrl,res_tc);
                if(res_tc!=0x69){
                    goto stop_end;
                }
            }
        }else {
            if(!judge_aux_open()){
                if(res_aux & BIT6==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }
        }
        if(res_rl!=0x69){
            R_OP_Hold_Tris = 1;
            Nop();
            if(R_OP_Hold_Read==0){
                delayus(100);
                if(R_OP_Hold_Read==0){
                    _StopTimer = 25;
                    dis_open_lock();
                    goto open_end;
                }         
            }
        }
        _StatusBack &= ~_OP_LockFlag;
        _DP_IDATA2 &= ~BIT4;
        open_phase3();
        if(_Back_Flag==0x55){
            goto stop_end;
        }      
    }
    
stop_end:
    forbid();
open_end:
    remote_err();
    return E_ERR;
}

Uint8 remote_aux_close(){
    
    Uint16 res_aux,res_rl,res_tc;
    _Thread_Flag = 0x06;
    if(_Thread_Flag!=0x06){
        goto close_end;
    }
    Remote_Tris = 1;
    Nop();
    if(Remote_Read!=0){
        goto close_end;
    }
    delayus(100);
    if(Remote_Read!=0){
        goto close_end;
    }
    eedata_read(_AUXMSK,res_aux);
    if(res_aux & BIT5==0){
        goto close_end;
    }
    if(!judge_aux_close()){
        goto close_end;        
    }
    eedata_read(_Remote_Lock,res_rl);
    
    if(res_rl!=0x69){
        R_CL_Hold_Tris = 1;
        Nop();
        if(R_CL_Hold_Read==0){
            delayus(100);
            if(R_CL_Hold_Read==0){
                _StopTimer = 50;
                dis_close_lock();
                goto close_end;
            }         
        }
    }
    _StatusBack &= ~_CL_LockFlag;
    _DP_IDATA2 &= ~BIT5;
    close_phase1();
    if(_Back_Flag==0x55){
        goto close_end;
    }
    lcd_dis_clralarm();
    close_phase2();
    if(_Back_Flag==0x55){
        goto stop_end;
    }
    close_phase4();
    while(1){
        if(_Thread_Flag!=0x06){
            goto stop_end;
        }
        Remote_Tris = 1;
        Nop();
        if(Remote_Read!=0){
            goto stop_end;
        }
        delayus(100);
        if(Remote_Read!=0){
            goto stop_end;
        }
        if(res_aux & BIT5==0){
            goto stop_end;
        }
        if(res_aux & BIT4!=0){
            if(!judge_aux_close()){
                if(res_aux & BIT6==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }else if(judge_aux_open()){
                eedata_read(_TwoLinesCtrl,res_tc);
                if(res_tc!=0x96){
                    goto stop_end;
                }
            }
        }else {
            if(!judge_aux_close()){
                if(res_aux & BIT6==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }
        }
        if(res_rl!=0x69){
            R_CL_Hold_Tris = 1;
            Nop();
            if(R_CL_Hold_Read==0){
                delayus(100);
                if(R_CL_Hold_Read==0){
                    _StopTimer = 25;
                    dis_close_lock();
                    goto close_end;
                }         
            }
        }
        _StatusBack &= ~_CL_LockFlag;
        _DP_IDATA2 &= ~BIT5;
        close_phase3();
        if(_Back_Flag==0x55){
            goto stop_end;
        }      
    }
    
stop_end:
    forbid();
close_end:
    remote_err();
    return E_ERR;
}

Uint8 remote_dp_position(){
    
}

Uint8 remote_dp_open(){
    
}

Uint8 remote_dp_close(){
    
}

Uint8 remote_dp_relay(){
    
}

Uint8 remote_dp_salos(){
    
}

Uint8 remote_dp(){
    
    Uint16 res;
    
    eedata_read(_Card,res);
    if((res==8)||(res==1)||(res==2)){
        if(_DP_PARA_FLAG!=0xa596){
            goto dp_end;
        }
        if(_DP_ACTION==0x08){
            _DP_IDATA2 |= BIT6;
            return remote_dp_position();
        }
        if(_DP_ACTION==0x02){
            _DP_IDATA2 &= ~BIT6;
            return remote_dp_open();
        }
        if(_DP_ACTION==0x01){
            _DP_IDATA2 &= ~BIT6;
            return remote_dp_close();
        }
        if(_DP_ACTION==0x04){
            _DP_IDATA2 &= ~BIT6;
            return remote_dp_relay();
        }
        /*
        if(_DP_ACTION==0x00){
            goto dp_end;
        }*/
        if(_DP_ACTION==0x55){
            _DP_IDATA2 &= ~BIT6;
            return remote_dp_salos();
        }
    }
dp_end:   
    remote_err();
    return E_ERR;
}


Uint8 remote_auto(){
    
}

Uint8 remote_man(){
    
    Uint16 res;
    eedata_read(_AUXMSK,res);
    if(res & BIT4==0){
        _strAlarmFlag &= ~_RmFlickFlag;
        if(res & BIT5==0){
            return remote_dp();
        }
        //open is forbit ,close is not
        if(!judge_aux_close()){
            return remote_dp();
        }else{
            _DP_IDATA2 &= ~BIT6;
            return remote_aux_close();
        } 
    }
    if(res & BIT5==0){
        //clsoe is forbit ,open is not
        _strAlarmFlag &= ~_RmFlickFlag;
        if(!judge_aux_open()){
            return remote_dp();
        }else{
            _DP_IDATA2 &= ~BIT6;
            return remote_aux_open();
        }    
    }
    //open and close are all permitted
    if(!judge_aux_open()){
        _strAlarmFlag &= ~_RmFlickFlag;
        if(!judge_aux_close()){
            return remote_dp();
        }else{
            _DP_IDATA2 &= ~BIT6;
            return remote_aux_close();
        }
    }
    if(!judge_aux_close()){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        return remote_aux_open();
    }
    //open and close signal exist the same time    
    eedata_read(_TwoLinesCtrl,res);
    if(res==0x69){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        return remote_aux_open();
    }
    if(res==0x96){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        return remote_aux_close();
    }
    delayms(500);
    if(!judge_aux_open()){
        _strAlarmFlag &= ~_RmFlickFlag;
        if(!judge_aux_close()){
            return remote_dp();
        }else{
            _DP_IDATA2 &= ~BIT6;
            return remote_aux_close();
        }
    }
    if(!judge_aux_close()){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        return remote_aux_open();
    }
    _strAlarmFlag |= _RmFlickFlag;
    monitor_release_dummy();
    lcd_dis_clralarm();
    lcd_dis_alarmrmflick();
    delayms(1000);
    remote_err();
    return E_ERR;
}

Uint8 remote_thread(){
    
    rush_monitor();
    if(_Menu!=0){
        remote_err();					
        return E_ERR;
    }
    R_CV_Tris = 1;
    Nop();
    if(R_CV_Read!=0){
        delayus(100);
        if(R_CV_Read!=0){
            _DP_IDATA2 |= BIT6;
            return remote_auto();
        }
    }
    return remote_man();
}

Uint8 button_remote_process(){

    if(_Rush_PlaceCount>=40){
        _Rush_PlaceCount = 0;
        lcd_dis_remote();
    }
    _DP_IDATA1 &= ~BIT5;
    _DP_IDATA1 |= BIT6;
    _strAlarmFlag &= ~_ButtonFlag;
    com_esd();
    if(_Back_Flag==0x55){
        esd_thread();
    }
    ir_close();
    if(remote_thread()==E_ERR)
        return E_ERR;
    return E_OK;
}