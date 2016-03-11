#include "includes.h"

void esd_active(){
    _strAlarmFlag |= _ESDFlag;
    rush_relay_esd();
    monitor_release();
}

void esd_inactive(){
    _strAlarmFlag &= ~_ESDFlag;
    rush_relay_conesd();
}


Uint8 esd_time_stop(Uint16 action){
    Uint16 res;
    
    _StatusBack &= ~_RunOver;
    stop();
    _StatusBack |= _TimeStopFlag;
    _DP_IDATA2 |= BIT2;
    eedata_read(_StopTime,res);
    _StopTimer = 5*res;
    eedata_read(_ESD_ExceedSp,res);
    while(1){
        if(res==ufalse){
            if(in_stop()){
                return E_ERR;
            }
        }
        rush_status();
        relay_position_judge();
        rush_relay_main();
        delayms(200);
        if(--_StopTimer==0){
            if(action==ACTION_OP){
                if(judge_opdir_protect()){
                    return E_ERR;
                }
                open_phase2();
                return E_OK;
            }else if(action==ACTION_CL){
                if(judge_cldir_protect()){
                    return E_ERR;
                }
                close_phase2();
                return E_OK;
            }
        }
    }
    return E_OK;
}

Uint8 com_esd(){
    Uint16 res;
    
    eedata_read(_AUXMSK,res);
    if(res & BIT7){
        if(judge_r_esd()){
            esd_active();
            return true;
        }
    }
    eedata_read(_Card,res);
    if((res==8)||(res==2)){
        if((_DP_PARA_FLAG==0xa596)&&(_DP_ACTION==3)){
            esd_active();
            return true;
        }
    }
    esd_inactive();
    return false;
}

void esd_op_thread(){
    Uint16 res;
    Uint16 res_eh,res_et,res_ep;
    
    if(_strAlarmFlag & _OTFlag){
        lcd_dis_clr_alarm();
        lcd_dis_alarm_opovertor();
        goto op_end;
    }
    if(!judge_esd_exceedlock(50,ACTION_OP)){
        goto op_end;
    }
    if(judge_opdir_protect()){
        goto op_end;
    }
    if(open_phase2()==E_ERR){
        goto stop_end;
    }
    open_phase4();
    lcd_dis_clr_alarm();
    lcd_dis_alarm_opesd();
    eedata_read(_ESD_ExceedTime,res_et);
    eedata_read(_ESD_ExceedHot,res_eh);
    eedata_read(_ESD_ExceedSp,res_ep);
    while(1){
        rush_status();
        check_remote_aux();
        relay_position_judge();
        rush_relay_main();
        if(_L_CodeVP>(65535-100)){
            _strAlarmFlag |= _VPOver;
            _DP_DIAGR1 |= BIT6;
            goto stop_end;
        }
        _strAlarmFlag &= ~_VPOver;
        _DP_DIAGR1 &= ~BIT6;
        if(judge_open_dir()==E_ERR){
            goto stop_end;
        }
        if(_strAlarmFlag & _PowerDownFlag){
            goto stop_end;
        }
        if(_strAlarmFlag & _PhaseLostedFlag){
            goto stop_end;
        }
        if(!com_esd()){
            goto stop_end;
        }
        if(res_eh==ufalse){
            if(check_hot()){
                goto stop_end;
            }
        }
        if(judge_optor_protect()){
            goto stop_end;
        }
        if(!judge_esd_exceedlock(25,ACTION_OP)){
            goto stop_end;
        }
        if(judge_opdir_protect()){
            goto stop_end;
        }
        if(res_ep==ufalse){
            if(in_stop()){
                goto stop_end;                }
        }
        if((_StatusBack & _OpeningFlag)==0){
            goto stop_end;
        }
        if(res_et==utrue){
            continue;
        }
        eedata_read(_Interim_Ctrl,res);
        if(res==0x69){
            eedata_read(_Start_Pos,res);
            if(_VPPercent<res){
                continue;
            }
            if((_StatusBack&_RunOver)==0){
                eedata_read(_MoveTime,res);
                res *= 200;
                if(_MoveCount <= res){
                    continue;
                }
            }  
        }else if(res==0x96){
            eedata_read(_Stop_Pos,res);
            if(_VPPercent>res){
                continue;
            }
            eedata_read(_MoveTime,res);
            res *= 200;
            if(_MoveCount <= res){
                continue;
            }
        } 
        if(esd_time_stop(ACTION_OP)==E_ERR){
            goto stop_end;
        }
    }
    
stop_end:
    forbid();
op_end:
    return;
}

