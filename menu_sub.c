#include "includes.h"
extern void (*menu_add_func[])();

void menu_sub_0(){
    
    if(--_Menu0Count0<0){
        _Menu0Count0 = 255;
    }
    lcd_dis_menu_0();
    return;
}

void menu_sub_2(){
    
    if(_uintCur>6){
        return;
    }
    switch(_uintCur){
        case 0:
        case 1:
        case 3:
        case 5:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 2:
            if(--_Menu2Count0<30){
                _Menu2Count0 = 100;
            }
            break;
        case 4:
            if(--_Menu2Count1<30){
                _Menu2Count1 = 100;
            }
            break;     
    }
    lcd_dis_menu_2();
    return;
}

void menu_sub_3(){
    Uint16 res;
    
    if(_uintCur>4){
        return;
    }
    switch(_uintCur){
        case 0:
             if(--_RmRead<0){
                _RmRead = 4;
            }
            break;
        case 1:
            if(--_RmRead<0){
                eedata_read(_Card,res);
                if(res==0xaa){
                    res = 1;
                }else if(res==16){
                    res = 2;
                }else{
                    res = 3;
                }
                _RmRead = res;
            }       
            break;
        case 2:
            if(--_RmRead<0){
                _RmRead = 3;
            }            
            break; 
        case 3:
            _RmRead = (_RmRead==0) ? 1:0;           
            break; 
    }
    lcd_dis_menu_3();
    return;
}

void menu_sub_5(){
    
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:
            if(--_Menu5Count0<0){
                _Menu5Count0 = 255;
            }
            break;     
    }
    lcd_dis_menu_5();
    return;
}

void menu_sub_8(){
#ifdef  LANGUAGE_EN
#else
    _RmReadS = (_RmReadS==0) ? 1:0;
    lcd_dis_menu_300();
#endif
    return;
}

void menu_sub_9(){
#ifndef LANGUAGE_EN
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
             if(--_Menu300ACount<1){
                _Menu300ACount = 99;
            }
            break;
        case 1:
            _RmReadS = (_RmReadS==0) ? 1:0;
            break;     
    }
    lcd_dis_menu_300a();
#endif
    return;
}

void menu_sub_10(){
    //menu_add_10();
    menu_add_func[11]();
}

void menu_sub_11(){
#ifdef LANGUAGE_EN
#endif
    return;
}

void menu_sub_12(){
    
    if(_uintCur>5){
        return;
    }
    switch(_uintCur){
        case 0:
            if(--_Menu312Count0<0){
                _Menu312Count0 = 99;
            }
            break;
        case 1:
            if(--_RmRead<0){
                _RmRead = 3;
            }
            break;
        case 2:
            if(--_Menu312Count1<0){
                _Menu312Count1 = 100;
            }
            break;
        case 3:
            if(--_Menu312Count2<0){
                _Menu312Count2 = 100;
            }
            break;
        case 4:   
        case 5:
            delayms(10);
            break; //in source code ,it is bra to menuloop,here dont do that
                    //in future, if it take errors, then check it 
    }
    lcd_dis_menu_312();
    return;
}

void menu_sub_13(){
    
    if(_uintCur>12){
        return;
    }
    switch(_uintCur){
        case 0:
            if(--_BusCount0<0){
                _BusCount0 = 126;
            }
            break;
        case 1:
            if(--_BusCount1<1){
                _BusCount1 = 255;
            }
            break;
        case 2:
            if(--_RmRead<0){
                _RmRead = 4;
            }
            break;
        case 3:
            if(--_RmRead<0){
                _RmRead = 2;
            }
            break;
        case 4:  
            if(--_BusCount2<0){
                _BusCount2 = 100;
            }
            break;
        case 5:
             if(--_BusCount3<0){
                _BusCount3 = 100;
            }
            break; 
        case 6:
             if(--_BusCount4<3){
                _BusCount4 = 99;
            }
            break; 
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 12:
            _RmRead = (_RmRead==ufalse) ? 0:ufalse;
            break;
    }
    lcd_dis_menu_profibus();
    
    return;
}

void menu_sub_14(){
    //menu_add_14();
    menu_add_func[15]();
}

void menu_sub_15(){
    //menu_add_15();
    menu_add_func[16]();
}

void menu_sub_16(){
    
    if(_uintCur>5){
        return;
    }
    switch(_uintCur){
        case 0:
            if(--_RmRead<0){
                _RmRead = 2;
            }
            break;
        case 1:   
        case 2:
        case 3:
        case 4:
        case 5:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
    }
    lcd_dis_menu_3210();
    
    return;
}

void menu_sub_17(){
    //menu_add_17();
    menu_add_func[18]();
}

