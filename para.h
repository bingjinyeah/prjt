#ifndef PARA_H
#define PARA_H

#ifdef _PARA_EXT
#define PARA_EXT
#else
#define PARA_EXT extern
#endif

#include <xc.h>
#include "basic.h"

//******************************************************************************
//******************************************************************************
//------------------rd ???????----------------------------------------
/******************************************************************************/
//	.section	.nbss,bss,near,address(0xE00)
/******************************************************************************/
//------------------????????-------------------------------------------
/******************************************************************************/
					
PARA_EXT Uint16 _Tab_Order_ADDR; 
	
PARA_EXT Uint16 _WriteEEPROMFlag;
	
PARA_EXT Uint16 BL;	
	
PARA_EXT Uint16 BL1;	
/******************************************************************************/
//------------------????????-------------------------------------------
/******************************************************************************/
					
PARA_EXT Uint16 _StopTimer;		  
    
PARA_EXT Uint16 _MoveCount;          
/******************************************************************************/
//------------------SPI2????-----------------------------------------------
/******************************************************************************/
					
PARA_EXT Uint16 _SPI2_DA;		
	
PARA_EXT Uint16 _CodeVP15;	
/******************************************************************************/
//------------------A/D????-------------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _CLNJ[11];		
	
PARA_EXT Uint16 _OPNJ[11];		
	
PARA_EXT Uint16 _IC[11];		
	
PARA_EXT Uint16 _AD[10];		
/******************************************************************************/
//------------------???????--------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _Delayms_Int_Flag; 	      
	
PARA_EXT Uint16 _DelayTimer; 	  
	
PARA_EXT Uint16 _RushRuning; 	  
	
PARA_EXT Uint16 _VPCount;		
		
PARA_EXT Uint16 _uintMenuCount;	
	
PARA_EXT Uint16 _JamCount;		
		
PARA_EXT Uint16 _S1_Count;		
	
PARA_EXT Uint16 _S2_Count;		
	
PARA_EXT Uint16 _S3_Count;		
	
PARA_EXT Uint16 _S4_Count;		
    
PARA_EXT Uint16 _Count2S;          
	
PARA_EXT Uint16 _Count5M;		
	
PARA_EXT Uint16 _Forbid_Count;	
	
PARA_EXT Uint16 _RushCount;		
	
PARA_EXT Uint16 _Rush_PlaceCount;       //?????????,?200ms????,200/5=40
	
PARA_EXT Uint16 _Rush_AlarmCount;       //?????????,?200ms????,200/5=40
	
PARA_EXT Uint16 _DisInitCount;        
//--------------------------------
PARA_EXT Uint16 _L_OP_Count;        
//--------------------------------
/******************************************************************************/
//-------------------????????------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _uintIrSampleCount;	
	
PARA_EXT Uint16 _uintIrSampleShr;	
	
PARA_EXT Uint16 _uintIrRxdCount;	
	
PARA_EXT Uint16 _uintIrRxdShr;		
	
PARA_EXT Uint16 _uintIrRxdBuf;		
	
PARA_EXT Uint16 _uintIrFlag;		
/******************************************************************************/
//------------------????????-------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _CodeVP;		
	
PARA_EXT Uint16 _L_CodeVP;		
    
PARA_EXT Uint16 _DirPreVP;  	  
	
PARA_EXT Uint16 _L_CodePreVP;	
		
PARA_EXT Uint16 _L_CodePPreVP;	
		
PARA_EXT Uint16 _L_CodePreVP2;	
		
PARA_EXT Uint16 _GrayCode;		
	
PARA_EXT Uint16 _VPPercent;		
		
PARA_EXT Uint16 _PreVPPercent;	
	
PARA_EXT Uint16 _NJPercent;		
		
PARA_EXT Uint16 _NJPercent_Temp;  
				
PARA_EXT Uint16 _VPDA;			
	
PARA_EXT Uint16 _NJDA;			
   
PARA_EXT Uint16 _SetCLLimitFlag;     
   
PARA_EXT Uint16 _SetOPLimitFlag;     
   
PARA_EXT Uint16 T1Int_Flag;          
   
PARA_EXT Uint16 _Limit_Flag;          
   
PARA_EXT Uint16 _Pre_Limit_Flag;          
   
PARA_EXT Uint16 _Length_Error_Flag;	
/******************************************************************************/
//------------------?????????-----------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _S1_Flag;		
	
