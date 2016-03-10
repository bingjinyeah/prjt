#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "lcd.h"
#include "wdt.h"

extern Uint16 _EEDATA(2) _FlowNum1;
extern Uint16 _EEDATA(2) _FlowNum2;

void flow_thread(){
    
    if(_ucharFlowKey){
        eedata_write(_FlowNum1,_Flow_Buf1);
        eedata_write(_FlowNum2,_Flow_Buf2);
    }else if(!_ucharReadFlowKey){
        return ;
    }
    while(1){
        _ucharFlowBackKey = false;
        _ucharFlowKey= false;
        _ucharReadFlowKey = false;
        lcd_dis_flow();
        while(1){
            if(_ucharReadFlowKey){
                break;
            }else if(_ucharFlowKey){
                eedata_write(_FlowNum1,_Flow_Buf1);
                eedata_write(_FlowNum2,_Flow_Buf2);
                break;
            }else if(_ucharFlowBackKey){
                return ;
            }
            clr_wdt();
        }
    }

    return ;
}
