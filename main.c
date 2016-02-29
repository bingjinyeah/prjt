/*
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2016?2?24?, ??12:58
 */

// DSPIC30F6014A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "eedata.h"
#include "lcd.h"
#include "flag.h"
#include "para.h"

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


extern void port_init();
extern void check_power();
extern void system_init();


void delayms(Uint16 num){
    Uint16 c=500;
    while(num--){
        while(c--){}
        c=500;
    }
}

void delayus(Uint16 num){  
    while(num--);
}

void main_power(){
    op_cl_port_init();
    if(_strAlarmFlag & _PowerDownFlag){
        process_power_down();
    }
    Code_Ctrl_Tris = 0;
    Nop();
    Code_Ctrl_Write = 0;
    _DP_IDATA2 &= 0x40;
    rush_status();
    relay_position_judge();
    rush_relay_main();
    dis_alarm();
    check_remote_aux();
    ir_init_dummy();
    enable_wdt();
    SET_CPU_IPL(3);	
    _StatusBack &= 0xff;
    _Length_Check_Flag = 0;
    _WriteEEPROMFlag = 0;
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
#ifdef TEST 
    LED_G_Tris = 0; // set port bit to be output
    LED_R_Tris = 0;
    // Timer3 setup
    T3CON = 0;
    _T3IF = 0;
    PR3 = 50000;
    TMR3 = 0;
    _T3IE = 1; // enable interrupts for timer 1
    _T3IP = 0x001; // set interrupt priority (lowest)
    T3CONbits.TON = 1;
    T3CONbits.TCKPS = 2;
    lcd_test(); 
    while(1){
        
        //LED_R_Write = 0;
        LED_G_Write = 0;
        delayms(500);
        //LED_R_Write = 1;
        LED_G_Write = 1;
        delayms(500);
        //lcd_dis_smallchar(0,4,_ucharTabR,0); 
    }
#else   
    cpu_init();
    port_init();
    check_power();
    system_init();
    para_init();
    while(1){
        main_power();
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
 #endif       
    return 0;
}
