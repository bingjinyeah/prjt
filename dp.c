#include "includes.h"


#define ACT_OPEN        0x55
#define ACT_CLOSE       0x66
#define ACT_POSITION    0x99
#define ACT_SALOS       0xaa


extern void remote_exit(void);

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


void check_dp_action1(Uint8 act){
    
    Uint16 res_aux;
    Uint8  thread,action;
    
    if(act==ACT_OPEN){
        thread = 0x09;
        action = 2;
    }else if(act==ACT_CLOSE){
        thread = 0x0a;
        action = 1;
    }else if(act==ACT_POSITION){
        thread = 0x0b;
        action = 8;
    }else if(act==ACT_SALOS){
        thread = 0x0c;
        action = 0x55;
    }else{
        goto action_end;
    }
    if(_Thread_Flag!=thread){
        goto action_end;
    }
    if(!in_remote()){
        goto action_end;
    }
    if(r_cv_read()){
        goto action_end;
    }
    eedata_read(_AUXMSK,res_aux);
    if((res_aux & BIT4)!=0){
        if(judge_aux_open()){
            goto action_end;
        }
    }
    if((res_aux & BIT5)!=0){
        if(judge_aux_close()){
            goto action_end;
        }
    }
    if(_DP_PARA_FLAG!=0xa596){
        goto action_end;
    }
    
    if((_DP_ACTION!=action)&&(_DP_ACTION!=0)){
        goto action_end;
    }
    
    _Back_Flag = false;
    return;
action_end:
    _Back_Flag = true;
    return;
}
void check_dp_action(Uint8 act){
    if(_DP_ACTION==0){
        _Back_Flag = true;
    }else{
        check_dp_action1(act);
    }
}

