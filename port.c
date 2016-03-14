#include "includes.h"

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

void led_g_r_set(Uint8 g, Uint8 r){
    
    LED_G_Tris = 0;
    LED_R_Tris = 0;
    LED_G_Write = g;
    LED_R_Write = r;
}

void motor_run_stop(){
    OP_Tris = 0;
    Nop();
    OP_Write = 0;
    OP_Write = 0;
    CL_Tris = 0;
    Nop();
    CL_Write = 0;
    CL_Write = 0;   
}

void motor_run_clock(){
    OP_Tris = 0;
    Nop();
    OP_Write = 0;
    OP_Write = 0;
    CL_Tris = 0;
    Nop();
    CL_Write = 1;
    CL_Write = 1;
}
void motor_run_antic(){
    OP_Tris = 0;
    Nop();
    OP_Write = 1;
    OP_Write = 1;
    CL_Tris = 0;
    Nop();
    CL_Write = 0;
    CL_Write = 0;
}

