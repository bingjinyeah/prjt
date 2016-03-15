#include "includes.h"

void multi_phase_test(){
#ifdef  PHASE1
    if(phase_b_read()&&phase_c_read()){
        _BytePowerDown = 0;
        return;
    }
#endif
    _BytePowerDown = 0x55;
    _PowerIsOn = 0;
    return;
}

void check_powerdown(){
	
	_IC2Count = 0;
    while(1){
        delayms(2);
        if(!phase_a_read()){
            break;
        }
        if(++_IC2Count>=10){
            multi_phase_test();
            return;
        }
    }
    _IC2Count = 0;
    while(1){
        delayms(2);
        if(phase_a_read()){
            _BytePowerDown = 0;
            return;
        }
        if(++_IC2Count>=10){
            multi_phase_test();
            return;
        }
    }
}

void poweron_init(){
    Uint16 res;
#ifdef  PHASE1
    eedata_read(_PhaseOrder,res);
    if(res!=0xa596){
        eedata_write(_PhaseOrder,0xa596);
    }
#else
    for(res=1;res<4;res++){
        _uintPhase1[res] = 0x78;
        _uintPhase2[res] = 0x78;
        _uintPhase3[res] = 0x78;
        _IC2Buf_Phase[res-1] = 0;
        _IC3Buf_Phase[res-1] = 0;
        _IC4Buf_Phase[res-1] = 0;
    }
#endif
    _strAlarmFlag &= ~_PhaseLostedFlag;
    _strAlarmFlag &= ~_PowerDownFlag;
    _BytePowerDown = 0;
    _ByteRunningFlag = 0;
    _PhaseCount = 0;
    power_init();
}

void power_init(){
    
}

void rush_power(){
    
}

void check_power(){
	
	check_powerdown();
    if(_BytePowerDown==0x55){
		process_power_down();
	}	
}  

void process_power_down(){
    
}

Uint8 check_hot(){
    
    return false;
}
        