void remote_dp_open(){
    Uint16 res_card,res_rl,res_dc;
    
    _Thread_Flag = 0x09;
    check_dp_action(ACT_OPEN);
    if(_Back_Flag==true){
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
    eedata_read(_Card,res_card);
    while(1){
        
        if(res_card==8){
            eedata_read(_DPCtrl,res_dc);
            if(res_dc==ufalse){
                check_dp_action1(ACT_OPEN);
            }else{
                check_dp_action(ACT_OPEN);
            }
        }else{
            check_dp_action(ACT_OPEN);
        }
        if(_Back_Flag==true){
            goto stop_end;
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

void remote_dp_close(){
     Uint16 res_card,res_rl,res_dc;
    
    _Thread_Flag = 0x0a;
    check_dp_action(ACT_CLOSE);
    if(_Back_Flag==true){
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
    eedata_read(_Card,res_card);
    while(1){
        
        if(res_card==8){
            eedata_read(_DPCtrl,res_dc);
            if(res_dc==ufalse){
                check_dp_action1(ACT_CLOSE);
            }else{
                check_dp_action(ACT_CLOSE);
            }
        }else{
            check_dp_action(ACT_CLOSE);
        }
        if(_Back_Flag==true){
            goto stop_end;
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

void remote_dp_position(){
    
    Uint16 dbd,cll,opl,rml,sub,act_flag;
    
    _Thread_Flag = 0x0b;
    check_dp_action(ACT_POSITION);
    if(_Back_Flag==true){
        goto auto_end;
    }
    _DP_IDATA1 |= BIT6;
    alu_dp_code();
    dbd = alu_dbd();
    eedata_read(_L_OP_Limit,opl);
    eedata_read(_Remote_Lock,rml);
    eedata_read(_L_CL_Limit,cll);
    cll += dbd;
    opl -= dbd;
    if(_DP_Code>=opl){
        act_flag = 1;
    }else if(_DP_Code<=cll){
        act_flag = 2;        
    }else{
        if(_L_CodeVP <= _DP_Code){
            sub = _DP_Code-_L_CodeVP;
            if(sub<dbd){
                goto auto_end;
            }
            act_flag = 1;
        }else{
            sub = _L_CodeVP-_DP_Code;
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
        lcd_dis_clr_alarm();
        if(open_phase2()==E_ERR){
            goto stop_end;
        }
        open_phase4();
        _DP_DIAGR1 |= BIT3;
        while(1){
            check_dp_action(ACT_POSITION);
            if(_Back_Flag==true){
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
            alu_dp_code();
            if(_DP_Code<opl){
                if(_DP_Code<=_L_CodeVP){
                    goto stop_end;
                }
                sub = _DP_Code - _L_CodeVP;
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
        lcd_dis_clr_alarm();
        if(close_phase2()==E_ERR){
            goto stop_end;
        }
        close_phase4();
        _DP_DIAGR1 |= BIT3;
        while(1){
            check_dp_action(ACT_POSITION);
            if(_Back_Flag==true){
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
            alu_dp_code();
            if(_DP_Code>cll){
                if(_L_CodeVP<=_DP_Code){
                    goto stop_end;
                }
                sub = _L_CodeVP - _DP_Code;
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

void remote_dp_relay(){
    Uint16  rc;
    
    eedata_read(_RelayControl,rc);
    if(rc & BIT0){
        if(_DP_ACTPOS & BIT0){
            if(_DP_ACTPOS & BIT4){
                _DP_Sn_Flag[0] = true;               
            }else{
                _DP_Sn_Flag[0] = false;
            }
        }
    }
    if(rc & BIT1){
        if(_DP_ACTPOS & BIT1){
            if(_DP_ACTPOS & BIT5){
                _DP_Sn_Flag[1] = true;               
            }else{
                _DP_Sn_Flag[1] = false;
            }
        }
    }
    if(rc & BIT2){
        if(_DP_ACTPOS & BIT2){
            if(_DP_ACTPOS & BIT6){
                _DP_Sn_Flag[2] = true;               
            }else{
                _DP_Sn_Flag[2] = false;
            }
        }
    }
    if(rc & BIT3){
        if(_DP_ACTPOS & BIT3){
            if(_DP_ACTPOS & BIT7){
                _DP_Sn_Flag[3] = true;               
            }else{
                _DP_Sn_Flag[3] = false;
            }
        }
    }
    rush_relays();
    remote_exit();
}

void remote_dp_salos(){
    
    Uint16 dbd,cll,opl,rml,sub,act_flag,res_los,lpc;
    
    _Thread_Flag = 0x0c;
    check_dp_action(ACT_SALOS);
    if(_Back_Flag==true){
        goto los_end;
    }
    _DP_IDATA1 &= ~BIT4;
    lcd_dis_clr_alarm();
    lcd_dis_alarm_dpsalos();
    eedata_read(_POSALS,res_los);
    eedata_read(_L_OP_Limit,opl);
    eedata_read(_L_CL_Limit,cll);
    eedata_read(_LOSPOS_Code,lpc);
    eedata_read(_Remote_Lock,rml);
    if(res_los==0){
        goto los_end;
    }else if(res_los==1){
        _DP_Code = opl;
    }else if(res_los==3){
        _DP_Code = cll;
    }else if(res_los==7){
        _DP_Code = lpc;
    }
    dbd = alu_dbd();
    cll += dbd;
    opl -= dbd;
    if(_DP_Code>=opl){
        act_flag = 1;
    }else if(_DP_Code<=cll){
        act_flag = 2;        
    }else{
        if(_L_CodeVP <= _DP_Code){
            sub = _DP_Code-_L_CodeVP;
            if(sub<dbd){
                goto los_end;
            }
            act_flag = 1;
        }else{
            sub = _L_CodeVP-_DP_Code;
            if(sub<dbd){
                goto los_end;
            }
            act_flag = 2;
        }
    }
    if(act_flag==1){
        if(rml!=ufalse){
            if(!r_op_hold_read()){
                _StopTimer = 50;
                dis_open_lock();
                goto los_end;
            }
        }
        _StatusBack &= ~_OP_LockFlag;
        _DP_IDATA2 &= ~BIT4;
        if(open_phase1()==E_ERR){
            goto los_end;
        }  
        if(open_phase2()==E_ERR){
            goto stop_end;
        }
        open_phase4();
        while(1){
            check_dp_action(ACT_SALOS);
            if(_Back_Flag==true){
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
            if(_DP_Code<opl){
                if(_DP_Code<=_L_CodeVP){
                    goto stop_end;
                }
                sub = _DP_Code - _L_CodeVP;
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
                goto los_end;
            }
        }
        _StatusBack &= ~_CL_LockFlag;
        _DP_IDATA2 &= ~BIT5;
        if(close_phase1()==E_ERR){
            goto los_end;
        }
        if(close_phase2()==E_ERR){
            goto stop_end;
        }
        close_phase4();
        while(1){
            check_dp_action(ACT_SALOS);
            if(_Back_Flag==true){
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
            
            if(_DP_Code>cll){
                if(_L_CodeVP<=_DP_Code){
                    goto stop_end;
                }
                sub = _L_CodeVP - _DP_Code;
                if(sub<dbd){
                    goto stop_end;
                }
            }
        } 
    }
    
stop_end:   
    _DP_DIAGR1 &= ~BIT3;
    forbid();
los_end:    
    remote_exit();
}

void remote_dp(){
    
    Uint16 res;
    
    eedata_read(_Card,res);
    if((res==8)||(res==1)||(res==2)){
        if(_DP_PARA_FLAG!=0xa596){
            goto dp_end;
        }
        if(_DP_ACTION==0x08){
            _DP_IDATA2 |= BIT6;
            remote_dp_position();
            return;
        }
        if(_DP_ACTION==0x02){
            _DP_IDATA2 &= ~BIT6;
            remote_dp_open();
            return;
        }
        if(_DP_ACTION==0x01){
            _DP_IDATA2 &= ~BIT6;
            remote_dp_close();
            return;
        }
        if(_DP_ACTION==0x04){
            _DP_IDATA2 &= ~BIT6;
            remote_dp_relay();
            return;
        }
        /*
        if(_DP_ACTION==0x00){
            goto dp_end;
        }*/
        if(_DP_ACTION==0x55){
            _DP_IDATA2 &= ~BIT6;
            remote_dp_salos();
            return;
        }
    }
    
dp_end:   
    _DP_IDATA2 &= ~BIT6;
    remote_exit();
}