PARA_EXT Uint16 _S1_PreFlag;	
	
PARA_EXT Uint16 _S2_Flag;		
	
PARA_EXT Uint16 _S2_PreFlag;	
	
PARA_EXT Uint16 _S3_Flag;		
	
PARA_EXT Uint16 _S3_PreFlag;	
	
PARA_EXT Uint16 _S4_Flag;		
	
PARA_EXT Uint16 _S4_PreFlag;	
//--------------------------------------------------------------------------------------
	
PARA_EXT Uint16 _DP_S1_Flag;	
	
PARA_EXT Uint16 _DP_S1_PreFlag;	
	
PARA_EXT Uint16 _DP_S2_Flag;	
	
PARA_EXT Uint16 _DP_S2_PreFlag;	
	
PARA_EXT Uint16 _DP_S3_Flag;	
	
PARA_EXT Uint16 _DP_S3_PreFlag;	
	
PARA_EXT Uint16 _DP_S4_Flag;	
	
PARA_EXT Uint16 _DP_S4_PreFlag;	
/******************************************************************************/
//------------------????????-------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _uchar_LocalPre;	
	
PARA_EXT Uint16 _uchar_OpenPre;		
/******************************************************************************/
//------------------??????-----------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _IC2Count;			
	
PARA_EXT Uint16 _IC3Count;			
	
PARA_EXT Uint16 _IC4Count;			
	
PARA_EXT Uint16 _IC2Buf[4];	
	
PARA_EXT Uint16 _IC3Buf[4];	
	
PARA_EXT Uint16 _IC4Buf[4];	
	
PARA_EXT Uint16 _IC2Buf_Phase[3];	
	
PARA_EXT Uint16 _IC3Buf_Phase[3];
	
PARA_EXT Uint16 _IC4Buf_Phase[3];
	
PARA_EXT Uint16 _uintPowerPeriod;	
//	
//_uintV1;			
//	
//_uintV2;			
//	
//_uintV3;			
	
PARA_EXT Uint16 _uintPhase1[4];
	
PARA_EXT Uint16 _uintPhase2[4];
	
PARA_EXT Uint16 _uintPhase3[4];
		
PARA_EXT Uint16 _LosPhaseCount; 	   
   
PARA_EXT Uint16 _PhaseCount;      
   
PARA_EXT Uint16 PowerInt_Flag;      
   
PARA_EXT Uint16 _RAMPhaseOrder[3];
/******************************************************************************/
//---------------??????--------------------------------------------------
/******************************************************************************/
	
PARA_EXT Uint16 _ucharKey;				
	
PARA_EXT Uint16 _ucharMenuKey;			
	
PARA_EXT Uint16 _ucharBackKey;			
	
PARA_EXT Uint16 _ucharDownKey;			
	
PARA_EXT Uint16 _ucharAddKey;			
	
PARA_EXT Uint16 _ucharSubKey;			
	
PARA_EXT Uint16 _ucharConfKey;			
	
PARA_EXT Uint16 _ucharAdDownKey;		
	
PARA_EXT Uint16 _ucharOpenKey;			
	
PARA_EXT Uint16 _ucharCloseKey;			
	
PARA_EXT Uint16 _ucharStopKey;			
	
PARA_EXT Uint16 _uintCur;				
	
PARA_EXT Uint16 _EmRead;				
	
PARA_EXT Uint16 _RmRead;				
	
PARA_EXT Uint16 _RmReadS;				
	
PARA_EXT Uint16 _uintRow;				
	
PARA_EXT Uint16 _Menu2Count0;			
	
PARA_EXT Uint16 _Menu2Count1;			
	
PARA_EXT Uint16 _Menu312Count0;			
	
PARA_EXT Uint16 _Menu312Count1;			
	
PARA_EXT Uint16 _Menu312Count2;			
	
PARA_EXT Uint16 _Menu312Count3;			
	
PARA_EXT Uint16 _Menu312Count4;			
	
PARA_EXT Uint16 _SxStatus;				
		
PARA_EXT Uint16 _RmRead1;				
		
PARA_EXT Uint16 _EmRead1;				
		
PARA_EXT Uint16 _Menu300ACount;			
	
PARA_EXT Uint16 _BusCount0;		    	
	
PARA_EXT Uint16 _BusCount1;               
        
PARA_EXT Uint16 _BusCount2;               
        
