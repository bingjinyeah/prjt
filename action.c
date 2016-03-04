#include <xc.h>
#include "basic.h"
#include "eedata.h"
#include "flag.h"
#include "para.h"
#include "lcd.h"
#include "pincfg.h"

void open_phase1(){
    
}

void open_phase2(){
    
}

void open_phase3(){
    
}

void open_phase4(){
    
}

void close_phase1(){
    
}

void close_phase2(){
    
}

void close_phase3(){
    
}

void close_phase4(){
    
}

void forbid(){
    
}

void dis_open_lock(){
    _StatusBack |= _OP_LockFlag;
    _DP_IDATA2 |= BIT4;
    lcd_dis_clr_alarm();
    lcd_dis_alarm_oplock();
    while(_StopTimer--){
        rush_status();
        relay_position_judge();
        rush_relay_main();
        delayms(20);
    }
}


void dis_close_lock(){
    _StatusBack |= _CL_LockFlag;
    _DP_IDATA2 |= BIT5;
    lcd_dis_clr_alarm();
    lcd_dis_alarm_cllock();
    while(_StopTimer--){
        rush_status();
        relay_position_judge();
        rush_relay_main();
        delayms(20);
    }
}