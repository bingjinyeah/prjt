#define _PARA_EXT
#include "includes.h"

void op_cl_port_init(){
    OP_Tris = 0;
    Nop();
    OP_Write = 0;
    OP_Write = 0;
    CL_Tris = 0;
    Nop();
    CL_Write = 0;
    CL_Write = 0;
}
extern Uint16 _RomValue[] _AUTO_PSV;
void cpu_init(){
    
    _PSV = 1;
    PSVPAG = __builtin_psvpage(&_RomValue);
    _PSV = 1;
    enable_wdt();
    clr_wdt();
    SET_CPU_IPL(3);
}

void port_init(){
    
    op_cl_port_init();
    _POR = 0;
    _StatusBack&=0xff;
    Code_Ctrl_Tris = 0;
    Nop();
    Code_Ctrl_Write = 0;
    E_S1A_Tris = 0;
	E_S1B_Tris = 0;
	E_S2A_Tris = 0;
	E_S2B_Tris = 0;
	E_S3A_Tris = 0;
	E_S3B_Tris = 0;
	E_S4A_Tris = 0;
	E_S4B_Tris = 0;
	E_S1A_Write = 0;		
	E_S1B_Write = 0;	
	E_S2A_Write = 0;		
	E_S2B_Write = 0;	
	E_S3A_Write = 0;		
	E_S3B_Write = 0;	
	E_S4A_Write = 0;			
	E_S4B_Write = 0;	
}

void para_init(){
    Uint16 i;
    
    _System_Back = false;
    _SetCLLimitFlag	= 0;		
    _SetOPLimitFlag	= 0;		
    _uintMenuCount	= 0;			
    _uintIdentCount	= 0;
    _Count_Ident_Key	= 0;
    _Menu					= 0;			
    _ucharKey			= false;		
    _ucharMenuKey		= false;		
    _ucharOpenKey      	= false;        
    _ucharCloseKey			= false;	   
    _ucharIdentKey	= false;
    _ucharReadIdentKey	= false;
    _ucharFlowKey	= false;
    _ucharReadFlowKey	= false;
    _ucharFlowBackKey	= false;

     _DP_ACTION    	= 0;  
     for(i=0;i<4;i++){
        _Sn_Flag[i] = 0;
        _Sn_PreFlag[i] = 0;
     }
    _RushCount = 0xff;              
    _Rush_PlaceCount = 40;        
    _Rush_AlarmCount = 40;        
    rush_status();	
}

void public_init(){
    
    poweron_init();
    spi2_init();
    check_card();
    _strAlarmFlag = 0;
    _BytePowerDown = 0;
    power_init();
    delayms(110);
    if(_BytePowerDown==0x55){
        process_power_down();
    }
    t1_init(_conT1Time);
    adc12_init();
    di_init();
    ir_init();
    ir_open();
    lcd_dis_clr_all();
}

void system_init(){
    
    BAT_EN_Tris = 0;
    if(_ChargeupFlag==0x55){
        BAT_EN_Write = 0;
    }else{
        BAT_EN_Write = 1;
    }
    lcd_init();
    lcd_dis_clr_all();
    
    if(_PowerIsOn!=NOINIT_STATUS){
        _SelfCheckFlag = INIT_STATUS;
        //rush_feedback();
        lcd_dis_softver();
        SYS_ENTER_CRI;
        self_check();
        SYS_EXIT_CRI;
        TQ_CL_Tris = 0;
        TQ_OP_Tris = 0;
        TQ_CL_Write = 1;
        TQ_OP_Write = 1;
        lcd_dis_company();
        battery_manage_init();
        _PowerIsOn = NOINIT_STATUS;
    }
    public_init();
}

        
        