void esd_cl_thread(){
    Uint16 res;
    Uint16 res_eh,res_et,res_ep;
    
    if(_strAlarmFlag & _CTFlag){
        lcd_dis_clr_alarm();
        lcd_dis_alarm_clovertor();
        goto cl_end;
    }
    if(!judge_esd_exceedlock(50,ACTION_CL)){
        goto cl_end;
    }
    if(judge_cldir_protect()){
        goto cl_end;
    }
    if(close_phase2()==E_ERR){
        goto stop_end;
    }
    close_phase4();
    lcd_dis_clr_alarm();
    lcd_dis_alarm_clesd();
    eedata_read(_ESD_ExceedTime,res_et);
    eedata_read(_ESD_ExceedHot,res_eh);
    eedata_read(_ESD_ExceedSp,res_ep);
    while(1){
        rush_status();
        check_remote_aux();
        relay_position_judge();
        rush_relay_main();
        if(_L_CodeVP<100){
            _strAlarmFlag |= _VPOver;
            _DP_DIAGR1 |= BIT6;
            goto stop_end;
        }
        _strAlarmFlag &= ~_VPOver;
        _DP_DIAGR1 &= ~BIT6;
        if(judge_close_dir()==E_ERR){
            goto stop_end;
        }
        if(_strAlarmFlag & _PowerDownFlag){
            goto stop_end;
        }
        if(_strAlarmFlag & _PhaseLostedFlag){
            goto stop_end;
        }
        if(!com_esd()){
            goto stop_end;
        }
        if(res_eh==ufalse){
            if(check_hot()){
                goto stop_end;
            }
        }
        if(judge_cltor_protect()){
            goto stop_end;
        }
        if(!judge_esd_exceedlock(25,ACTION_CL)){
            goto stop_end;
        }
        if(judge_cldir_protect()){
            goto stop_end;
        }
        if(res_ep==ufalse){
            if(in_stop()){
                goto stop_end;                }
        }
        if((_StatusBack & _ClosingFlag)==0){
            goto stop_end;
        }
        if(res_et==utrue){
            continue;
        }
        eedata_read(_Interim_Ctrl,res);
        if(res==0x96){
            eedata_read(_Start_Pos,res);
            if(_VPPercent>res){
                continue;
            }
            if((_StatusBack&_RunOver)==0){
                eedata_read(_MoveTime,res);
                res *= 200;
                if(_MoveCount <= res){
                    continue;
                }
            }  
        }else if(res==0x69){
            eedata_read(_Stop_Pos,res);
            if(_VPPercent<res){
                continue;
            }
            eedata_read(_MoveTime,res);
            res *= 200;
            if(_MoveCount <= res){
                continue;
            }
        } 
        if(esd_time_stop(ACTION_CL)==E_ERR){
            goto stop_end;
        }
    }
    
stop_end:
    forbid();
cl_end:
    return;
}

void esd_thread(){
    Uint16 res;
    
    _Thread_Flag = 8;
    if(_strAlarmFlag & _PowerDownFlag){
        goto esd_end;
    }
    if(_strAlarmFlag & _PhaseLostedFlag){
        goto esd_end;
    }
    if(_strAlarmFlag & _VPOver){
        goto esd_end;
    }
    if(!com_esd()){
        goto esd_end;
    }
    
    eedata_read(_ESD_ExceedHot,res);
    if(res==ufalse){
        if(check_hot()){
            goto esd_end;
        }
    }
    eedata_read(_ESD_ExceedSp,res);
    if(res==ufalse){
        if(in_stop()){
            goto esd_end;
        }
    }else{
        _INT0IE = 0;
        _T3IE = 0;
        _CNIE = 0;
    }
    
    eedata_read(_ESD_Action,res);
    if(res==ACTION_OP){
        esd_op_thread();
    }else if(res==ACTION_CL){
        esd_cl_thread();
    }
    
esd_end:
    _INT0IE = 1;
    _T3IE = 1;
    _CNIE = 1;
    _uintMenuCount = 0;
    _ucharOpenKey = 0;
    _ucharCloseKey = 0;
    _ucharStopKey = 0;
    
}
