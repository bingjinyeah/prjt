#define _PARA_EXT
#include <xc.h>
#include "basic.h"
#include "pincfg.h"
#include "para.h"
#include "lcd.h"
#include "flag.h"

extern void spi_init();
extern void poweron_init();
extern void power_init();
extern void process_power_down();
extern void check_card();
extern void battery_manage_init();
extern void self_check();
extern void ir_init();
extern void ir_open();
extern void adc12_init();
extern void di_init();
extern void t1_init(Uint16 num);

void rush_status(){
    
}

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

void cpu_init(){
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
     _S1_Flag	= 0;
     _S1_PreFlag	= 0;
     _S2_Flag	= 0;
     _S2_PreFlag		= 0;
     _S3_Flag	= 0;
     _S3_PreFlag	= 0;
     _S4_Flag	= 0;
     _S4_PreFlag		= 0;
    _RushCount = 0xff;              
    _Rush_PlaceCount = 40;        
    _Rush_AlarmCount = 40;        
    rush_status();	
}

void public_init(){
    
    poweron_init();
    spi_init();
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

        
        