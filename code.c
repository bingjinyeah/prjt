#include "includes.h"

Uint16 gray_to_bin(Uint16 gray){
    Uint16 temp;
    Uint16 i;
    
    temp = gray;
    for(i=0;i<15;i++){
        temp>>=1;
        gray = gray ^ temp; 
    }
    return gray;
}

void get_code_vp(){
    Uint16 res;
    
    res = SPI2BUF;
    if(_SPIRBF){
        res = (res>>1)|(_CodeVP15<<15);
        _CodeVP = gray_to_bin(res);
    }
    DA_LD_Tris = 0;
    DA_CS_Tris = 0;
    BMQ_LD_Tris = 0;
    
    DA_LD_Write = 0;
    DA_CS_Write = 0;
    BMQ_LD_Write = 1;
    delayus(10);
    BMQ_LD_Write = 0;
    delayus(10);
    _CodeVP15 = SPI_DI_Read;
    if(_SPI2_DA==ufalse){
        _NJDA = ~(_NJDA^0x9000);
        res = _NJDA;
    }else{
         _VPDA = ~(_VPDA^0x1000);
         res = _VPDA;
    }
    DA_CS_Write = 1;
    SPI2BUF = res;
    _SPI2IF = 0;
#ifndef TEST
    while(_SPI2IF==0);
#endif
    delayus(42);
    DA_CS_Write = 0;
    delayus(10);
    DA_LD_Write = 1;
    delayus(42);
    DA_LD_Write = 0;
}

Uint16 circle_to_line(Uint16 vp){
    Uint16 cld,bs,lz;
    
    eedata_read(_CL_Dir,cld);
    eedata_read(_BIG_SHUCK ,bs);
    eedata_read(_L_Zero,lz);
    if(((cld==ufalse)&&(bs==0x69))||
       ((cld!=ufalse)&&(bs!=0x69))){
            return (vp - lz);
    }else{
        return (lz - vp);
    }  

}
/*
Uint8 set_logic(){
    Uint16 low,high;
    
    eedata_read(_IC_Low_VP,low);
    eedata_read(_IC_High_VP,high);
    if(high>low){
        return 0x69;
    }else{
        return 0xff;
    }
}
*/
Uint16 alu_dbd(){
    
    return 0;
}
void alu_ic_code(){
    Uint16 dl,dh;
    Uint16 lvp,hvp;
    Uint16 cll,opl;
    float res;
    
    _Back_Flag = 0;
    eedata_read(_IC_Low_VP,dl);
    eedata_read(_IC_High_VP,dh);
    if(dh<dl){
        hvp = dl;
        lvp = dh;
    }else{
        hvp = dh;
        lvp = dl;
    }
    eedata_read(_L_CL_Limit,cll);
    eedata_read(_L_OP_Limit,opl);
    eedata_read(_IC_Low,dl);
    eedata_read(_IC_High,dh);
    if(_IC[10]>=dh){
        res = hvp;
    }else if(_IC[10]>=dl){
        res = 1.0*(hvp-lvp)*(_IC[10]-dl)/(dh-dl)+lvp;
    }else if(_IC[10]>=dl/2){
        res = lvp;
    }else{
        lcd_dis_clr_alarm();
        lcd_dis_alarm_salos();
        _strAlarmFlag |= _SignLostedFlag;
        monitor_release_dummy();
        eedata_read(_POSALS,dl);
        if(dl==0x03){
            _IC_Code = cll;
        }else if(dl==0x01){
            _IC_Code = opl;
        }else if(dl==0x07){
            eedata_read(_LOSPOS,dl);
            _IC_Code = (opl-cll)*dl/100+cll;
        }else{
            _Back_Flag = 0x55;
        }
        return;
    }
    res = res*(opl-cll)/100 + cll;
    _strAlarmFlag &= ~_SignLostedFlag;
    _IC_Code = (Uint16)res;
    
}
/*
Uint8 set_dp_logic(){
    Uint16 low,high;
    
    eedata_read(_POSMIN,low);
    eedata_read(_POSMAX,high);
    if(high>low){
        return 0x69;
    }else{
        return 0xff;
    }
}
*/
void alu_dp_code(){
    Uint16 min,max;
    
    eedata_read(_POSMIN_Code,min);
    eedata_read(_POSMAX_Code,max);
    if(max>min){
        _DP_Code = _DP_ACTPOS*(max-min)/0xff+min;
    }else{
        _DP_Code = min - _DP_ACTPOS*(min-max)/0xff;
    }
}


