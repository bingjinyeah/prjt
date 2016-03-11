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
    while(_SPI2IF==0);
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

Uint8 set_logic(){
    return 0x69;
}

Uint16 alu_dbd(){
    
    return 0;
}

void alu_nx(){
    
}

void alu_nnx(){
    
}

Uint8 set_dp_logic(){
    return 0x69;
}

void alu_dp_nx(){
    
}

void alu_dp_nnx(){
    
}

Uint16 alu_dis_ic(){
    
    return 0;
}

Uint16 alu_dis_position_back(){
    
    return 0;
}

Uint16 alu_dis_tor_back(){
    
    return 0;
}

void cal_zero(Uint16 cll, Uint16 opl){
    
    Uint16 res;
    
    res = (opl+cll)>>1;
    eedata_write(_L_Zero,res);
}

void cal_limit_length(){
    
}

Uint8 cal_length(Uint16 low, Uint16 high){
    
    return 0;
}