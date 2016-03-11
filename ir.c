#include "includes.h"

void ir_init(){
    
    _uintIrFlag = 0;
    _INT0IE = 0; 
    IR_Tris = 1;
    _INT0EP = 1;
    _INT0IP = 4;
    _uintIrRxdBuf = 0;
    _T3IE = 0;
    _T3IP = 4;
    T3CON = 0;
    PR3 = 2800;
    TMR3 = 0;
}

void ir_init_dummy(){

    IR_Tris = 1;
    _INT0EP = 1;
    _INT0IP = 4;
    _T3IP = 4;
    PR3 = 2800;
}

void ir_open(){
    _INT0IF = 0;
    _INT0IE = 1;
}

void ir_close(){
    _INT0IE = 0;
    _T3IE = 0;
    T3CONbits.TON = 0;
}
