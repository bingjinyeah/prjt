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


Uint8 in_local(){
    Local_Tris = 1;
    Nop();
    if(Local_Read==0){
        delayus(100);
        if(Local_Read==0){
            return true;
        }
    }
    return false;
}


Uint8 in_remote(){
    Remote_Tris = 1;
    Nop();
    if(Remote_Read==0){
        delayus(100);
        if(Remote_Read==0){
            return true;
        }
    }
    return false;
}

Uint8 r_op_hold_read(){
    R_OP_Hold_Tris = 1;
    Nop();
    if(R_OP_Hold_Read){
        delayus(100);
        if(R_OP_Hold_Read){
            return true;
        }
    }
    return false;
}

Uint8 r_cl_hold_read(){
    R_CL_Hold_Tris = 1;
    Nop();
    if(R_CL_Hold_Read){
        delayus(100);
        if(R_CL_Hold_Read){
            return true;
        }
    }
    return false;
}
Uint8 l_op_read(){
    L_OP_Tris = 1;
    Nop();
    if(L_OP_Read==0){
        delayus(100);
        if(L_OP_Read==0){
            return true;
        }
    }
    return false;
}
Uint8 l_cl_read(){
    L_CL_Tris = 1;
    Nop();
    if(L_CL_Read==0){
        delayus(100);
        if(L_CL_Read==0){
            return true;
        }
    }
    return false;
}

Uint8 r_op_read(){
    R_OP_Tris = 1;
    Nop();
    if(R_OP_Read){
        delayus(100);
        if(R_OP_Read){
            return true;
        }
    }
    return false;
}

Uint8 r_cl_read(){
    R_CL_Tris = 1;
    Nop();
    if(R_CL_Read){
        delayus(100);
        if(R_CL_Read){
            return true;
        }
    }
    return false;
}

Uint8 r_st_read(){
    R_ST_Tris = 1;
    Nop();
    if(R_ST_Read){
        delayus(100);
        if(R_ST_Read){
            return true;
        }
    }
    return false;
}

Uint8 r_cv_read(){
    R_CV_Tris = 1;
    Nop();
    if(R_CV_Read){
        delayus(100);
        if(R_CV_Read){
            return true;
        }
    }
    return false;
}

Uint8 r_esd_read(){
    R_ESD_Tris = 1;
    Nop();
    if(R_ESD_Read){
        delayus(100);
        if(R_ESD_Read){
            return true;
        }
    }
    return false;
}


