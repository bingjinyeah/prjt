#include "includes.h"

Uint8 check_code(){
    
    return E_OK;
}

Uint8 check_rom(){
    
    return E_OK;
}
Uint8 check_ram(){
    
    return E_OK;
}
Uint8 check_eeprom(){
    
    return E_OK;
}
Uint8 check_ad(){
    
    return E_OK;
}

Uint8 self_check(){
    
    if(check_code()!=E_OK)
        return E_ERR;
    if(check_rom()!=E_OK)
        return E_ERR;
    if(check_ram()!=E_OK)
        return E_ERR;
    if(check_eeprom()!=E_OK)
        return E_ERR;
    if(check_ad()!=E_OK)
        return E_ERR;
    return E_OK;
}