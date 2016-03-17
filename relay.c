#include "includes.h"

void sx_status(Uint8 n){
    Uint16 res;
    
    if(n>3){
        return;
    }
    get_eedata_snstatus(n,&res);   
    if(res==ufalse){
        _RmReadS = 1;
    }else{
        _RmReadS = 0;
    }
}

void rush_relay_tor(Uint16 num, Uint16 flag){
    Uint16 res;
    Uint16 n;
    
    for(n=0;n<4;n++){
        get_eedata_snfun(n,&res);  
        //eedata_read(_Sn_Fun[n],res);
        if(res==num){
            if(_strAlarmFlag & flag){
                _Sn_Flag[n] = ufalse;
            }else{
                _Sn_Flag[n] = utrue;
            }
        }
    }
}



void rush_relay_midtor(){
    Uint16 res;
    Uint16 n;
    
    for(n=0;n<4;n++){
        get_eedata_snfun(n,&res);
        //eedata_read(_Sn_Fun[n],res);
        if(res==7){
            if(_strAlarmFlag & _CTFlag){
                eedata_read(_CL_OverTorPos,res);
                if(res){
                    _Sn_Flag[n] = ufalse;
                }else{
                    _Sn_Flag[n] = utrue;
                }
            }else if(_strAlarmFlag & _OTFlag){
                eedata_read(_OP_OverTorPos,res);
                if(res!=100){
                    _Sn_Flag[n] = ufalse;
                }else{
                    _Sn_Flag[n] = utrue;
                }
            }else{
                _Sn_Flag[n] = utrue;
            }
        }
    }  
}


void relay_position_judge(){
    Uint16 res;
    Uint16 n;
    
    for(n=0;n<4;n++){
        get_eedata_snfun(n,&res);   
        //eedata_read(_Sn_Fun[n],res);
        if((res==0)||(res>=0x0a)){
            if(_strAlarmFlag & _CSFlag){
                _Sn_Flag[n] = ufalse;
            }else{
                _Sn_Flag[n] = utrue;
            }
        }else if(res==1){
            if(_strAlarmFlag & _OSFlag){
                _Sn_Flag[n] = ufalse;
            }else{
                _Sn_Flag[n] = utrue;
            }
        }else if(res==0x0a){
            get_eedata_snpos(n,&res);
            //eedata_read(_Sn_Position[n],res);
            if(_VPPercent>res){
                _Sn_Flag[n] = ufalse;
            }else{
                _Sn_Flag[n] = utrue;
            }
        } 
    }
}

void relay_s1_close(){
    _Sn_Count[0] = 0;
    E_S1A_Tris = 0;
    Nop();
    E_S1A_Write = 1;
    E_S1B_Tris = 0;
    Nop();
    E_S1B_Write = 0;
    _DP_IDATA3 |= BIT0;
}

void relay_s1_open(){
    _Sn_Count[0] = 0;
    E_S1A_Tris = 0;
    Nop();
    E_S1A_Write = 0;
    E_S1B_Tris = 0;
    Nop();
    E_S1B_Write = 1;
    _DP_IDATA3 &= ~BIT0;
}

void relay_s2_close(){
    _Sn_Count[1] = 0;
    E_S2A_Tris = 0;
    Nop();
    E_S2A_Write = 1;
    E_S2B_Tris = 0;
    Nop();
    E_S2B_Write = 0;
    _DP_IDATA3 |= BIT1;
}

void relay_s2_open(){
    _Sn_Count[1] = 0;
    E_S2A_Tris = 0;
    Nop();
    E_S2A_Write = 0;
    E_S2B_Tris = 0;
    Nop();
    E_S2B_Write = 1;
    _DP_IDATA3 &= ~BIT1;
}

void relay_s3_close(){
    _Sn_Count[2] = 0;
    E_S3A_Tris = 0;
    Nop();
    E_S3A_Write = 1;
    E_S3B_Tris = 0;
    Nop();
    E_S3B_Write = 0;
    _DP_IDATA3 |= BIT2;
}

void relay_s3_open(){
    _Sn_Count[2] = 0;
    E_S3A_Tris = 0;
    Nop();
    E_S3A_Write = 0;
    E_S3B_Tris = 0;
    Nop();
    E_S3B_Write = 1;
    _DP_IDATA3 &= ~BIT2;
}

void relay_s4_close(){
    _Sn_Count[3] = 0;
    E_S4A_Tris = 0;
    Nop();
    E_S4A_Write = 1;
    E_S4B_Tris = 0;
    Nop();
    E_S4B_Write = 0;
    _DP_IDATA3 |= BIT3;
}

void relay_s4_open(){
    _Sn_Count[3] = 0;
    E_S4A_Tris = 0;
    Nop();
    E_S4A_Write = 0;
    E_S4B_Tris = 0;
    Nop();
    E_S4B_Write = 1;
    _DP_IDATA3 &= ~BIT3;
}

void (*relay_open[])() = {
    relay_s1_open,
    relay_s2_open,
    relay_s3_open,
    relay_s4_open
};

void (*relay_close[])() = {
    relay_s1_close,
    relay_s2_close,
    relay_s3_close,
    relay_s4_close
};

