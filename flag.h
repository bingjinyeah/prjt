
#ifndef FLAG_H
#define	FLAG_H
//==============================================================================
//+++++++++++++++++++++++++define debug	flag+++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define	_DisCheckTime            500	
#define	_conT1Time            	0x05	
#define	_NJADLength             0xC1f	
#define	Volt_coeff             71		
#define    DP_FRAM_START              0x03   
#define    DP_FRAM_END                0x03   
#define    DP_RX_BUF_MAX              0x0B   
/*****************************************************************/
//--------------????????-----------------------------------
/*****************************************************************/
#define	_S_CS            	0x0B		
#define	_S_OS            	0x01		
#define	_S_OD            	0x02		
#define	_S_CD            	0x03		
#define	_S_R            	0x04		
#define	_S_CT            	0x05		
#define	_S_OT            	0x06		
#define	_S_MT            	0x07		
#define	_S_J            	0x08		
#define	_S_ESD            	0x09		
#define	_S_G            	0x0A		
/*****************************************************************/
//--------------???????--------------------------------------
/*****************************************************************/
#define	_conStopCode            	0x96
#define	_conCloseCode            	0xaa
#define	_conOpenCode            	0x55
#define	_conBackCode            	0xfc
#define	_conAddCode                 0x2f
#define	_conSubCode                 0x7e
#define	_conDownCode            	0xcf
#define	_conConfCode            	0xf2
#define	_conIdentCode            	0x5a
#define	_conReadIdentCode           0xa5
#define _conFlowCode                0xa5
#define _conReadFlowCode            0x5a
/*****************************************************************/
//--------------------?????---------------------------------
/*****************************************************************/
#define	_utrue            	0x96
#define	_ufalse            0x69
/*****************************************************************/
//--------------strAlarmFlag????----------------------------------
/*****************************************************************/
#define	_CSFlag            	0x0001		
#define	_OSFlag            	0x0002		
#define	_RmFlickFlag        0x0004	
#define	_SignLostedFlag     0x0008	
#define	_ESDFlag            0x0010		
#define	_JamFlag            0x0020		
#define	_NoLoadFlag         0x0040	
#define	_CTFlag            	0x0080		
#define	_OTFlag            	0x0100		
#define	_VPStopFlag         0x0200	
#define	_DirErrorFlag       0x0400	
#define	_ButtonFlag         0x0800	
#define	_VPOver            	0x1000	
#define	_PhaseLostedFlag    0x2000
#define	_PowerDownFlag      0x4000	
#define	_Hot            	0x8000			
/*****************************************************************/
//--------------????????	_StatusBack --------------------------------
/*****************************************************************/
#define	_RunningFlag         0x0001	
#define	_ClosingFlag         0x0002	
#define	_OpeningFlag         0x0004	
#define	_RunOver             0x0008	
#define _TimeStopFlag        0x0010       
#define	_OP_LockFlag         0x0020	
#define	_CL_LockFlag         0x0040	
#define	_FbTimeFlag          0x0080
/*******************************************************************/
#define MOVE_DIR_CLOCK      0x6996
#define MOVE_DIR_ANTIC      0x9669

#define TWOLINE_OPEN         0x69
#define TWOLINE_CLOSE        0x96
#define TWOLINE_NO          0xff

#define ESD_OPENL           0x69
#define ESD_CLOSEL          0x96
#define ESD_HOLD            0xff

#define OPEN_MOV            0x69
#define CLOSE_MOV           0x96
#define NO_MOV              0xff

#endif	

