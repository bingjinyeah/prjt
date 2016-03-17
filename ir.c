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

void __attribute__((interrupt,no_auto_psv)) _INT0Interrupt(void){
    delayus(100);
    IR_Tris = 1;
    Nop();
    if(IR_Read){
        _INT0IF = 0;
    }else{
        _uintIrSampleCount = 0;
        _uintIrSampleShr = 0;
        _uintIrRxdCount = 0;
        _uintIrRxdShr = 0;
        _INT0IE = 0;
        T3CONbits.TON = 0;
        TMR3 = 0;
        T3CONbits.TON = 1;
        _T3IF = 0;
        _T3IE = 1;
    }
}

void process_ir_flow(){
    if(_Flag_Flow_Rec!=true){
        if(_uintIrRxdBuf!=_conFlowCode){
            _Flag_Flow_Rec = 0;
            _Count_Flow_Rec = 0;
            _ucharFlowKey = 0;
            if(_uintIrRxdBuf!=_conReadFlowCode){
                if(_uintIrRxdBuf==_conBackCode){ 
                    _ucharFlowBackKey = true;
                }
            }else{
                _ucharReadFlowKey = true;
                
            }  
        }else{
            _Count_Flow_Rec = 0;
            _Flag_Flow_Rec = true;
        }
    }else{
        if(((_uintIrRxdBuf & 0x0f)>9)||((_uintIrRxdBuf & 0xf0)>0x90)){
            _Flag_Flow_Rec = 0;
            _Count_Flow_Rec = 0;
            _ucharFlowKey = 0;
        }else{
            if(_Count_Flow_Rec==0){
                _Flow_Buf1 = _uintIrRxdBuf<<8;
                _Count_Flow_Rec++;
            }else if(_Count_Flow_Rec==1){
                _Flow_Buf1 += _uintIrRxdBuf;
                _Count_Flow_Rec++;
            }else if(_Count_Flow_Rec==2){
                _Flow_Buf2 = _uintIrRxdBuf<<8;
                _Count_Flow_Rec++;
            }else if(_Count_Flow_Rec==3){
                _Flow_Buf2 += _uintIrRxdBuf;
                _Flag_Flow_Rec = 0;
                _Count_Flow_Rec = 0;
                _ucharFlowKey = true;
            }
        }
    }
    _uintIrFlag = false;
}

void process_ir_ident(){
    if(_Flag_Ident_Rec!=true){
        if(_uintIrRxdBuf!=_conIdentCode){
            _Flag_Ident_Rec = 0;
            _Count_Ident_Rec = 0;
            _ucharIdentKey = 0;
            switch(_uintIrRxdBuf){
                case _conCloseCode:
                    _ucharCloseKey = true;
                    break;
                case _conOpenCode:
                    _ucharOpenKey = true;
                    break;
                case _conAddCode:
                    _ucharAddKey = true;
                    _ucharKey = true;
                    _ucharMenuKey = true;
                    break;
                case _conSubCode:
                    _ucharSubKey = true;
                    _ucharKey = true;
                    _ucharMenuKey = true;
                    break;
                case _conConfCode:
                    _ucharConfKey = true;
                    _ucharKey = true;
                    _ucharMenuKey = true;
                    break;
                case _conDownCode:
                    _ucharDownKey = true;
                    _ucharKey = true;
                    _ucharMenuKey = true;
                    break;
                case _conBackCode:
                    _ucharBackKey = true;
                    _ucharKey = true;
                    _ucharMenuKey = true;
                    break;
                case _conReadIdentCode:
                    _ucharReadIdentKey = true; 
                    break;
            } 
        }else{
            _Count_Ident_Rec = 0;
            _Flag_Ident_Rec = true;
        }
    }else{
        if(((_uintIrRxdBuf & 0x0f)>9)||((_uintIrRxdBuf & 0xf0)>0x90)){
            _Flag_Ident_Rec = 0;
            _Count_Ident_Rec = 0;
            _ucharIdentKey = 0;
        }else{
            if(_Count_Ident_Rec==0){
                _Ident_Buf1 = _uintIrRxdBuf;
                _Count_Ident_Rec++;
            }else if(_Count_Ident_Rec==1){
                _Ident_Buf2 = _uintIrRxdBuf<<8;
                _Count_Ident_Rec++;
            }else if(_Count_Ident_Rec==2){
                _Ident_Buf2 += _uintIrRxdBuf;
                _Flag_Ident_Rec = 0;
                _Count_Ident_Rec = 0;
                _ucharIdentKey = true;
            }
        }
    }
    _uintIrFlag = false;
}

void ir_interrupt(){
    if(_uintIrFlag!=true){
        if(_uintIrRxdBuf==0xff){
            _uintIrFlow = false;
            _uintIrFlag = true;
        }else if(_uintIrRxdBuf==0xaa){
            _uintIrFlow = true;
            _uintIrFlag = true;
        }
    }else if(_uintIrFlow==true){
        process_ir_flow();
    }else{
        process_ir_ident();
    }
}

void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void){
    _T3IF = 0;
    if(_uintIrSampleCount>2){
        _uintIrSampleCount = 0;
        return;
    }
    IR_Tris = 1;
    Nop();
    if(IR_Read){
        _uintIrSampleShr++;
    }
    if(++_uintIrSampleCount!=3){
        return;
    }
    _uintIrRxdShr >>= 1;
    if(_uintIrSampleShr>1){
        _uintIrRxdShr |= 0x80;
    }
    _uintIrSampleShr = 0;
    if(_uintIrRxdCount==8){
        _uintIrRxdBuf = _uintIrRxdShr;
        ir_interrupt();
        _T3IE = 0;
        _INT0IF = 0;
        _INT0IE = 1;
    }else if((_uintIrRxdCount==0)&&(_uintIrRxdShr!=0)){
        _T3IE = 0;
        _INT0IF = 0;
        _INT0IE = 1;
    }else{
        _uintIrRxdCount++;
    }
    
}