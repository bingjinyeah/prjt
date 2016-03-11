#include "includes.h"


Uint8 alarm_flag_read(Uint16 b){
    if(_strAlarmFlag & b){
        return true;
    }
    return false;
}

void alarm_flag_set(Uint16 b){
    _strAlarmFlag |= b;
}

void alarm_flag_clr(Uint16 b){
    _strAlarmFlag &= ~b;
}
