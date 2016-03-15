/*
 * File   main.c
 * Author Administrator
 *
 * Created on 2016?2?24?, ??1258
 */

// DSPIC30F6014A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include "basic.h"
#include "eedata.h"

/*****************************************************************/
//-----------------???????????????---------------------------
/*****************************************************************/
Uint16 _EEDATA(2) _Card = 0x0;

Uint16 _EEDATA(2) _CL_Dir = _CL_Dir_Init;;

Uint16 _EEDATA(2) _CL_Limit = 0x0;			
		
Uint16 _EEDATA(2) _L_CL_Limit = 0x0;		
		
Uint16 _EEDATA(2) _OP_Limit = 0x0;			
#ifdef  TEST
Uint16 _EEDATA(2) _L_OP_Limit = 0x100;	//test
#else
Uint16 _EEDATA(2) _L_OP_Limit = 0x0;	//test	
#endif	
Uint16 _EEDATA(2) _Limit_Length = 0x0;		
	
Uint16 _EEDATA(2) _L_Zero = 0x0;			
	
Uint16 _EEDATA(2) _PhaseOrder = 0x0;		
	
Uint16 _EEDATA(2) _Chargelapse = 0x0;		
	
Uint16 _EEDATA(2) _IdentNum1 = _IdentNum1_Init;

Uint16 _EEDATA(2) _IdentNum2 = _IdentNum2_Init;

Uint16 _EEDATA(2) _FlowNum1 = _FlowNum1_Init;

Uint16 _EEDATA(2) _FlowNum2 = _FlowNum2_Init;
	
/*****************************************************************/
//-------------------??????????????---------------------------
/*****************************************************************/
	
Uint16 _EEDATA(2) _Language = _conCn;
	
Uint16 _EEDATA(2) _InverseDisEnable = _InverseDisEnable_Init;
	
Uint16 _EEDATA(2) _Code_Orde = _Code_Orde_Init;
		
Uint16 _EEDATA(2) _CLDir_Protect = _CLDir_Protect_Init;

Uint16 _EEDATA(2) _CL_TorProtect =  _CL_TorProtect_Init;
	
Uint16 _EEDATA(2) _CL_OverTorPos = 0x0;		
			
Uint16 _EEDATA(2) _OPDir_Protect =  _OPDir_Protect_Init;

Uint16 _EEDATA(2) _OP_TorProtect =  _OP_TorProtect_Init;
	
Uint16 _EEDATA(2) _OP_OverTorPos = 0x0;	
Uint16 _EEDATA(2) _Sn_Fun[4]	 = {
    _S1_Fun_Init,
    _S2_Fun_Init,
    _S3_Fun_Init,
    _S4_Fun_Init,
};
Uint16 _EEDATA(2) _Sn_Position[4]	 = {
    0,
    0,
    0,
    0,
};
Uint16 _EEDATA(2) _Sn_Status[4]	 = {
    _S1_Status_Init,
    _S2_Status_Init,
    _S3_Status_Init,
    _S4_Status_Init,
};
/*	
Uint16 _EEDATA(2) _S1_Fun	 =  _S1_Fun_Init;
						
Uint16 _EEDATA(2) _S1_Position	 = 0x0;	
	
Uint16 _EEDATA(2) _S1_Status	 =  _S1_Status_Init;
	
Uint16 _EEDATA(2) _S2_Fun	 =  _S2_Fun_Init;
						
Uint16 _EEDATA(2) _S2_Position	 = 0x0;	
	
Uint16 _EEDATA(2) _S2_Status	 =  _S2_Status_Init;

Uint16 _EEDATA(2) _S3_Fun	 =  _S3_Fun_Init;
						
Uint16 _EEDATA(2) _S3_Position	 = 0x0;	
	
Uint16 _EEDATA(2) _S3_Status	 =  _S3_Status_Init;
	
Uint16 _EEDATA(2) _S4_Fun	 =  _S4_Fun_Init;
						
Uint16 _EEDATA(2) _S4_Position = 0x0;

Uint16 _EEDATA(2) _S4_Status	 =  _S4_Status_Init;
*/			
Uint16 _EEDATA(2) _LocalCtrl	 =  _LocalCtrl_Init;

Uint16 _EEDATA(2) _TwoLinesCtrl =  _TwoLinesCtrl_Init;
	
Uint16 _EEDATA(2) _IC_Dbd	 =  _IC_Dbd_Init;   
	
Uint16 _EEDATA(2) _Code_Dbd	 = 0x0;	
		
Uint16 _EEDATA(2) _IC_Logic	 =  _IC_Logic_Init;
	
Uint16 _EEDATA(2) _IC_Low	 = _IC_Low_Init;   
	
Uint16 _EEDATA(2) _IC_High	 =  _IC_High_Init;  

