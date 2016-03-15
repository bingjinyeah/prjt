/*
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2016?2?24?, ??12:58
 */

// DSPIC30F6014A Configuration Bit Settings

// 'C' source line config statements

#include "includes.h"

// FOSC
#pragma config FOSFPR = XT_PLL4         // Oscillator (XT w/PLL 4x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_1         // WDT Prescaler B (1:1)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_27         // Brown Out Voltage (2.7V)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)
// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF             // General Segment Code Protection (Enabled)


extern Uint8 button_stop_process();
extern Uint8 button_local_process();


void delayms(Uint16 num){
    Uint16 c=500;
    clr_wdt();
    while(num--){
        while(c--){}
        c=500;
        
    }
}

void delayus(Uint16 num){  
    while(num--);
}

void main_rush(){
    motor_run_stop();
    if(_strAlarmFlag & _PowerDownFlag){
        process_power_down();
    }
    code_ctrl_clr();
    _DP_IDATA2 &= 0x40;
    rush_status();
    relay_position_judge();
    rush_relay_main();
    lcd_dis_alarm();
    check_remote_aux();
    ir_init_dummy();
    enable_wdt();
    SET_CPU_IPL(3);	
    _StatusBack &= 0xff;
    _Length_Check_Flag = 0;
    //_WriteEEPROMFlag = 0;
    battery_manage();
    /*low power cost mode*/
    adc12_close();
    set_t1(200);
    T1Int_Flag = 0;
    clr_wdt();
}

void main_idle(){
       
    while(1){
        PowerInt_Flag = 0;
        disable_wdt();
        Idle();
        enable_wdt();
        if(T1Int_Flag==0x69){
            time_compensate();
            break;
        }else if(_ucharMenuKey==true){
            break;
        }else if(PowerInt_Flag!=0x69){
            break;
        }
    }
    clr_wdt();
    set_t1(_conT1Time);
}

Uint16 temp;
int main(void) { 
    cpu_init();
    port_init();
    check_power();
    system_init();
    para_init();
    while(1){
        main_rush();
        main_idle();
        XN_STOP_Tris = 1;
        Nop();
        if(XN_STOP_Read!=0){  
            delayus(100);
            if(XN_STOP_Read!=0){
                button_stop_process();
                continue;
            }
        }
        _uintMenuCount = 0;
        _Count_Ident_Key = 0;
        _uintIdentCount = 0;
        Remote_Tris = 1;
        Nop();
        if(Remote_Read==0){
            delayus(100);
            if(Remote_Read==0){
                button_remote_process();
                continue;
            }
        }
        Local_Tris = 1;
        Nop();
        if(Local_Read==0){  
            delayus(100);
            if(Local_Read==0){
                button_local_process();
                continue;
            }
        }
        //a button error exist as not in the three state 
        _strAlarmFlag |= _ButtonFlag;
        if(_Rush_PlaceCount>=40){
            _Rush_PlaceCount = 0;
            lcd_dis_stop();
        }
    }     
    return 0;
}
