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
        _WriteEEPROMFlag = 0x55aa;
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
    Local_Tris = 1;
    Nop();
    if(Local_Read!=0){
        goto open_end;
    }
    delayus(100);
    if(Local_Read!=0){
        goto open_end;
    }
    if(ctrl!=IR_CONTROL){
        L_OP_Tris = 1;
        Nop();
        if(L_OP_Read!=0){
            goto open_end;
        }
        delayus(100);
        if(L_OP_Read!=0){
            goto open_end;
        }
    }
    eedata_read(_Local_Lock,res_ll);
    if(res_ll!=0x69){
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
        Local_Tris = 1;
        Nop();
        if(Local_Read!=0){
            delayus(100);
            if(Local_Read!=0){
                goto stop_end;
            }
        }
        if(ctrl!=IR_CONTROL){
            L_OP_Tris = 1;
            Nop();
            if(L_OP_Read!=0){   
                delayus(100);
                if(L_OP_Read!=0){
                    eedata_read(_LocalCtrl,res_lc);
                    if(res_lc!=0x69){
                        goto stop_end;
                    }
                }
            }
        }
        if(res_ll!=0x69){
            R_OP_Hold_Tris = 1;
            Nop();
            if(R_OP_Hold_Read==0){
                delayus(100);
                if(R_OP_Hold_Read==0){
                    _StopTimer = 25;
                    dis_open_lock();
                    goto stop_end;
                }         
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
    return ;
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
    Local_Tris = 1;
    Nop();
    if(Local_Read!=0){
        goto close_end;
    }
    delayus(100);
    if(Local_Read!=0){
        goto close_end;
    }
    if(ctrl!=IR_CONTROL){
        L_CL_Tris = 1;
        Nop();
        if(L_CL_Read!=0){
            goto close_end;
        }
        delayus(100);
        if(L_CL_Read!=0){
            goto close_end;
        }
    }
    eedata_read(_Local_Lock,res_ll);
    if(res_ll!=0x69){
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
        Local_Tris = 1;
        Nop();
        if(Local_Read!=0){
            delayus(100);
            if(Local_Read!=0){
                goto stop_end;
            }
        }
        if(ctrl!=IR_CONTROL){
            L_CL_Tris = 1;
            Nop();
            if(L_CL_Read!=0){   
                delayus(100);
                if(L_CL_Read!=0){
                    eedata_read(_LocalCtrl,res_lc);
                    if(res_lc!=0x69){
                        goto stop_end;
                    }
                }
            }
        }
        if(res_ll!=0x69){
            R_CL_Hold_Tris = 1;
            Nop();
            if(R_CL_Hold_Read==0){
                delayus(100);
                if(R_CL_Hold_Read==0){
                    _StopTimer = 25;
                    dis_close_lock();
                    goto stop_end;
                }         
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
    return;
}

void local_thread(){
    
    L_CL_Tris = 1;
    Nop();
    if(L_CL_Read==0){
        delayus(100);
        if(L_CL_Read==0){
            local_close(LC_CONTROL);
            return;
        }
    }
    
    L_OP_Tris = 1;
    Nop();
    if(L_OP_Read==0){
        delayus(100);
        if(L_OP_Read==0){
            local_open(LC_CONTROL);
            return;
        }
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

Uint8 button_local_process(){
    
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
    return E_OK;
    
}