Uint16 _EEDATA(2) _IC_Low_VP	 =  _IC_Low_VP_Init;
	
Uint16 _EEDATA(2) _IC_High_VP =  _IC_High_VP_Init;
		
Uint16 _EEDATA(2) _Local_Lock =  _Local_Lock_Init;

Uint16 _EEDATA(2) _Remote_Lock =  _Remote_Lock_Init;

Uint16 _EEDATA(2) _ESD_Action	 = 0x0;	
					
Uint16 _EEDATA(2) _ESD_ExceedHot = 0x0;		
		
Uint16 _EEDATA(2) _ESD_ExceedSp = 0x0;		
		
Uint16 _EEDATA(2) _ESD_ExceedLock = 0x0;	
		
Uint16 _EEDATA(2) _ESD_ExceedTime = 0x0;	
	
Uint16 _EEDATA(2) _Forbid_ESD =  _Forbid_ESD_Init;

Uint16 _EEDATA(2) _Interim_Ctrl =  _Interim_Ctrl_Init;

Uint16 _EEDATA(2) _Start_Pos = 0x0;			
	
Uint16 _EEDATA(2) _Stop_Pos = 0x0;			
				
Uint16 _EEDATA(2) _MoveTime = 0x0;			
	
Uint16 _EEDATA(2) _StopTime = 0x0; 			
		
Uint16 _EEDATA(2) _VarSpeedEnable	= _VarSpeedEnable_Init;

Uint16 _EEDATA(2) _OP_Position[10] = {
    _OP_Position1_Init,
    _OP_Position2_Init,
    _OP_Position3_Init,
    _OP_Position4_Init,
    _OP_Position5_Init,
    _OP_Position6_Init,
    _OP_Position7_Init,
    _OP_Position8_Init,
    _OP_Position9_Init,
    _OP_Position10_Init
};
Uint16 _EEDATA(2) _CL_Position[10] = {
    _CL_Position1_Init,
    _CL_Position2_Init,
    _CL_Position3_Init,
    _CL_Position4_Init,
    _CL_Position5_Init,
    _CL_Position6_Init,
    _CL_Position7_Init,
    _CL_Position8_Init,
    _CL_Position9_Init,
    _CL_Position10_Init
};
Uint16 _EEDATA(2) _OP_Speed[10] = {
    _OP_Speed1_Init,
    _OP_Speed2_Init,
    _OP_Speed3_Init,
    _OP_Speed4_Init,
    _OP_Speed5_Init,
    _OP_Speed6_Init,
    _OP_Speed7_Init,
    _OP_Speed8_Init,
    _OP_Speed9_Init,
    _OP_Speed10_Init
};
Uint16 _EEDATA(2) _CL_Speed[10] = {
    _CL_Speed1_Init,
    _CL_Speed2_Init,
    _CL_Speed3_Init,
    _CL_Speed4_Init,
    _CL_Speed5_Init,
    _CL_Speed6_Init,
    _CL_Speed7_Init,
    _CL_Speed8_Init,
    _CL_Speed9_Init,
    _CL_Speed10_Init
};
/*	
Uint16 _EEDATA(2) _OP_Position1 =  _OP_Position1_Init;
	
Uint16 _EEDATA(2) _OP_Position2 =  _OP_Position2_Init;
	
Uint16 _EEDATA(2) _OP_Position3 =  _OP_Position3_Init;
	
Uint16 _EEDATA(2) _OP_Position4 =  _OP_Position4_Init;
	
Uint16 _EEDATA(2) _OP_Position5 =  _OP_Position5_Init;

Uint16 _EEDATA(2) _OP_Position6 =  _OP_Position6_Init;
	
Uint16 _EEDATA(2) _OP_Position7 =  _OP_Position7_Init;

Uint16 _EEDATA(2) _OP_Position8 =  _OP_Position8_Init;
	
Uint16 _EEDATA(2) _OP_Position9 =  _OP_Position9_Init;

Uint16 _EEDATA(2) _OP_Position10 =  _OP_Position10_Init;
		
Uint16 _EEDATA(2) _CL_Position1 =  _CL_Position1_Init;
	
Uint16 _EEDATA(2) _CL_Position2 =  _CL_Position2_Init;
	
Uint16 _EEDATA(2) _CL_Position3 =  _CL_Position3_Init;
	
Uint16 _EEDATA(2) _CL_Position4 =  _CL_Position4_Init;
	
Uint16 _EEDATA(2) _CL_Position5 =  _CL_Position5_Init;

Uint16 _EEDATA(2) _CL_Position6 =  _CL_Position6_Init;
	
Uint16 _EEDATA(2) _CL_Position7 =  _CL_Position7_Init;

Uint16 _EEDATA(2) _CL_Position8 =  _CL_Position8_Init;
	
Uint16 _EEDATA(2) _CL_Position9 =  _CL_Position9_Init;

Uint16 _EEDATA(2) _CL_Position10 =  _CL_Position10_Init;
	
Uint16 _EEDATA(2) _OP_Speed1	 =  _OP_Speed1_Init;

Uint16 _EEDATA(2) _OP_Speed2	 =  _OP_Speed2_Init;
		
Uint16 _EEDATA(2) _OP_Speed3	 =  _OP_Speed3_Init;

Uint16 _EEDATA(2) _OP_Speed4	 =  _OP_Speed4_Init;

Uint16 _EEDATA(2) _OP_Speed5	 =  _OP_Speed5_Init;

Uint16 _EEDATA(2) _OP_Speed6	 =  _OP_Speed6_Init;

Uint16 _EEDATA(2) _OP_Speed7	 =  _OP_Speed7_Init;

Uint16 _EEDATA(2) _OP_Speed8	 =  _OP_Speed8_Init;

Uint16 _EEDATA(2) _OP_Speed9	 =  _OP_Speed9_Init;

Uint16 _EEDATA(2) _OP_Speed10 =  _OP_Speed10_Init;

Uint16 _EEDATA(2) _CL_Speed1	 =  _CL_Speed1_Init;

Uint16 _EEDATA(2) _CL_Speed2	 =  _CL_Speed2_Init;
			
Uint16 _EEDATA(2) _CL_Speed3	 =  _CL_Speed3_Init;

Uint16 _EEDATA(2) _CL_Speed4	 =  _CL_Speed4_Init;

Uint16 _EEDATA(2) _CL_Speed5	 =  _CL_Speed5_Init;

Uint16 _EEDATA(2) _CL_Speed6	 =  _CL_Speed6_Init;

Uint16 _EEDATA(2) _CL_Speed7	 =  _CL_Speed7_Init;

Uint16 _EEDATA(2) _CL_Speed8	 =  _CL_Speed8_Init;

Uint16 _EEDATA(2) _CL_Speed9	 =  _CL_Speed9_Init;

Uint16 _EEDATA(2) _CL_Speed10 	=  _CL_Speed10_Init;
*/	
Uint16 _EEDATA(2) _ESD_Speed = 0x0;			
	
