
#ifndef EEDATA_H
#define	EEDATA_H

#include "basic.h"
/*****************************************************************/
//						?????????
/*****************************************************************/
/*****************************************************************/
//-----------------------????????---------------------------------------
/*****************************************************************/
#define  _IdentNum1_Init            0x1234
#define  _IdentNum2_Init            0x5678
#define  _FlowNum1_Init             0x0000
#define  _FlowNum2_Init             0x0000
/*****************************************************************/
//-----------------------????????---------------------------------------
/*****************************************************************/
#define  _CL_Dir_Init            0xff 	
#define  _Code_Orde_Init            0x00	
#define  _CLDir_Protect_Init            0xff
#define  _CL_TorProtect_Init            60
#define  _OPDir_Protect_Init            0xff
#define  _OP_TorProtect_Init            80
/*****************************************************************/
//-----------------------????????---------------------------------------
/*****************************************************************/	
#define  _S1_Fun_Init            0xff		
#define  _S1_Status_Init            0xff	
#define  _S2_Fun_Init            0x01		
#define  _S2_Status_Init            0xff	
#define  _S3_Fun_Init            0xff		
#define  _S3_Status_Init            0x69	
#define  _S4_Fun_Init            0x01		
#define  _S4_Status_Init            0x69	
/*****************************************************************/
//----------------------????????---------------------------------------
/*****************************************************************/						
#define  _LocalCtrl_Init            0xff	
#define	_DPCtrl_Init            0xff	
#define  _TwoLinesCtrl_Init            0xff
#define  _IC_Dbd_Init            10		
#define  _IC_Logic_Init            0xffff	
#define  _IC_Low_Init            0x02DD      
#define  _IC_High_Init            0x0E53	   
#define  _IC_Low_VP_Init            0		
#define  _IC_High_VP_Init            100	
#define  _Local_Lock_Init            0x69	
#define  _Remote_Lock_Init            0x69
#define  _ESD_Action_Init            0xff	
#define  _ESD_ExceedHot_Init            ufalse
#define  _ESD_ExceedSp_Init            ufalse
#define  _ESD_ExceedLock_Init            ufalse
#define  _ESD_ExceedTime_Init            ufalse
#define  _Forbid_ESD_Init            0xff	
#define  _Interim_Ctrl_Init            0xff
#define  _Pos_BackL_Init            400	
#define  _Pos_BackH_Init            2000	
#define  _Tor_BackL_Init            400	
#define  _Tor_BackH_Init            2000	
#define  _VarSpeedEnable_Init            0xff
#define  _OP_Position1_Init            1	
#define  _OP_Position2_Init            2	
#define  _OP_Position3_Init            3	
#define  _OP_Position4_Init            4	
#define  _OP_Position5_Init            5	
#define  _OP_Position6_Init            6	
#define  _OP_Position7_Init            7	
#define  _OP_Position8_Init            8	
#define  _OP_Position9_Init            9	
#define  _OP_Position10_Init            10
#define  _CL_Position1_Init            10	
#define  _CL_Position2_Init            9	
#define  _CL_Position3_Init            8	
#define  _CL_Position4_Init            7	
#define  _CL_Position5_Init            6	
#define  _CL_Position6_Init            5	
#define  _CL_Position7_Init            4	
#define  _CL_Position8_Init            3	
#define  _CL_Position9_Init            2	
#define  _CL_Position10_Init            1	
#define  _OP_Speed1_Init            1		
#define  _OP_Speed2_Init            2	 	
#define  _OP_Speed3_Init            3		
#define  _OP_Speed4_Init            4		
#define  _OP_Speed5_Init            5		
#define  _OP_Speed6_Init            6		
#define  _OP_Speed7_Init            7		
#define  _OP_Speed8_Init            8		
#define  _OP_Speed9_Init            9		
#define  _OP_Speed10_Init            10	
#define  _CL_Speed1_Init            1		
#define  _CL_Speed2_Init            2		
#define  _CL_Speed3_Init            3		
#define  _CL_Speed4_Init            4		
#define  _CL_Speed5_Init            5		
#define  _CL_Speed6_Init            6		
#define  _CL_Speed7_Init            7		
#define  _CL_Speed8_Init            8		
#define  _CL_Speed9_Init            9		
#define  _CL_Speed10_Init            10	
#define  _ESD_Speed_Init            200	
#define  _Pos_BackLogic_Init            0x69
#define  _Tor_BackLogic_Init            0x69
#define  _DP_Adress_Init            126	
#define  _POSALS_Init            0x05									
#define  _POSMIN_Init            0x00 														
#define  _POSMAX_Init            0x064							
#define  _POSDBD_Init            0x0a		
#define  _POSMIT_Init            0x00		
#define  _LOSPOS_Init            0x00		
#define  _DPSLTO_Init            99          
#define  _MODSLTO_Init            99         
#define  _AUXMSK_Init            0x7f		
#define  _RelayControl_Init            0x00  
#define  _BANDRT_Init            0x05         
#define  _PARITY_Init            0x02        
#define  _InverseDisEnable_Init            0xff
#define  _conEn            	0x69		
#define  _conCn            	0xff		
#define  _BIG_SHUCK_Init            0	       
#define  _EEPRomValue_Init            0x00
#define	_Monitor_With_OverTorque_Init             0x00
#define	_Monitor_With_Remote_Init             0x00 


