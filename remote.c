#include "includes.h"


void check_card(){
    Uint16 res;
    
    _TRISB11 = 1;
    _TRISB12 = 1;
    _TRISB13 = 1;
    _TRISB14 = 1;
    _TRISB15 = 1;
    delayms(1);
    res = PORTB;
    res = (res>>11)&0x1f;
    if(res!=0){
        delayus(100);
        res = PORTB;
        res = (res>>11)&0x1f;
        if(res==0){
            res = 0xaa;
        }
    }else{
        res = 0xaa;
    }
    eedata_write(_Card,res);
    if(res==8){
        dp_init0();
    }else if(res==2){
        eedata_write(_DPSLTO,1);
        dp_init0();
    }
}

void check_remote_aux(){
    if(judge_aux_open()){
        _DP_IDATA3 |= BIT6;
    }else{
        _DP_IDATA3 &= ~BIT6;
    }
    
    if(judge_aux_close()){
        _DP_IDATA3 |= BIT5;
    }else{
        _DP_IDATA3 &= ~BIT5;
    }
    
    if(judge_r_st()){
        _DP_IDATA3 |= BIT4;
    }else{
        _DP_IDATA3 &= ~BIT4;
    }
    
    if(judge_r_esd()){
        _DP_IDATA3 |= BIT7;
    }else{
        _DP_IDATA3 &= ~BIT7;
    }
    
}

Uint8 judge_aux_open(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    if((res & BIT0)==0){
        b = true;
    }else{
        b = false;
    }
        
    if(r_op_read()){
        return ~b;
    }
    return b;
}

Uint8 judge_aux_close(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    if((res & BIT1)==0){
        b = true;
    }else{
        b = false;
    }
    if(r_cl_read()){
        return ~b;
    }
    return b;
}