Uint16 _EEDATA(2) _Pos_BackL	 =  _Pos_BackL_Init;
	
Uint16 _EEDATA(2) _Pos_BackH	 =  _Pos_BackH_Init;
		
Uint16 _EEDATA(2) _Pos_BackLogic	=  _Pos_BackLogic_Init;

Uint16 _EEDATA(2) _Tor_BackL	 =  _Tor_BackL_Init;

Uint16 _EEDATA(2) _Tor_BackH	 =  _Tor_BackH_Init;
							
Uint16 _EEDATA(2) _Tor_BackLogic =  _Tor_BackLogic_Init;

Uint16 _EEDATA(2) _DP_Adress	 =  _DP_Adress_Init;

Uint16 _EEDATA(2) _DP_Adress2 = 0x0;		
	
Uint16 _EEDATA(2) _POSALS	 =  _POSALS_Init;
						
Uint16 _EEDATA(2) _POSMIN 	 =  _POSMIN_Init;
						
Uint16 _EEDATA(2) _POSMAX	 =  _POSMAX_Init;
			
Uint16 _EEDATA(2) _POSMIT	 =  _POSMIT_Init;

Uint16 _EEDATA(2) _LOSPOS   = _LOSPOS_Init;

Uint16 _EEDATA(2) _LOSPOS_Code  = 0x0;               
            
Uint16 _EEDATA(2) _DPSLTO   = _DPSLTO_Init;
	
Uint16 _EEDATA(2) _MODSLTO	 =  _MODSLTO_Init;

Uint16 _EEDATA(2) _AUXMSK	 =  _AUXMSK_Init;   
	
Uint16 _EEDATA(2) _POSMIN_Code  = 0x0;                    

Uint16 _EEDATA(2) _POSMAX_Code  = 0x0;                   

Uint16 _EEDATA(2) _BANDRT = _BANDRT_Init;     

Uint16 _EEDATA(2) _PARITY = _PARITY_Init;	

Uint16 _EEDATA(2) _RelayControl = _RelayControl_Init;

Uint16 _EEDATA(2) _Redundancy = 0x0;			

Uint16 _EEDATA(2) _CL_TorPercent = 0x0;				

Uint16 _EEDATA(2) _OP_TorPercent = 0x0;				

Uint16 _EEDATA(2) _BIG_SHUCK = _BIG_SHUCK_Init;

Uint16 _EEDATA(2) _EEPRomValue = 0x0;				

