#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"

Uint8 fb_fw_read(){
    FB_FW_Tris = 1;
    delayus(1000);
    if(FB_FW_Read){
        delayus(100);
        if(FB_FW_Read){
            return true;
        }
    }
    return false;
}

Uint8 fb_tq_read(){
    FB_TQ_Tris = 1;
    delayus(1000);
    if(FB_TQ_Read){
        delayus(100);
        if(FB_TQ_Read){
            return true;
        }
    }
    return false;
}