void menu_sub_18(){
    
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            if(--_Menu3220Count0<0){
                _Menu3220Count0 = 100;
            }
            break;
        case 1:   
            if(--_Menu3220Count1<0){
                _Menu3220Count1 = 100;
            }
            break;
        case 2:
            if(--_Menu3220Count2<1){
                _Menu3220Count2 = 99;
            }
            break;
        case 3:
            if(--_Menu3220Count3<1){
                _Menu3220Count3 = 99;
            }
            break;
    }
    lcd_dis_menu_3220();
    
    return;
}

void menu_sub_19(){
    
    if(_uintCur>3){
        return;
    }
    switch(_uintCur){
        case 0:
            if(--_Menu3221Count0<0){
                _Menu3221Count0 = 100;
            }
            break;
        case 1:   
            if(--_Menu3221Count1<0){
                _Menu3221Count1 = 100;
            }
            break;
        case 2:
            if(--_Menu3221Count2<1){
                _Menu3221Count2 = 99;
            }
            break;
        case 3:
            if(--_Menu3221Count3<1){
                _Menu3221Count3 = 99;
            }
            break;
    }
    lcd_dis_menu_3221();
    
    return;
}

void menu_sub_20(){
    
    if(--_Menu323Count<0){
        _Menu323Count = 50;
    }
    lcd_dis_menu_323();
    return;
}

void menu_sub_45(){
    //menu_add_45();
    menu_add_func[45]();
}

void menu_sub_21(){
    
    if(--_Menu3230Count0<0){
        _Menu3230Count0 = 200;
    }
    lcd_dis_menu_3230();
    return;
}

void menu_sub_22(){
    Uint16 res;
    
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            if(_Menu22_ConfCount>=10){
                _Menu32301Count1 = 100;
                break;
            }
            if(_Menu22_ConfCount==1){
                res = 0;
            }else{
                get_eedata_oppos(_Menu22_ConfCount-2,&res);
            }/*
            switch(_Menu22_ConfCount-1){
                case 0:
                    res = 0;
                    break;
                case 1:
                    eedata_read(_OP_Position1,res);
                    break;
                case 2:
                    eedata_read(_OP_Position2,res);
                    break;
                case 3:
                    eedata_read(_OP_Position3,res);
                    break;
                case 4:
                    eedata_read(_OP_Position4,res);
                    break;
                case 5:
                    eedata_read(_OP_Position5,res);
                    break;
                case 6:
                    eedata_read(_OP_Position6,res);
                    break;
                case 7:
                    eedata_read(_OP_Position7,res);
                    break;
                case 8:
                    eedata_read(_OP_Position8,res);
                    break;
            }*/
            if(--_Menu32301Count1<=res){
                _Menu32301Count1 = 100;
            }
            break;
        case 1:   
            if(--_Menu32301Count2<0){
                _Menu32301Count2 = 100;
            }
            break;
    }
    lcd_dis_menu_32301();
    
    return;
}

void menu_sub_23(){
    Uint16 res;
    
    if(_uintCur>1){
        return;
    }
    switch(_uintCur){
        case 0:
            if(_Menu23_ConfCount>=10){
                _Menu32302Count1 = 0;
                break;
            }
            if(--_Menu32302Count1>=0){
                break;
            }
            if(_Menu23_ConfCount==1){
                res = 100;
            }else{
                get_eedata_clpos(_Menu23_ConfCount-2,&res);
            }/*
            switch(_Menu23_ConfCount-1){
                case 0:
                    res = 100;
                    break;
                case 1:
                    eedata_read(_CL_Position1,res);
                    break;
                case 2:
                    eedata_read(_CL_Position2,res);
                    break;
                case 3:
                    eedata_read(_CL_Position3,res);
                    break;
                case 4:
                    eedata_read(_CL_Position4,res);
                    break;
                case 5:
                    eedata_read(_CL_Position5,res);
                    break;
                case 6:
                    eedata_read(_CL_Position6,res);
                    break;
                case 7:
                    eedata_read(_CL_Position7,res);
                    break;
                case 8:
                    eedata_read(_CL_Position8,res);
                    break;
            }*/
            _Menu32301Count1 = --res;
            break;
        case 1:   
            if(--_Menu32302Count2<0){
                _Menu32302Count2 = 100;
            }
            break;
    }
    lcd_dis_menu_32302();
    
    return;
}

void menu_sub_24(){
    Uint16 res;
    
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:   
            if(--_Menu330Count<200){
                eedata_read(_Pos_BackL,res);
                _Menu330Count = res;
            }
            _VPDA = _Menu330Count;
            break;
        case 2:
            if(--_Menu330Count<1800){
                eedata_read(_Pos_BackH,res);
                _Menu330Count = res;
            }
            _VPDA = _Menu330Count;
            break;
    }
    lcd_dis_menu_330();
    
    return;
}