extern Uint16 _EEDATA(2) _Card;

extern Uint16 _EEDATA(2) _CL_Dir;

extern Uint16 _EEDATA(2) _CL_Limit;			
		
extern Uint16 _EEDATA(2) _L_CL_Limit;		
		
extern Uint16 _EEDATA(2) _OP_Limit;			
		
extern Uint16 _EEDATA(2) _L_OP_Limit;		
		
extern Uint16 _EEDATA(2) _Limit_Length;		
	
extern Uint16 _EEDATA(2) _L_Zero;			
	
extern Uint16 _EEDATA(2) _PhaseOrder;		
	
extern Uint16 _EEDATA(2) _Chargelapse;		
	
extern Uint16 _EEDATA(2) _IdentNum1;

extern Uint16 _EEDATA(2) _IdentNum2;

extern Uint16 _EEDATA(2) _FlowNum1;

extern Uint16 _EEDATA(2) _FlowNum2;
	
/*****************************************************************/
//-------------------??????????????---------------------------
/*****************************************************************/
	
extern Uint16 _EEDATA(2) _Language;
	
extern Uint16 _EEDATA(2) _InverseDisEnable;
	
extern Uint16 _EEDATA(2) _Code_Orde;
		
extern Uint16 _EEDATA(2) _CLDir_Protect;

extern Uint16 _EEDATA(2) _CL_TorProtect;
	
extern Uint16 _EEDATA(2) _CL_OverTorPos;		
			
extern Uint16 _EEDATA(2) _OPDir_Protect;

extern Uint16 _EEDATA(2) _OP_TorProtect;
	
extern Uint16 _EEDATA(2) _OP_OverTorPos;		
	
extern Uint16 _EEDATA(2) _S1_Fun;
						
extern Uint16 _EEDATA(2) _S1_Position;	
	
extern Uint16 _EEDATA(2) _S1_Status;
	
extern Uint16 _EEDATA(2) _S2_Fun;
						
extern Uint16 _EEDATA(2) _S2_Position;	
	
extern Uint16 _EEDATA(2) _S2_Status;

extern Uint16 _EEDATA(2) _S3_Fun;
						
extern Uint16 _EEDATA(2) _S3_Position;	
	
extern Uint16 _EEDATA(2) _S3_Status;
	
extern Uint16 _EEDATA(2) _S4_Fun;
						
extern Uint16 _EEDATA(2) _S4_Position;

extern Uint16 _EEDATA(2) _S4_Status;
			
extern Uint16 _EEDATA(2) _LocalCtrl;

extern Uint16 _EEDATA(2) _TwoLinesCtrl;
	
extern Uint16 _EEDATA(2) _IC_Dbd;   
	
extern Uint16 _EEDATA(2) _Code_Dbd;	
		
extern Uint16 _EEDATA(2) _IC_Logic;
	
extern Uint16 _EEDATA(2) _IC_Low;   
	
extern Uint16 _EEDATA(2) _IC_High;  

extern Uint16 _EEDATA(2) _IC_Low_VP;
	
extern Uint16 _EEDATA(2) _IC_High_VP;
		
extern Uint16 _EEDATA(2) _Local_Lock;

extern Uint16 _EEDATA(2) _Remote_Lock;

extern Uint16 _EEDATA(2) _ESD_Action;	
					
extern Uint16 _EEDATA(2) _ESD_ExceedHot;		
		
extern Uint16 _EEDATA(2) _ESD_ExceedSp;		
		
extern Uint16 _EEDATA(2) _ESD_ExceedLock;	
		
extern Uint16 _EEDATA(2) _ESD_ExceedTime;	
	
extern Uint16 _EEDATA(2) _Forbid_ESD;

extern Uint16 _EEDATA(2) _Interim_Ctrl;

extern Uint16 _EEDATA(2) _Start_Pos;			
	
extern Uint16 _EEDATA(2) _Stop_Pos;			
				
extern Uint16 _EEDATA(2) _MoveTime;			
	
extern Uint16 _EEDATA(2) _StopTime; 			
		
extern Uint16 _EEDATA(2) _VarSpeedEnable;
	
extern Uint16 _EEDATA(2) _OP_Position1;
	
extern Uint16 _EEDATA(2) _OP_Position2;
	
extern Uint16 _EEDATA(2) _OP_Position3;
	
extern Uint16 _EEDATA(2) _OP_Position4;
	
extern Uint16 _EEDATA(2) _OP_Position5;

extern Uint16 _EEDATA(2) _OP_Position6;
	
extern Uint16 _EEDATA(2) _OP_Position7;

extern Uint16 _EEDATA(2) _OP_Position8;
	
extern Uint16 _EEDATA(2) _OP_Position9;

extern Uint16 _EEDATA(2) _OP_Position10;
		
extern Uint16 _EEDATA(2) _CL_Position1;
	
extern Uint16 _EEDATA(2) _CL_Position2;
	
