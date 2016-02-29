#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "eedata.h"
#include "flag.h"

extern Uint16 _EEDATA(2) _IdentNum1;
extern Uint16 _EEDATA(2) _IdentNum2;

Uint8 ident_read(){
    
    _ucharKey = 0;
    _Count_Ident_Key = 0;
    _ucharIdentKey = 0;
    _ucharReadIdentKey = 0;
    lcd_dis_ident();
    while(1){
        Local_Tris = 1;
        Nop();
        if(Local_Read==0){
            delayus(100);
            if(Local_Read==0){
                return E_ERR;
            }
        }
        Remote_Tris = 1;
        Nop();
        if(Remote_Read==0){
            delayus(100);
            if(Remote_Read==0){
                return E_ERR;
            }
        }
        L_CL_Tris = 1;
        Nop();
        if(L_CL_Read==0){
            delayus(100);
            if(L_CL_Read==0){
                return E_ERR;
            }
        }
        /*
        if(_ucharMenuKey==true){
            _ucharMenuKey = 0;
            _ucharReadIdentKey = 0;
            return E_ERR;
        }*/
        if(_ucharReadIdentKey==true){
            //_ucharMenuKey = 0;
            _ucharReadIdentKey = 0;
            return E_ERR;
        }    
        if(_ucharIdentKey==true){
            return E_OK;
        }
        if(_uintMenuCount>12000){
            return E_ERR;
        }
        check_remote_aux();
        if(_strAlarmFlag & _PowerDownFlag){
            process_power_down();
            return E_ERR;
        }else{
            menu_idle();
        }
        if(_VPCount>=5){
            _VPCount = 0;
            _SPI2_DA = false;
            get_code_vp();
            _SPI2_DA = true;
            get_code_vp();
            _L_CodeVP = circle_to_line(_CodeVP);
        }
    }
    
    return E_ERR;
}

Uint8 ident_loop(){
 
    while(1){
        if(_ucharIdentKey==true){
            _uintMenuCount = 0;
            _uintIdentCount = 0;
            _ucharKey = 0;
            _ucharAddKey = 0;
            _ucharSubKey = 0;
            _ucharDownKey = 0;
            _ucharBackKey = 0;
            _ucharConfKey = 0;
            eedata_write(_IdentNum1,_Ident_Buf1);
            eedata_write(_IdentNum2,_Ident_Buf2);
        }else if(_ucharReadIdentKey!=true){
            return E_ERR;
        }
        if(ident_read()!=E_OK){
            return E_ERR;
        }
    }
    
    return E_OK;
}

Uint8 ident_thread(){
    
    Uint8 res = 1;
    L_CL_Tris = 1;
    Nop();
    if(L_CL_Read==0){
        delayus(100);
        if(L_CL_Read==0){
            _Count_Ident_Key = 0;
            _uintIdentCount = 0;
        }
    }
    L_OP_Tris = 1;
    Nop();
    if(L_OP_Read==0){
        delayus(100);
        if(L_OP_Read==0){
            res = 0;
            if(_Flag_Ident_Key==0x55){
                _Count_Ident_Key++;
                _Flag_Ident_Key = 0;
                _uintIdentCount = 0; 
                if(_Count_Ident_Key>=3){
                    _ucharReadIdentKey = true;                   
                }
            }
        }
    }
    if(res==1){
        if(_uintIdentCount<30){
            _Flag_Ident_Key = 0x55;
        }else{
            _Count_Ident_Key = 0;
            _uintIdentCount = 0;
            _Flag_Ident_Key = 0x55;
        }
    }
    ident_loop();
    if(_ucharMenuKey==true){
        menu_thread();
    }
    return;
}