Uint8 judge_r_st(){
    Uint16 res;
    Uint8  b;
    eedata_read(_AUXMSK,res);
    if((res & BIT2)==0){
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
    if((res & BIT3)==0){
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

void remote_exit(){
    _uintMenuCount = 0;
    _ucharMenuKey = 0;
    _ucharOpenKey = 0;
    _ucharCloseKey = 0;
    ir_open(); 
}

void remote_aux_open(){
    
    Uint16 res_aux,res_rl,res_tc;
    _Thread_Flag = 0x05;
    if(_Thread_Flag!=0x05){
        goto open_end;
    }
    if(!in_remote()){
        goto open_end;
    }
    eedata_read(_AUXMSK,res_aux);
    if((res_aux & BIT4)==0){
        goto open_end;
    }
    if(!judge_aux_open()){
        goto open_end;        
    }
    eedata_read(_Remote_Lock,res_rl);
    
    if(res_rl!=ufalse){
        if(!r_op_hold_read()){
            _StopTimer = 50;
            dis_open_lock();
            goto open_end;
        }
    }
    _StatusBack &= ~_OP_LockFlag;
    _DP_IDATA2 &= ~BIT4;
    if(open_phase1()==E_ERR){
        goto open_end;
    }
    lcd_dis_clr_alarm();
    if(open_phase2()==E_ERR){
        goto stop_end;
    }
    open_phase4();
    while(1){
        if(_Thread_Flag!=0x05){
            goto stop_end;
        }
        if(!in_remote()){
            goto stop_end;
        }
        if((res_aux & BIT4)==0){
            goto stop_end;
        }
        if((res_aux & BIT5)!=0){
            if(!judge_aux_open()){
                if((res_aux & BIT6)==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }else if(judge_aux_close()){
                eedata_read(_TwoLinesCtrl,res_tc);
                if(res_tc!=TWOLINE_OPEN){
                    goto stop_end;
                }
            }
        }else {
            if(!judge_aux_open()){
                if((res_aux & BIT6)==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }
        }
        if(res_rl!=ufalse){
            if(!r_op_hold_read()){
                _StopTimer = 25;
                dis_open_lock();
                goto stop_end;
            }
        }
        _StatusBack &= ~_OP_LockFlag;
        _DP_IDATA2 &= ~BIT4;
        if(open_phase3()==E_ERR){
            goto stop_end;
        }      
    }
    
stop_end:
    forbid();
open_end:
    remote_exit();
}

void remote_aux_close(){
    
    Uint16 res_aux,res_rl,res_tc;
    _Thread_Flag = 0x06;
    if(_Thread_Flag!=0x06){
        goto close_end;
    }
    if(!in_remote()){
        goto close_end;
    }
    eedata_read(_AUXMSK,res_aux);
    if((res_aux & BIT5)==0){
        goto close_end;
    }
    if(!judge_aux_close()){
        goto close_end;        
    }
    eedata_read(_Remote_Lock,res_rl);
    
    if(res_rl!=ufalse){
        if(!r_cl_hold_read()){
            _StopTimer = 50;
            dis_close_lock();
            goto close_end;
        }
    }
    _StatusBack &= ~_CL_LockFlag;
    _DP_IDATA2 &= ~BIT5;
    if(close_phase1()==E_ERR){
        goto close_end;
    }
    lcd_dis_clr_alarm();
    if(close_phase2()==E_ERR){
        goto stop_end;
    }
    close_phase4();
    while(1){
        if(_Thread_Flag!=0x06){
            goto stop_end;
        }
        if(!in_remote()){
            goto stop_end;
        }
        if((res_aux & BIT5)==0){
            goto stop_end;
        }
        if((res_aux & BIT4)!=0){
            if(!judge_aux_close()){
                if((res_aux & BIT6)==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }else if(judge_aux_open()){
                eedata_read(_TwoLinesCtrl,res_tc);
                if(res_tc!=TWOLINE_CLOSE){
                    goto stop_end;
                }
            }
        }else {
            if(!judge_aux_close()){
                if((res_aux & BIT6)==0){
                    goto stop_end;
                }
                if(!judge_r_st()){
                    goto stop_end;
                }
            }
        }
        if(res_rl!=ufalse){
            if(!r_cl_hold_read()){
                _StopTimer = 25;
                dis_close_lock();
                goto stop_end;
            }
        }
        _StatusBack &= ~_CL_LockFlag;
        _DP_IDATA2 &= ~BIT5;
        if(close_phase3()==E_ERR){
            goto stop_end;
        }      
    }
    
stop_end:
    forbid();
close_end:
    remote_exit();
}

void remote_auto(){
    Uint16 dbd,cll,opl,rml,sub,act_flag;
    
    _Thread_Flag = 0x07;
    if(_Thread_Flag!=0x07){
        goto auto_end;
    }
    if(!in_remote()){
        goto auto_end;
    }
    if(!r_cv_read()){
        goto auto_end;
    }
    
    alu_ic_code();
    if(_Back_Flag==true){
        goto auto_end;
    }
    dbd = alu_dbd();
    eedata_read(_L_OP_Limit,opl);
    eedata_read(_Remote_Lock,rml);
    eedata_read(_L_CL_Limit,cll);
    cll += dbd;
    opl -= dbd;
    if(_IC_Code>=opl){
        act_flag = 1;
    }else if(_IC_Code<=cll){
        act_flag = 2;        
    }else{
        if(_L_CodeVP <= _IC_Code){
            sub = _IC_Code-_L_CodeVP;
            if(sub<dbd){
                goto auto_end;
            }
            act_flag = 1;
        }else{
            sub = _L_CodeVP-_IC_Code;
            if(sub<dbd){
                goto auto_end;
            }
            act_flag = 2;
        }
    }
    if(act_flag==1){
        if(rml!=ufalse){
            if(!r_op_hold_read()){
                _StopTimer = 50;
                dis_open_lock();
                goto auto_end;
            }
        }
        _StatusBack &= ~_OP_LockFlag;
        _DP_IDATA2 &= ~BIT4;
        if(open_phase1()==E_ERR){
            goto auto_end;
        }
        if((_strAlarmFlag & _SignLostedFlag)==0){
            lcd_dis_clr_alarm();
        }
        if(open_phase2()==E_ERR){
            goto stop_end;
        }
        open_phase4();
        _DP_DIAGR1 |= BIT3;
        while(1){
            if(_Thread_Flag!=0x07){
                goto stop_end;
            }
            if(!in_remote()){
                goto stop_end;
            }
            if(!r_cv_read()){
                goto stop_end;
            }
            if(rml!=ufalse){
                if(!r_op_hold_read()){
                    _StopTimer = 25;
                    dis_open_lock();
                    goto stop_end;
                }
            }
            _StatusBack &= ~_OP_LockFlag;
            _DP_IDATA2 &= ~BIT4;
            if(open_phase3()==E_ERR){
                goto stop_end;
            }
            alu_ic_code();
         
            if(_Back_Flag==true){
                goto stop_end;
            }
            if(_IC_Code<opl){
                if(_IC_Code<=_L_CodeVP){
                    goto stop_end;
                }
                sub = _IC_Code - _L_CodeVP;
                if(sub<dbd){
                    goto stop_end;
                }
            }
        }
    }else if(act_flag==2){
        if(rml!=ufalse){
            if(!r_cl_hold_read()){
                _StopTimer = 50;
                dis_close_lock();
                goto auto_end;
            }
        }
        _StatusBack &= ~_CL_LockFlag;
        _DP_IDATA2 &= ~BIT5;
        if(close_phase1()==E_ERR){
            goto auto_end;
        }
        if((_strAlarmFlag & _SignLostedFlag)==0){
            lcd_dis_clr_alarm();
        }
        if(close_phase2()==E_ERR){
            goto stop_end;
        }
        close_phase4();
        _DP_DIAGR1 |= BIT3;
        while(1){
            if(_Thread_Flag!=0x07){
                goto stop_end;
            }
            if(!in_remote()){
                goto stop_end;
            }
            if(!r_cv_read()){
                goto stop_end;
            }
            if(rml!=ufalse){
                if(!r_cl_hold_read()){
                    _StopTimer = 25;
                    dis_close_lock();
                    goto stop_end;
                }
            }
            _StatusBack &= ~_CL_LockFlag;
            _DP_IDATA2 &= ~BIT5;
            if(close_phase3()==E_ERR){
                goto stop_end;
            }
            alu_ic_code();
            if(_Back_Flag==true){
                goto stop_end;
            }
            if(_IC_Code>cll){
                if(_L_CodeVP<=_IC_Code){
                    goto stop_end;
                }
                sub = _L_CodeVP - _IC_Code;
                if(sub<dbd){
                    goto stop_end;
                }
            }
        } 
    }
stop_end:   
    _DP_DIAGR1 &= ~BIT3;
    forbid();
auto_end:    
    remote_exit();
}

Uint8 remote_rm_flick(){
    if(!judge_aux_open()){
        _strAlarmFlag &= ~_RmFlickFlag;
        if(!judge_aux_close()){
            remote_dp();
            return E_OK;
        }else{
            _DP_IDATA2 &= ~BIT6;
            remote_aux_close();
            return E_OK;
        }
    }
    if(!judge_aux_close()){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        remote_aux_open();
        return E_OK;
    }
    
    return E_ERR;
}

void remote_man(){
    
    Uint16 res;
    eedata_read(_AUXMSK,res);
    if((res & BIT4)==0){
        _strAlarmFlag &= ~_RmFlickFlag;
        if((res & BIT5)==0){
            remote_dp();
            return;
        }
        //open is forbit ,close is not
        if(!judge_aux_close()){
            remote_dp();
            return;
        }else{
            _DP_IDATA2 &= ~BIT6;
            remote_aux_close();
            return;
        } 
    }
    if((res & BIT5)==0){
        //clsoe is forbit ,open is not
        _strAlarmFlag &= ~_RmFlickFlag;
        if(!judge_aux_open()){
            remote_dp();
            return;
        }else{
            _DP_IDATA2 &= ~BIT6;
            remote_aux_open();
            return;
        }    
    }
    //open and close are all permitted
    if(remote_rm_flick()==E_OK){
        return;
    }
    //open and close signal exist the same time    
    eedata_read(_TwoLinesCtrl,res);
    if(res==TWOLINE_OPEN){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        remote_aux_open();
        return;
    }
    if(res==TWOLINE_CLOSE){
        _strAlarmFlag &= ~_RmFlickFlag;
        _DP_IDATA2 &= ~BIT6;
        remote_aux_close();
        return;
    }
    delayms(500);
    if(remote_rm_flick()==E_OK){
        return;
    }
    _strAlarmFlag |= _RmFlickFlag;
    monitor_release_dummy();
    lcd_dis_clr_alarm();
    lcd_dis_alarm_rmflick();
    delays(1);
    remote_exit();
}

void remote_thread(){
    
    rush_monitor();
    if(_Menu!=0){
        remote_exit();					
        return;
    }
    if(r_cv_read()){
        _DP_IDATA2 |= BIT6;
        remote_auto();
    }else{
        remote_man();
    }
}

void button_remote_process(){

    if(_Rush_PlaceCount>=40){
        _Rush_PlaceCount = 0;
        lcd_dis_remote();
    }
    _DP_IDATA1 &= ~BIT5;
    _DP_IDATA1 |= BIT6;
    _strAlarmFlag &= ~_ButtonFlag;
    if(com_esd()){
        esd_thread();
    }
    ir_close();
    remote_thread();
}