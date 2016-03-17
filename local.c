#include "includes.h"

#define IR_CONTROL      0x55
#define LC_CONTROL      0xAA

//extern Uint16 _EEDATA(2) _Local_Lock;
//extern Uint16 _EEDATA(2) _LocalCtrl;


void local_exit(){
    if(_Menu==0){
        _uintMenuCount = 0;
        _ucharOpenKey = 0;
        _ucharCloseKey = 0;
        _ucharStopKey = 0;
    }else{
        _ucharBackKey = 0;
        _ucharConfKey = 0;
        _ucharAddKey = 0;
        _ucharSubKey = 0;
        _ucharDownKey = 0;
        _ucharOpenKey = 0;
        _ucharCloseKey = 0;
        lcd_dis_alarm();
        //_VPCount = 5;
        //_WriteEEPROMFlag = 0x55aa;
        if(_Menu!=33){
            lcd_dis_menu_2();
        } 
    }
}

void local_open(Uint8 ctrl){
    
    Uint16 res_ll,res_lc;
    Uint8 thread;
    if(ctrl==IR_CONTROL){
        thread = 0x03;
    }else if(ctrl==LC_CONTROL){
        thread = 0x01;
    }else{
        return;
    }
    _Thread_Flag = thread;
    if(_Thread_Flag!=thread){
        goto open_end;
    }
    if(!in_local()){
        goto open_end;
    }
    if(ctrl!=IR_CONTROL){
        if(!l_op_read()){
            goto open_end;
        }
    }
    eedata_read(_Local_Lock,res_ll);
    if(res_ll!=ufalse){
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
        if(_Thread_Flag!=0x01){
            goto stop_end;
        }
        if(!in_local()){
            goto stop_end;
        }
        if(ctrl!=IR_CONTROL){
            if(!l_op_read()){
                eedata_read(_LocalCtrl,res_lc);
                if(res_lc!=ufalse){
                    goto stop_end;
                }
            }
        }
        if(res_ll!=ufalse){
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
    local_exit();
}

void local_close (Uint8 ctrl){
    
    Uint16 res_ll,res_lc;
    Uint8 thread;
    if(ctrl==IR_CONTROL){
        thread = 0x04;
    }else if(ctrl==LC_CONTROL){
        thread = 0x02;
    }else{
        return;
    }
    _Thread_Flag = thread;
    if(_Thread_Flag!=thread){
        goto close_end;
    }
    if(!in_local()){
        goto close_end;
    }
    if(ctrl!=IR_CONTROL){
        if(!l_op_read()){
            goto close_end;
        }
    }
    eedata_read(_Local_Lock,res_ll);
    if(res_ll!=ufalse){
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
        if(_Thread_Flag!=0x02){
            goto stop_end;
        }
        if(!in_local()){
            goto stop_end;
        }
        if(ctrl!=IR_CONTROL){
            if(!l_op_read()){
                eedata_read(_LocalCtrl,res_lc);
                if(res_lc!=ufalse){
                    goto stop_end;
                }
            }
            
        }
        if(res_ll!=ufalse){
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
    local_exit();
}

void local_thread(){
    
    if(l_cl_read()){
        local_close(LC_CONTROL);
        return;
    }
    if(l_op_read()){
        local_open(LC_CONTROL);
        return;
    }
    if(_ucharCloseKey){
        local_close(IR_CONTROL);
        return;
    }
    
    if(_ucharOpenKey){
        local_open(IR_CONTROL);
        return;
    }
}

void button_local_process(){
    
    if(_Rush_PlaceCount>=40){
        _Rush_PlaceCount = 0;
        lcd_dis_local();
    }
    _DP_IDATA1 |= BIT5;
    _DP_IDATA1 &= ~BIT6;
    _DP_IDATA2 &= ~BIT6;
    _strAlarmFlag &= ~_ButtonFlag;
    if(com_esd()){
        esd_thread();
    }
    if(_ucharMenuKey){
        menu_thread();
    }else{
        local_thread();
    }
}