void rush_relays(){
    Uint16 res;
    Uint16 b;
    Uint16 n;
    
    eedata_read(_RelayControl,res);
    for(n=0;n<4;n++){
        for(b=0x01;b!=0x10;b<<=1){
            if(res & b){
                if(_DP_Sn_PreFlag[n]==_DP_Sn_Flag[n]){
                    continue;
                }
                if(_DP_Sn_Flag[n]==utrue){
                    relay_close[n]();
                }else{
                    relay_open[n]();
                }  
            }else{
                if(_Sn_PreFlag[n]==_Sn_Flag[n]){
                    continue;
                }
                get_eedata_snstatus(n,&res);
                //eedata_read(_Sn_Status[n],res);
                if(_Sn_Flag[n]==ufalse){
                    if(res==ufalse){
                        relay_open[n]();
                    }else{
                        relay_close[n]();
                    }
                }else{
                    if(res==ufalse){
                        relay_close[n]();
                    }else{
                        relay_open[n]();
                    }
                }
                _Sn_PreFlag[n] = _Sn_Flag[n];
                _DP_Sn_PreFlag[n] = _DP_Sn_Flag[n];
            }
        }
    }
}

void rush_relay_main(){
    rush_relay_tor(5,_CTFlag);
    rush_relay_tor(6,_OTFlag);
    rush_relay_midtor();
    rush_relays();
    if(_strAlarmFlag & _CTFlag){
        TQ_CL_Tris = 0;
        Nop();
        TQ_CL_Write = 0;
    }else{
        TQ_CL_Tris = 0;
        Nop();
        TQ_CL_Write = 1;
    }
    if(_strAlarmFlag & _OTFlag){
        TQ_OP_Tris = 0;
        Nop();
        TQ_OP_Write = 0;
    }else{
        TQ_OP_Tris = 0;
        Nop();
        TQ_OP_Write = 1;
    }
}

void rush_relay_mov(Uint16 n, Uint16 logic, Uint16 num){
    Uint16 res;
    
    get_eedata_snfun(n,&res);
    //eedata_read(_Sn_Fun[n-1],res);
    if(res==num){
        _Sn_Flag[n-1] = logic;
    }
}

void rush_relay_close(){
    rush_relay_mov(1,ufalse,3);
    rush_relay_mov(2,ufalse,3);
    rush_relay_mov(3,ufalse,3);
    rush_relay_mov(4,ufalse,3);
    rush_relays();
}

void rush_relay_concl(){
    rush_relay_mov(1,utrue,3);
    rush_relay_mov(2,utrue,3);
    rush_relay_mov(3,utrue,3);
    rush_relay_mov(4,utrue,3);
}

void rush_relay_open(){
    rush_relay_mov(1,ufalse,2);
    rush_relay_mov(2,ufalse,2);
    rush_relay_mov(3,ufalse,2);
    rush_relay_mov(4,ufalse,2);
    rush_relays();
}

void rush_relay_conop(){
    rush_relay_mov(1,utrue,2);
    rush_relay_mov(2,utrue,2);
    rush_relay_mov(3,utrue,2);
    rush_relay_mov(4,utrue,2);
}

void rush_relay_run(){
    rush_relay_mov(1,ufalse,4);
    rush_relay_mov(2,ufalse,4);
    rush_relay_mov(3,ufalse,4);
    rush_relay_mov(4,ufalse,4);
    rush_relays();
}

void rush_relay_conrun(){
    rush_relay_mov(1,utrue,4);
    rush_relay_mov(2,utrue,4);
    rush_relay_mov(3,utrue,4);
    rush_relay_mov(4,utrue,4);
}

void rush_relay_jam(){
    rush_relay_mov(1,ufalse,8);
    rush_relay_mov(2,ufalse,8);
    rush_relay_mov(3,ufalse,8);
    rush_relay_mov(4,ufalse,8);
    rush_relays();
}

void rush_relay_conjam(){
    rush_relay_mov(1,utrue,8);
    rush_relay_mov(2,utrue,8);
    rush_relay_mov(3,utrue,8);
    rush_relay_mov(4,utrue,8);
}

void rush_relay_esd(){
    rush_relay_mov(1,ufalse,9);
    rush_relay_mov(2,ufalse,9);
    rush_relay_mov(3,ufalse,9);
    rush_relay_mov(4,ufalse,9);
    rush_relays();
}

void rush_relay_conesd(){
    rush_relay_mov(1,utrue,9);
    rush_relay_mov(2,utrue,9);
    rush_relay_mov(3,utrue,9);
    rush_relay_mov(4,utrue,9);
}


void monitor_release_dummy(){
    E_S5_Tris = 0;
    Nop();
    E_S5_Write = 1;
}

void monitor_release(){
    
    _DP_IDATA1 &= ~BIT4;
    if(_DP_ACTION!=3){
        _DP_ACTION = 0;
    }
    monitor_release_dummy();
}

void rush_monitor(){
    Uint16 res;
    
    if(_strAlarmFlag & _PowerDownFlag){
        goto mnt_end;
    }
    if(_strAlarmFlag & _PhaseLostedFlag){
        goto mnt_end;
    }
    if(_strAlarmFlag & _Hot){
        goto mnt_end;
    }
    if(_strAlarmFlag & _RmFlickFlag){
        goto mnt_end;
    }
    if(_strAlarmFlag & _ESDFlag){
        goto mnt_end;
    }
    if(_strAlarmFlag & _SignLostedFlag){
        goto mnt_end;
    }
    eedata_read(_Monitor_With_OverTorque,res);
    if(res==utrue){
        if(_strAlarmFlag & _CTFlag){
            goto mnt_end;
        }
        if(_strAlarmFlag & _OTFlag){
            goto mnt_end;
        }
    }
    eedata_read(_Monitor_With_Remote,res);
    if(res==utrue){
        if((_DP_IDATA1 & BIT6)==0){
            goto mnt_end;
        }
    }
    E_S5_Tris = 0;
    Nop();
    E_S5_Write = 0;
    _DP_IDATA1 |= BIT4;
    return;
mnt_end:
    E_S5_Tris = 0;
    Nop();
    E_S5_Write = 1;
    _DP_IDATA1 &= ~BIT4;
    return; 
}
