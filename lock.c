#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "flag.h"
#include "eedata.h"
#include "action.h"
#include "port.h"

Uint8 judge_esd_exceedlock(Uint16 time, Uint16 action){
    Uint16 res;
    
    eedata_read(_ESD_ExceedLock,res);   
    if(res==utrue){
        goto end;
    }
    if(in_local()){
        eedata_read(_Local_Lock,res);
    }else if(in_remote()){
        eedata_read(_Remote_Lock,res);
    }else{
        res = ufalse;
    }
    if(res==ufalse){
        goto end;
    }
    if(!r_op_hold_read()){
        _StopTimer = time;
        if(action==ACTION_OP){
            dis_open_lock();
        }else if(action==ACTION_CL){
            dis_close_lock();
        }
        return false;
    }  
    
end:
    if(action==ACTION_OP){
        _StatusBack &= ~_OP_LockFlag;
        _DP_IDATA2 &= ~BIT4;
    }else if(action==ACTION_CL){
        _StatusBack &= ~_CL_LockFlag;
        _DP_IDATA2 &= ~BIT5;
    }
    
    return true;
}


