#include "includes.h"

void spi2_init(){
    
    Uint16 res;
    
    _SPI2IE = 0;
    _SPISIDL = 0;
    _SPIROV = 0;
    res = SPI2BUF;
    SPI2CON = 0x420;
    _SPIEN = 1;
    DA_CS_Tris = 0;
    DA_LD_Tris = 0;
    BMQ_LD_Tris = 0;
    Nop();
    DA_CS_Write = 0;
    BMQ_LD_Write = 0;
    delayus(10);
    BMQ_LD_Write = 1;
    delayus(10);
    _CodeVP15 = SPI_DI_Read;
    SPI2BUF = 0;
    _SPI2IF = 0;
}

void spi2_init_dummy(){
    
    _SPI2IE = 0;
    _SPISIDL = 0;
    _SPIROV = 0;
    SPI2CON = 0x420;
    _SPIEN = 1;
    DA_CS_Tris = 0;
    DA_LD_Tris = 0;
}