PARA_EXT Uint16 _BusCount3;               
        
PARA_EXT Uint16 _BusCount4;               
        
PARA_EXT Uint16 _BusCount5;               
        
PARA_EXT Uint16 _BusCount6;               
		
PARA_EXT Uint16 _Menu323Count;            
	
PARA_EXT Uint16 _Menu3220Count0;		
		
PARA_EXT Uint16 _Menu3220Count1;		
		
PARA_EXT Uint16 _Menu3220Count2;		
		
PARA_EXT Uint16 _Menu3220Count3;		
		
PARA_EXT Uint16 _Menu3221Count0;		
		
PARA_EXT Uint16 _Menu3221Count1;		
		
PARA_EXT Uint16 _Menu3221Count2;		
		
PARA_EXT Uint16 _Menu3221Count3;		
		
PARA_EXT Uint16 _Menu3230Count0;		
		
PARA_EXT Uint16 _Menu32301Count0;		
		
PARA_EXT Uint16 _Menu32301Count1;		
		
PARA_EXT Uint16 _Menu32301Count2;		
		
PARA_EXT Uint16 _Menu32302Count0;		
		
PARA_EXT Uint16 _Menu32302Count1;		
		
PARA_EXT Uint16 _Menu32302Count2;		
	
PARA_EXT Uint16 _Menu22_ConfCount;		
	
PARA_EXT Uint16 _Menu23_ConfCount;		
	
PARA_EXT Uint16 _Menu330Count;			
	
PARA_EXT Uint16 _Menu331Count;			
	
PARA_EXT Uint16 _Menu41Count0;			
	
PARA_EXT Uint16 _Menu43Count0;			
	
PARA_EXT Uint16 _Menu43Count1;			
	
PARA_EXT Uint16 _Menu5Count0;			
	
PARA_EXT Uint16 _Menu0Count0;			
	
PARA_EXT Uint16 _FB_Temp;	 			
	
PARA_EXT Uint16 _uchar_RemotePre;   	
		
PARA_EXT Uint16 _uchar_StopPre;     	
	
PARA_EXT Uint16 _uchar_ClosePre;    	
	
PARA_EXT Uint16 _uchar_IdlePre;     	
	
PARA_EXT Uint16 _uchar_SignalPre;   	
	
PARA_EXT Uint16 _uchar_SignalPre1;  	
	
PARA_EXT Uint16 _uchar_SignalPre2;  	
/*		
_Debug;
		
_Debug1;
	
_Debug2;
	
_Debug3;*/
	
PARA_EXT Uint16 _Alu_IC_tempL;      	
	
PARA_EXT Uint16 _Alu_IC_tempH;      	   
	
PARA_EXT Uint16 _Menu300Atemp;      	
	
PARA_EXT Uint16 _Menu300Atemp1;      	   
	
PARA_EXT Uint16 _Pre_Menu;                
//********************************************************************
//                ??????                                 *
//********************************************************************
	
PARA_EXT Uint16 _Row;                   
		
PARA_EXT Uint16 _Cloumn;                	
	
PARA_EXT Uint16 _PageCount;             
		
PARA_EXT Uint16 _CloumnCount;           		
	
PARA_EXT Uint16 _DisWord0;              
	
PARA_EXT Uint16 _DisWord1;              
	
PARA_EXT Uint16 _DisWord2;              
	
PARA_EXT Uint16 _DisWord3;              
	
PARA_EXT Uint16 _DisWord4;              
	
PARA_EXT Uint16 _DisWord5;              
	
PARA_EXT Uint16 _DisWord6;              
	
PARA_EXT Uint16 _DisWord7;              
	
PARA_EXT Uint16 _DisWord8;              
	
PARA_EXT Uint16 _DisWord9;              
	
PARA_EXT Uint16 _DisWord10;              
	
PARA_EXT Uint16 _DisWord11;              
	
PARA_EXT Uint16 _DisWord12;              
	
PARA_EXT Uint16 _DisWord13;              
	
PARA_EXT Uint16 _DisWord14;              
	
PARA_EXT Uint16 _DisWord15;              
	
PARA_EXT Uint16 _Dis_Length;              
	
PARA_EXT Uint16 _Dis_Addr;              
	
PARA_EXT Uint16 _RowWord0;              
	
PARA_EXT Uint16 _RowWord1;              
	
PARA_EXT Uint16 _RowWord2;              
	