Uint16 _EEDATA(2) _Monitor_With_OverTorque	= _Monitor_With_OverTorque_Init;
	
Uint16 _EEDATA(2) _Monitor_With_Remote = _Monitor_With_Remote_Init;		

Uint16 _EEDATA(2) _DPCtrl = _DPCtrl_Init;

Uint16 eedata_addr; 

Uint16 eedata_val; 

void get_eedata_snfun(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_Sn_Fun[0],temp);
            break;
        case 1:
            eedata_read(_Sn_Fun[1],temp);
            break;
        case 2:
            eedata_read(_Sn_Fun[2],temp);
            break;
        case 3:
            eedata_read(_Sn_Fun[3],temp);
            break;
    }
    *res = temp;
}

void get_eedata_snpos(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_Sn_Position[0],temp);
            break;
        case 1:
            eedata_read(_Sn_Position[1],temp);
            break;
        case 2:
            eedata_read(_Sn_Position[2],temp);
            break;
        case 3:
            eedata_read(_Sn_Position[3],temp);
            break;
    }
    *res = temp;
}

void get_eedata_snstatus(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_Sn_Status[0],temp);
            break;
        case 1:
            eedata_read(_Sn_Status[1],temp);
            break;
        case 2:
            eedata_read(_Sn_Status[2],temp);
            break;
        case 3:
            eedata_read(_Sn_Status[3],temp);
            break;
    }
    *res = temp;
}

void get_eedata_oppos(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_OP_Position[0],temp);
            break;
        case 1:
            eedata_read(_OP_Position[1],temp);
            break;
        case 2:
            eedata_read(_OP_Position[2],temp);
            break;
        case 3:
            eedata_read(_OP_Position[3],temp);
            break;
        case 4:
            eedata_read(_OP_Position[4],temp);
            break;
        case 5:
            eedata_read(_OP_Position[5],temp);
            break;
        case 6:
            eedata_read(_OP_Position[6],temp);
            break;
        case 7:
            eedata_read(_OP_Position[7],temp);
            break;
        case 8:
            eedata_read(_OP_Position[8],temp);
            break;
        case 9:
            eedata_read(_OP_Position[9],temp);
            break;
    }
    *res = temp;
}
void get_eedata_clpos(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_CL_Position[0],temp);
            break;
        case 1:
            eedata_read(_CL_Position[1],temp);
            break;
        case 2:
            eedata_read(_CL_Position[2],temp);
            break;
        case 3:
            eedata_read(_CL_Position[3],temp);
            break;
        case 4:
            eedata_read(_CL_Position[4],temp);
            break;
        case 5:
            eedata_read(_CL_Position[5],temp);
            break;
        case 6:
            eedata_read(_CL_Position[6],temp);
            break;
        case 7:
            eedata_read(_CL_Position[7],temp);
            break;
        case 8:
            eedata_read(_CL_Position[8],temp);
            break;
        case 9:
            eedata_read(_CL_Position[9],temp);
            break;
    }
    *res = temp;
}
void get_eedata_opspeed(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_OP_Speed[0],temp);
            break;
        case 1:
            eedata_read(_OP_Speed[1],temp);
            break;
        case 2:
            eedata_read(_OP_Speed[2],temp);
            break;
        case 3:
            eedata_read(_OP_Speed[3],temp);
            break;
        case 4:
            eedata_read(_OP_Speed[4],temp);
            break;
        case 5:
            eedata_read(_OP_Speed[5],temp);
            break;
        case 6:
            eedata_read(_OP_Speed[6],temp);
            break;
        case 7:
            eedata_read(_OP_Speed[7],temp);
            break;
        case 8:
            eedata_read(_OP_Speed[8],temp);
            break;
        case 9:
            eedata_read(_OP_Speed[9],temp);
            break;
    }
    *res = temp;
}
void get_eedata_clspeed(Uint16 n,Uint16 *res){
    Uint16 temp;
    switch(n){
        case 0:
            eedata_read(_CL_Speed[0],temp);
            break;
        case 1:
            eedata_read(_CL_Speed[1],temp);
            break;
        case 2:
            eedata_read(_CL_Speed[2],temp);
            break;
        case 3:
            eedata_read(_CL_Speed[3],temp);
            break;
        case 4:
            eedata_read(_CL_Speed[4],temp);
            break;
        case 5:
            eedata_read(_CL_Speed[5],temp);
            break;
        case 6:
            eedata_read(_CL_Speed[6],temp);
            break;
        case 7:
            eedata_read(_CL_Speed[7],temp);
            break;
        case 8:
            eedata_read(_CL_Speed[8],temp);
            break;
        case 9:
            eedata_read(_CL_Speed[9],temp);
            break;
    }
    *res = temp;
}