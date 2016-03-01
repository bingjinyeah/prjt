#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"

void relay_position_judge(){
    
}

void rush_relays(){
    
}

void rush_relay_main(){
    
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
    
}