extern Uint16 _EEDATA(2) _CL_Position3;
	
extern Uint16 _EEDATA(2) _CL_Position4;
	
extern Uint16 _EEDATA(2) _CL_Position5;

extern Uint16 _EEDATA(2) _CL_Position6;
	
extern Uint16 _EEDATA(2) _CL_Position7;

extern Uint16 _EEDATA(2) _CL_Position8;
	
extern Uint16 _EEDATA(2) _CL_Position9;

extern Uint16 _EEDATA(2) _CL_Position10;
	
extern Uint16 _EEDATA(2) _OP_Speed1;

extern Uint16 _EEDATA(2) _OP_Speed2;
		
extern Uint16 _EEDATA(2) _OP_Speed3;

extern Uint16 _EEDATA(2) _OP_Speed4;

extern Uint16 _EEDATA(2) _OP_Speed5;

extern Uint16 _EEDATA(2) _OP_Speed6;

extern Uint16 _EEDATA(2) _OP_Speed7;

extern Uint16 _EEDATA(2) _OP_Speed8;

extern Uint16 _EEDATA(2) _OP_Speed9	;

extern Uint16 _EEDATA(2) _OP_Speed10 ;

extern Uint16 _EEDATA(2) _CL_Speed1	 ;

extern Uint16 _EEDATA(2) _CL_Speed2	 ;
			
extern Uint16 _EEDATA(2) _CL_Speed3	 ;

extern Uint16 _EEDATA(2) _CL_Speed4	 ;

extern Uint16 _EEDATA(2) _CL_Speed5	 ;

extern Uint16 _EEDATA(2) _CL_Speed6	 ;

extern Uint16 _EEDATA(2) _CL_Speed7	 ;

extern Uint16 _EEDATA(2) _CL_Speed8	 ;

extern Uint16 _EEDATA(2) _CL_Speed9	 ;

extern Uint16 _EEDATA(2) _CL_Speed10 	;
	
extern Uint16 _EEDATA(2) _ESD_Speed;			
	
extern Uint16 _EEDATA(2) _Pos_BackL	 ;
	
extern Uint16 _EEDATA(2) _Pos_BackH	 ;
		
extern Uint16 _EEDATA(2) _Pos_BackLogic	;

extern Uint16 _EEDATA(2) _Tor_BackL	 ;

extern Uint16 _EEDATA(2) _Tor_BackH	 ;
							
extern Uint16 _EEDATA(2) _Tor_BackLogic ;

extern Uint16 _EEDATA(2) _DP_Adress	 ;

extern Uint16 _EEDATA(2) _DP_Adress2;		
	
extern Uint16 _EEDATA(2) _POSALS	 ;
						
extern Uint16 _EEDATA(2) _POSMIN 	 ;
						
extern Uint16 _EEDATA(2) _POSMAX	 ;
			
extern Uint16 _EEDATA(2) _POSMIT	 ;

extern Uint16 _EEDATA(2) _LOSPOS  ;

extern Uint16 _EEDATA(2) _LOSPOS_Code ;               
            
extern Uint16 _EEDATA(2) _DPSLTO  ;
	
extern Uint16 _EEDATA(2) _MODSLTO	 ;

extern Uint16 _EEDATA(2) _AUXMSK	 ;   
	
extern Uint16 _EEDATA(2) _POSMIN_Code ;                    

extern Uint16 _EEDATA(2) _POSMAX_Code ;                   

extern Uint16 _EEDATA(2) _BANDRT;     

extern Uint16 _EEDATA(2) _PARITY;	

extern Uint16 _EEDATA(2) _RelayControl;

extern Uint16 _EEDATA(2) _Redundancy;			

extern Uint16 _EEDATA(2) _CL_TorPercent;				

extern Uint16 _EEDATA(2) _OP_TorPercent;				

extern Uint16 _EEDATA(2) _BIG_SHUCK;

extern Uint16 _EEDATA(2) _EEPRomValue;				

extern Uint16 _EEDATA(2) _Monitor_With_OverTorque;
	
extern Uint16 _EEDATA(2) _Monitor_With_Remote;		

extern Uint16 _EEDATA(2) _DPCtrl;

extern  Uint16 eedata_addr; 
extern  Uint16 eedata_val;

#define eedata_read(src, dest) { \
    TBLPAG = __builtin_tblpage(&src);\
    eedata_addr = __builtin_tbloffset(&src); \
    eedata_val = __builtin_tblrdl(eedata_addr); \
    dest = eedata_val; \
}


#define eedata_erase(src) { \
    NVMCON = 0x4044;\
    NVMADRU = __builtin_tblpage(&src);\
    NVMADR = __builtin_tbloffset(&src); \
    __builtin_write_NVM();\
    while(NVMCONbits.WR);\
}

#define eedata_write(src, data) { \
    eedata_erase(src)\
    NVMCON = 0x4004;\
    TBLPAG = __builtin_tblpage(&src);\
    eedata_addr = __builtin_tbloffset(&src); \
    __builtin_tblwtl(eedata_addr, data);\
    __builtin_write_NVM();\
    while(NVMCONbits.WR);\
}
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used             regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	