PARA_EXT Uint16 _RowTemp;               
	
PARA_EXT Uint16 _Cardtype;              
	
PARA_EXT Uint16 _Cardtype0;             
	
PARA_EXT Uint16 _Clr_Row;                      
	
PARA_EXT Uint16 _Clr_Cloumn;                   
	
PARA_EXT Uint16 _Dis_Row;                      
	
PARA_EXT Uint16 _Dis_Cloumn;                   
//********************************************************************
//                ??????BCD???????                      *
//********************************************************************
	
PARA_EXT Uint16 _BCD_Ge;                       
	
PARA_EXT Uint16 _BCD_Shi;                      
	
PARA_EXT Uint16 _BCD_Bai;                      
	
PARA_EXT Uint16 _BCD_Qian;                     
//********************************************************************
//                ????????                            *
//********************************************************************
	
PARA_EXT Uint16 _Bat_3DayCount0;                
	
PARA_EXT Uint16 _Bat_3DayCount1;                
	
PARA_EXT Uint16 _Bat_3DayFlag;                  
	
PARA_EXT Uint16 _Bat_30MinCount0;               
	
PARA_EXT Uint16 _Bat_30MinCount1;               
	
PARA_EXT Uint16 _Bat_30MinFlag;                 
	
PARA_EXT Uint16 _Bat_10MinCount0;               
	
PARA_EXT Uint16 _Bat_10MinCount1;               
	
PARA_EXT Uint16 _Bat_10MinFlag;                 
	
PARA_EXT Uint16 _Bat_1MinCount;                 
	
PARA_EXT Uint16 _Bat_AlarmCount;                
	    
PARA_EXT Uint16 _Bat_Alarm_Flag;                
	
PARA_EXT Uint16 _uchar_BatteryPre;             
		
PARA_EXT Uint16 _Chargeuplapse;                
//********************************************************************
//                DP?????????                              *
//********************************************************************
        
PARA_EXT Uint16 _DPSLTO_COUNT;                 
        
PARA_EXT Uint16 _DPSLTO_COUNT1;                
        
PARA_EXT Uint16 _DP_NJ;                        
        
PARA_EXT Uint16 _DP_APP_FLAG;                  
//********************************************************************
//                DP?????????                              *
//********************************************************************
        
PARA_EXT Uint16 DP_TX_IDLE_COUNT;              
                                                             
PARA_EXT Uint16 DP_TX_LENGTH;                  
                                                             
PARA_EXT Uint16 DP_TX_POINTER;                 
                                                             
PARA_EXT Uint16 DP_TX_BUF;                     
                                                             
PARA_EXT Uint16 DP_TX_BUF1;                     
        
PARA_EXT Uint16 DP_TX_BUF2;             
        
PARA_EXT Uint16 DP_TX_BUF3;             
        
PARA_EXT Uint16 DP_TX_BUF4;             
        
PARA_EXT Uint16 DP_TX_BUF5;             
        
PARA_EXT Uint16 DP_TX_BUF6;             
        
PARA_EXT Uint16 DP_TX_BUF7;             
        
PARA_EXT Uint16 DP_TX_BUF8;             
        
PARA_EXT Uint16 DP_TX_BUF9;             
        
PARA_EXT Uint16 DP_TX_BUF10;            
        
PARA_EXT Uint16 DP_TX_BUF11;            
//********************************************************************
//                  DP?????????                           *
//********************************************************************
        
PARA_EXT Uint16 DP_RX_IDLE_COUNT;              
               
PARA_EXT Uint16 DP_RX_ERR;                     
        
PARA_EXT Uint16 DP_RX_LENGTH;                  
                       
PARA_EXT Uint16 DP_RX_BUF;                     
        
PARA_EXT Uint16 DP_RX_BUF1;                    
        
PARA_EXT Uint16 DP_RX_BUF2;                    
        
PARA_EXT Uint16 DP_RX_BUF3;                    
        
PARA_EXT Uint16 DP_RX_BUF4;                    
        
PARA_EXT Uint16 DP_RX_BUF5;                    
        
PARA_EXT Uint16 DP_RX_BUF6;                    
        
PARA_EXT Uint16 DP_RX_BUF7;                    
        
PARA_EXT Uint16 DP_RX_BUF8;                    
        
PARA_EXT Uint16 DP_RX_BUF9;             
        
PARA_EXT Uint16 DP_RX_BUF10;            
        
