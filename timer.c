#include "includes.h"

void set_oscconl(Uint8 num){
    SYS_ENTER_CRI;
    OSCCONL = 0x46;
    OSCCONL = 0x57;
    OSCCONL = num;
    SYS_EXIT_CRI;
}

void set_t1(Uint16 num){
    
    T1CON = 0;
    TMR1 = 0;
    PR1 = num * 33;
    T1CON = 2;
    T1CONbits.TON = 1;
}

void t1_init(Uint16 num){
    set_oscconl(2);
    _T1IE = 0;
    _T1IP = 4;
    set_t1(num);
    _T1IF = 0;
    _T1IE = 1;
}

void t1_init_dummy(){
    set_oscconl(2);
    _T1IP = 4;
    T1CONbits.TON = 1;
    _T1IE = 1;    
}

void t1_close(){
    T1CONbits.TON = 0;
    _T1IE = 0; 
}

void t4_init(Uint16 num){
    set_oscconl(2);
    _T4IE = 0;
    _T4IP = 4;
    T4CON = 0;
    TMR4 = 0;
    T4CONbits.TCKPS0 = 1;
    PR4 = 573;
    T4CONbits.TON = 1;
    _T4IF = 0;
    _T4IE = 1;
}

void time_compensate(){
    _Bat_3DayCount0+=40;
    if(_Bat_3DayCount0>12000){
        _Bat_3DayCount0 -= 12000;
        _Bat_3DayCount1++;
        if(_Bat_3DayCount1>4320){
            _Bat_3DayCount1 = 0;
            _Bat_3DayFlag = 0xa596;
        }
    }
    _Bat_30MinCount0+=40;
    if(_Bat_30MinCount0>12000){
        _Bat_30MinCount0 -= 12000;
        _Bat_30MinCount1++;
        if(_Bat_30MinCount1>30){
            _Bat_30MinCount1 = 0;
            _Bat_30MinFlag = 0xa596;
        }
    }
    _Bat_10MinCount0+=40;
    if(_Bat_10MinCount0>12000){
        _Bat_10MinCount0 -= 12000;
        _Bat_10MinCount1++;
        if(_Bat_10MinCount1>10){
            _Bat_10MinCount1 = 0;
            _Bat_10MinFlag = 0xa596;
        }
    }
    if(_ChargeupFlag==0x55){
        _Bat_1MinCount+=40;
    }
    _Sn_Count[0] = 5;
    _Sn_Count[1] = 5;
    _Sn_Count[2] = 5;
    _Sn_Count[3] = 5;
}



void __attribute__((interrupt,no_auto_psv)) _T1Interrupt(void){
    
    _T1IF = 0;
    T1Int_Flag = 0x69;
    _RushCount++;
    _Rush_PlaceCount++;
    _Rush_AlarmCount++;
    _Count5M++;
    if(_BytePowerDown==0x55){
        return;
    }
    _RushRuning++;                
	_VPCount++;  				
	_uintIdentCount++;  
	_uintMenuCount++;  			
	_JamCount++;  				
	_MoveCount++;  				
    _DisInitCount++;                
    _L_OP_Count++; 
    adc12_on();
    _Sn_Count[0]++;
    if(_Sn_Count[0]>3){
        E_S1A_Tris = 0;
        Nop();
        E_S1A_Write = 0;
        E_S1B_Tris = 0;
        Nop();
        E_S1B_Write = 0; 
    }
    _Sn_Count[1]++;
    if(_Sn_Count[1]>3){
        E_S2A_Tris = 0;
        Nop();
        E_S2A_Write = 0;
        E_S2B_Tris = 0;
        Nop();
        E_S2B_Write = 0; 
    }
    _Sn_Count[2]++;
    if(_Sn_Count[2]>3){
        E_S3A_Tris = 0;
        Nop();
        E_S3A_Write = 0;
        E_S3B_Tris = 0;
        Nop();
        E_S3B_Write = 0; 
    }
    _Sn_Count[3]++;
    if(_Sn_Count[3]>3){
        E_S4A_Tris = 0;
        Nop();
        E_S4A_Write = 0;
        E_S4B_Tris = 0;
        Nop();
        E_S4B_Write = 0; 
    }
    _Count2S++;
    _Bat_3DayCount0++;  //5ms every tick,so uint is 5ms
    if(_Bat_3DayCount0>12000){
        _Bat_3DayCount0 = 0;
        _Bat_3DayCount1++;
        if(_Bat_3DayCount1>4320){
            _Bat_3DayCount1 = 0;
            _Bat_3DayFlag = 0xa596;
        }
    }
    _Bat_30MinCount0++;
    if(_Bat_30MinCount0>12000){
        _Bat_30MinCount0 = 0;
        _Bat_30MinCount1++;
        if(_Bat_30MinCount1>30){
            _Bat_30MinCount1 = 0;
            _Bat_30MinFlag = 0xa596;
        }
    }
    _Bat_10MinCount0++;
    if(_Bat_10MinCount0>12000){
        _Bat_10MinCount0 = 0;
        _Bat_10MinCount1++;
        if(_Bat_10MinCount1>10){
            _Bat_10MinCount1 = 0;
            _Bat_10MinFlag = 0xa596;
        }
    }
    if(_ChargeupFlag!=0x55){
        return;
    }
    _Bat_1MinCount++;
    if(_Bat_1MinCount>12000){
        _Bat_1MinCount = 0;
        if(_Bat_AlarmCount>20){
            _Bat_Alarm_Flag = 0xa596;
        }else{
            _Bat_Alarm_Flag = 0;
        }
        _Bat_AlarmCount = 0;
    }
}
//extern Uint16 _EEDATA(2) _POSALS;
//extern Uint16 _EEDATA(2) _DPSLTO;
void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void){
    
    _T4IF = 0;
    //push _RCOUNT;
    _DPSLTO_COUNT++;
    if(_DPSLTO_COUNT>87){
        _DPSLTO_COUNT = 0;
        _DPSLTO_COUNT1++;
        if(_DPSLTO_COUNT1==5){
            dp_init2();
        }
        if(_DP_PARA_FLAG==0xa596){
            Uint16 res;
            eedata_read(_POSALS,res);
            if((res&0x01)!=0){
                eedata_read(_DPSLTO,res);
                res *= 10;
                if(_DPSLTO_COUNT1>res){
                    _DPSLTO_COUNT1 = res;
                    _DPSLTO_COUNT = 87;
                    _DP_ACTION = 0x55;
                }
            }
        }
    }
    DP_RX_IDLE_COUNT++;
    DP_TX_IDLE_COUNT++;
    if(DP_RX_IDLE_COUNT>DP_FRAM_END){
        DP_RX_IDLE_COUNT = DP_FRAM_END;
        if(DP_RX_LENGTH!=0){
            dp_app_func();
            DP_RX_LENGTH = 0;
            DP_RX_ERR = 0;
        }
    }
    if(DP_TX_IDLE_COUNT>DP_FRAM_START){
        DP_TX_IDLE_COUNT = DP_FRAM_START;
        dp_tx_func();
    }
}
#ifdef TEST
void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void){
    // static variable for permanent storage duration
    static Uint8 portValue = 0;
    // write to port latch
    LED_R_Write = portValue++;
    // clear this interrupt condition
    _T3IF = 0;
}
#endif