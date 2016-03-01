#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"

extern Uint16 _EEDATA(2) _FlowNum1;
extern Uint16 _EEDATA(2) _FlowNum2;

Uint8 flow_thread(){
    
    if(_ucharFlowKey==true){
        eedata_write(_FlowNum1,_Flow_Buf1);
        eedata_write(_FlowNum2,_Flow_Buf2);
    }else if(_ucharReadFlowKey!=true){
        return E_OK;
    }
    while(1){
        _ucharFlowBackKey = 0;
        _ucharFlowKey= 0;
        _ucharReadFlowKey = 0;
        lcd_dis_flow();
        while(1){
            if(_ucharReadFlowKey==true){
                break;
            }else if(_ucharFlowKey==true){
                eedata_write(_FlowNum1,_Flow_Buf1);
                eedata_write(_FlowNum2,_Flow_Buf2);
                break;
            }else if(_ucharFlowBackKey==true){
                return E_OK;
            }
            clr_wdt();
        }
    }
    
    
    return E_OK;
}