PARA_EXT Uint16 DP_RX_BUF11;            
//********************************************************************
//                       CRC???                                  *
//********************************************************************
        
PARA_EXT Uint16 DP_CRC_ADDR;                  
        
PARA_EXT Uint16 DP_CRC_LENGTH;                
        
PARA_EXT Uint16 DP_CRC_VALUE_L;               
        
PARA_EXT Uint16 DP_CRC_VALUE_H;               
//********************************************************************
//                       ?????                                 *
//********************************************************************
        
PARA_EXT Uint16 _Flag_Ident_Key;            	      
        
PARA_EXT Uint16 _Count_Ident_Key;        	      
        
PARA_EXT Uint16 _Ident_Buf1;         		      
        
PARA_EXT Uint16 _Ident_Buf2;         		      
       
PARA_EXT Uint16 _Flag_Ident_Rec;         	      
        
PARA_EXT Uint16 _Count_Ident_Rec;       	      
   
PARA_EXT Uint16 _ucharIdentKey;          	      
        
PARA_EXT Uint16 _ucharReadIdentKey;  
   	
PARA_EXT Uint16 _uintIdentCount;		      
	
PARA_EXT Uint16 _uintIdentCount1;	

/********************************************************************
                       ????*
********************************************************************/

PARA_EXT Uint16 _Flag_Flow_Key;            	
PARA_EXT Uint16 _Count_Flow_Key;        	
PARA_EXT Uint16 _Flow_Buf1;        		
PARA_EXT Uint16 _Flow_Buf2;         		
PARA_EXT Uint16 _Flag_Flow_Rec;         	
PARA_EXT Uint16 _Count_Flow_Rec;       	
PARA_EXT Uint16 _ucharFlowKey;  
PARA_EXT Uint16 _ucharFlowBackKey;
PARA_EXT Uint16 _ucharReadFlowKey;      	
PARA_EXT Uint16 _uintFlowCount;		
PARA_EXT Uint16 _uintFlowCount1;		
PARA_EXT Uint16 _uintIrFlow;			
PARA_EXT Uint16 _uintRomNum1;			
PARA_EXT Uint16 _uintRomNum2;			 

//******************************************************************************
//******************************************************************************
//-------------rd 3??2?????1--------------------------------------------
/******************************************************************************/
//	.section	 flag_section,bss,address(0x1800)
	
PARA_EXT Uint16 _Thread_Flag;             
                          
PARA_EXT Uint16 _Back_Flag;  			
	
PARA_EXT Uint16 _StatusBack;			
	
PARA_EXT Uint16 _strAlarmFlag;			
	
PARA_EXT Uint16 _PowerOn;				
    
PARA_EXT Uint16 _PowerIsOn;     		
    
PARA_EXT Uint16 _Dif1_Phase;              
    
PARA_EXT Uint16 _Dif2_Phase;              
    
PARA_EXT Uint16 _Dif3_Phase;              
    
PARA_EXT Uint16 _CalPhCount;              
   
PARA_EXT Uint16 _PhOrderFlag;             
    
PARA_EXT Uint16 _SelfCheckFlag;			
   
PARA_EXT Uint16 _BytePowerDown;			
   
PARA_EXT Uint16 _ByteRunningFlag;	   
	
PARA_EXT Uint16 _IC_Code;       		
	
PARA_EXT Uint16 _Menu;					   
	
PARA_EXT Uint16 _ChargeupFlag;  		
	
PARA_EXT Uint16 _Movement_Dire; 		
	
PARA_EXT Uint16 _Length_Check_Flag;		
//********************************************************************
//               ?DP????????????????1               *
//********************************************************************
        
PARA_EXT Uint16 _DP_Code;                      
        
PARA_EXT Uint16 _DP_PARA_FLAG;                 
        
PARA_EXT Uint16 _DP_IDATA1;                    
        
PARA_EXT Uint16 _DP_IDATA2;                    
        
PARA_EXT Uint16 _DP_IDATA3;                    
        
PARA_EXT Uint16 _DP_DIAGR1;                    
        
PARA_EXT Uint16 _DP_MODPOS;                    
        
PARA_EXT Uint16 _DP_RAWPOS;                    
        
PARA_EXT Uint16 _DP_DIAGR0;                    
        
PARA_EXT Uint16 _DP_ACTION;                    
        
PARA_EXT Uint16 _DP_ACTPOS;                    
    
#endif
