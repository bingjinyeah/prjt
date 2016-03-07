#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "flag.h"
#include "eedata.h"

//extern Uint16 _EEDATA(2) _ESD_ExceedSp;


Uint8 in_stop(){
    XN_STOP_Tris = 1;
    Nop();
    if(XN_STOP_Read){
        delayus(100);
        if(XN_STOP_Read){
            return true;
        }
    }
    return false;
}

Uint8 button_stop_process(){
    
    Uint16 res;
    
    if(_Rush_PlaceCount>=40){
        _Rush_PlaceCount = 0;
        lcd_dis_stop();
    }
    _DP_IDATA1 &= ~BIT5;
    _DP_IDATA1 &= ~BIT6;
    _DP_IDATA2 &= ~BIT6;
    _strAlarmFlag &= ~_ButtonFlag;
    _Thread_Flag = 0;
    _ucharOpenKey = 0;
    _ucharCloseKey = 0;
    
    eedata_read(_ESD_ExceedSp,res);
    if(res){
        if(com_esd()){
            esd_thread();
        }
    }
    flow_thread();
    ident_thread();
    if(_ucharMenuKey){
        menu_thread();
    }
    return E_ERR;
}
