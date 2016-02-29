#include <xc.h>
#include "basic.h"

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

void adc12_filter(){
    
}

void __attribute__((interrupt,no_auto_psv)) _ADCInterrupt(void){
    
    _ADIF = 0;
    _ASAM = 0;
    _ADON = 0;
    
}