Uint16 alu_dis_ic(){
    Uint16 low,high,res;
    
    eedata_read(_IC_Low,low);
    eedata_read(_IC_High,high);
    if(_IC[10]>=low){
        res = 160*(_IC[10]-low)/(high-low) + 40;
    }else{
        res = 40 - 160*(low-_IC[10])/(high-low);
    }
    return res;
}

Uint16 alu_dis_position_back(){
    
    Uint16 low,high,res;
    
    eedata_read(_Pos_BackL,low);
    eedata_read(_Pos_BackH,high);
    if(_Menu330Count>=low){
        res = 1600*(_Menu330Count-low)/(high-low) + 400;
    }else{
        res = 400 - 1600*(low-_Menu330Count)/(high-low);
    }
    return res;
}

Uint16 alu_dis_tor_back(){
    
    Uint16 low,high,res;
    
    eedata_read(_Tor_BackL,low);
    eedata_read(_Tor_BackH,high);
    if(_Menu331Count>=low){
        res = 1600*(_Menu331Count-low)/(high-low) + 400;
    }else{
        res = 400 - 1600*(low-_Menu331Count)/(high-low);
    }
    return res;
}

void cal_zero(Uint16 cll, Uint16 opl){
    
    Uint16 cld,bs,res;

    eedata_read(_CL_Dir,cld);
    eedata_read(_BIG_SHUCK ,bs);

    if(((cld==ufalse)&&(bs==0x69))||
       ((cld!=ufalse)&&(bs!=0x69))){  
        res = cll - opl;
        res>>=1;
        if((opl>=cll)&&(res<=cll)){
            
            res = cll - res;
        }else{
            res += opl;
        }      
    }else{
        res = opl - cll;
        res>>=1;
        if((cll>=opl)&&(res<=opl)){
                res = opl - res;
        }else{
            res += cll;
        }
    } 
    eedata_write(_L_Zero,res);
}

Uint8 cal_limit(Uint16 opl, Uint16 cll, Uint16 lz){
    Uint32  mul;
    Uint16  sub,res;
    
    
    cal_zero(cll,opl);
    opl = circle_to_line(opl);
    cll = circle_to_line(cll);
    sub = opl-cll;
    if(sub>(65535-512)){
        eedata_write(_L_Zero,lz);
        lcd_dis_clr_alarm();
        lcd_dis_alarm_lengtherror();
        delayms(400);
        lcd_dis_clr_alarm();
        delayms(200);
        lcd_dis_alarm_lengtherror();
        delayms(400);
        lcd_dis_clr_alarm();
        return E_ERR;
    }else{
        eedata_write(_Limit_Length,sub);
        eedata_write(_L_OP_Limit,opl);
        eedata_write(_L_CL_Limit,cll);
        eedata_read(_POSMIN,res);
        mul = res * sub;
        res = mul/100;
        res += cll;
        eedata_write(_POSMIN_Code,res);
        eedata_read(_POSMAX,res);
        mul = res * sub;
        res = mul/100;
        res += cll;
        eedata_write(_POSMAX_Code,res);
        
    }
    return E_OK;
}

void cal_limit_length(){
    Uint16  lz,opl,cll;
    
    if(((_SetOPLimitFlag==0x69)&&(_SetCLLimitFlag!=0x69))||
       ((_SetOPLimitFlag!=0x69)&&(_SetCLLimitFlag==0x69))){
        eedata_read(_L_Zero,lz);
        eedata_read(_OP_Limit,opl);
        eedata_read(_CL_Limit,cll);
        cal_limit(cll,opl,lz);
    }
        
    _SetOPLimitFlag = 0;
    _SetCLLimitFlag = 0;
    relay_position_judge();
    rush_relays();
}

Uint8 cal_length(Uint16 low, Uint16 high){    
    Uint16 cld,bs,res;
    
    if((_SetOPLimitFlag==0x69)||(_SetCLLimitFlag==0x69)){

        eedata_read(_CL_Dir,cld);
        eedata_read(_BIG_SHUCK ,bs);
        if(((cld==ufalse)&&(bs==0x69))||
           ((cld!=ufalse)&&(bs!=0x69))){   
            res = low - high;
        }else{
            res = high - low;
        } 
        if(_Length_Check_Flag==0x69){
            if(res<=200){
                _Length_Error_Flag = 0x69;
                return E_ERR;
            }
        }else{
            if((res>=200)&&(res<=400)){
                _Length_Check_Flag = 0x69;
            }
        }
    }
    _Length_Error_Flag = 0;
    return E_OK;
}