void menu_sub_25(){
    Uint16 res;
    
    if(_uintCur>2){
        return;
    }
    switch(_uintCur){
        case 0:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
        case 1:   
            if(--_Menu331Count<200){
                eedata_read(_Tor_BackL,res);
                _Menu331Count = res;
            }
            _NJDA = _Menu331Count;
            break;
        case 2:
            if(--_Menu331Count<1800){
                eedata_read(_Tor_BackH,res);
                _Menu331Count = res;
            }
            _NJDA = _Menu331Count;
            break;
    }
    lcd_dis_menu_331();
    
    return;
}

void menu_sub_26(){
    
    if(_uintCur>13){
        return;
    }
    switch(_uintCur){
        case 0:
            if(--_BusCount0<0){
                _BusCount0 = 247;
            }
            break;
        case 1:
            if(--_RmRead<0){
                _RmRead = 7;
            }
            break;
        case 2:
            if(--_RmRead<0){
                _RmRead = 2;
            }
            break;
        case 3:
            if(--_BusCount1<1){
                _BusCount1 = 255;
            }
            break;
        case 4:  
            if(--_RmRead<0){
                _RmRead = 4;
            }
            break;
        case 5:
            if(--_RmRead<0){
                _RmRead = 2;
            }
            break; 
        case 6:
            if(--_BusCount2<0){
                _BusCount2 = 100;
            }
            break; 
        case 7:
            if(--_BusCount3<0){
                _BusCount3 = 100;
            }
            break;
        case 8:
            if(--_BusCount4<3){
                _BusCount4 = 99;
            }
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            _RmRead = (_RmRead==0) ? 1:0;
            break;
    }
    lcd_dis_menu_modbus();
    
    return;
}

void menu_sub_33(){
//    menu_add_33();
    menu_add_func[34]();
}

void menu_sub_35(){
    
    if(--_BusCount5<0){
        _BusCount5 = 100;
    }
    lcd_dis_menu_posals();
    return;
}

void menu_sub_36(){
//    menu_add_36();
    menu_add_func[36]();
}
void menu_sub_37(){
//    menu_add_37();
    menu_add_func[37]();
}
void menu_sub_38(){
//    menu_add_38();
    menu_add_func[38]();
    
}
void menu_sub_39(){
//    menu_add_39();
    menu_add_func[39]();
}
void menu_sub_40(){
 //   menu_add_40();
    menu_add_func[40]();
}
void menu_sub_41(){
//    menu_add_41();
    menu_add_func[41]();
}
void menu_sub_42(){
//    menu_add_42();
    menu_add_func[42]();
}
void menu_sub_43(){
 //   menu_add_43();
    menu_add_func[43]();
}

void menu_sub_44(){
//    menu_add_44();
    menu_add_func[44]();
}

void menu_sub_46(){
    Uint16 res;
    
    if(--_BusCount6<0){
        eedata_read(_Card,res);
        if(res==8){
            res = 126;
        }else{
            res = 247;
        }
        _BusCount6 = res;
    }
    lcd_dis_menu_redudant();
    
    return;
}

void menu_sub_48(){
    
    _RmRead = (_RmRead==0) ? 1:0;
    lcd_dis_menu_300b();
    return;
}














void (*menu_sub_func[])() = {
    NULL,
    menu_sub_0,
    NULL,
    menu_sub_2,
    menu_sub_3,
    NULL,
    menu_sub_5,
    NULL,
    NULL,
    menu_sub_8,
    menu_sub_9,
    menu_sub_10,
    menu_sub_11,
    menu_sub_12,
    menu_sub_13,
    menu_sub_14,
    menu_sub_15,
    menu_sub_16,
    menu_sub_17,
    menu_sub_18,
    menu_sub_19,
    menu_sub_20,
    menu_sub_21,
    menu_sub_22,
    menu_sub_23,
    menu_sub_24,
    menu_sub_25,
    menu_sub_26,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    menu_sub_33,
    menu_sub_35,
    menu_sub_36,
    menu_sub_37,
    menu_sub_38,
    menu_sub_39,
    menu_sub_40,
    menu_sub_41,
    menu_sub_42,
    menu_sub_43,
    menu_sub_44,
    menu_sub_45,
    menu_sub_46,
    NULL,
    menu_sub_48   
};

void menu_sub(){
    
    if(_Menu > 48){
        return;
    }
    if(menu_sub_func[_Menu]==NULL){
        return;
    }
    menu_sub_func[_Menu]();
}
