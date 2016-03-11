#include "includes.h"

void adc12_init(){
    
    ADPCFG = 0xffe3;
    ADCHS = 0;
    ADCSSL = 0x1c;
    ADCON1 = 0xe0;
    ADCON2 = 0x640c;
    ADCON3 = 0x280;
    _ADIF = 0;
    _ADIE = 1;
    _ADIP = 4;
    _ADON = 1;
    _ASAM = 1;
}

void adc12_init_dummy(){
    
    ADPCFG = 0xffe3;
    ADCHS = 0;
    ADCSSL = 0x1c;
    ADCON1 = 0xe0;
    ADCON2 = 0x640c;
    ADCON3 = 0x280;
    _ADIE = 1;
    _ADIP = 4;
}

void adc12_on(){
    _ADON = 1;
    _ASAM = 1;
}

void adc12_close(){
    
    _ADON = 0;
    _ASAM = 0;
}

void table_order(Uint16* src){
    Uint16 min,max,sum;
    Int16 i;
    
    if(src==NULL){
        return;
    }
    min = src[0];
    max = src[0];
    sum = src[0];
    for(i=1;i<10;i++){
        if(src[i]>max){
            max = src[i];
        }else if(src[i]<min){
            min = src[i];
        }
        sum += src[i];
    }
    src[10] = (sum-min-max)>>3;
}

void __attribute__((interrupt,no_auto_psv)) _ADCInterrupt(void){
    Int16 i;
    
    _ADIF = 0;
    _ASAM = 0;
    _ADON = 0;
    for(i=9;i>0;i--){
        _OPNJ[i] = _OPNJ[i-1]; 
        _CLNJ[i] = _CLNJ[i-1]; 
        _IC[i]   = _IC[i-1];
    }
    _OPNJ[0] = ADCBUF0;
    _CLNJ[0] = ADCBUF1;
    _IC[0]   = ADCBUF2;
    table_order(_IC);
    table_order(_CLNJ);
    table_order(_OPNJ);
}
