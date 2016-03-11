
#ifndef PINCFG_H
#define	PINCFG_H
#include <xc.h>


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************/
//	         端口定义模块
/**************************************************/
/**************************************************/	
#define  R_CL_Hold_Tris            _TRISC2	
//#define  R_CL_Hold_Write            _LATC2	
#define  R_CL_Hold_Read            _RC2
#define  R_CL_Hold_Bit            2	
/**************************************************/
#define  R_OP_Hold_Tris            _TRISC3	
//#define  R_OP_Hold_Write            _LATC3	
#define  R_OP_Hold_Read            _RC3	
#define  R_OP_Hold_Bit            3	
/**************************************************/
#define  BMQ_LD_Tris            _TRISC4		
#define  BMQ_LD_Write            _LATC4		
//#define  BMQ_LD_Read            _RC4
#define  BMQ_LD_Bit            4	
/**************************************************/
#define  SPI_CLK_Tris            _TRISG6	
#define  SPI_CLK_Write            _LATG6
#define  SPI_CLK_Read            _RG6
#define  SPI_CLK_Bit            6	
/**************************************************/
#define  SPI_DI_Tris            _TRISG7	
#define  SPI_DI_Write            _LATG7		
#define  SPI_DI_Read            _RG7
#define  SPI_DI_Bit            7	
/**************************************************/
#define  SPI_DO_Tris            _TRISG8	
#define  SPI_DO_Write            _LATG8		
#define  SPI_DO_Read            _RG8
#define  SPI_DO_Bit            8-8	
/**************************************************/
#define  L_OP_Tris            _TRISG9		
//#define  L_OP_Write            _LATG9	
#define  L_OP_Read            _RG9
#define  L_OP_Bit            9-8	
/**************************************************/
#define  L_CL_Tris            _TRISA12		
//#define  L_CL_Write            _LATA12	
#define  L_CL_Read            _RA12
#define  L_CL_Bit            12-8	
/**************************************************/
#define  Remote_Tris            _TRISA13	
//#define  Remote_Write            _LATA13	
#define  Remote_Read            _RA13
#define  Remote_Bit            13-8	
/**************************************************/
#define  Local_Tris            _TRISB5		
#define  Local_Write            _LATB5		
#define  Local_Read            _RB5
#define  Local_Bit            5
/**************************************************/
//#define  I_Ctrl_Tris            _TRISB4	
//#define  I_Ctrl_Write            _LATB4
//#define  I_Ctrl_Read            _RB4
//#define  I_Ctrl_Bit            4
/**************************************************/
//#define  ZJ_CL_Tris            _TRISB3		
//#define  ZJ_CL_Write            _LATB3
//#define  ZJ_CL_Read            _RB3
//#define  ZJ_CL_Bit            3
/**************************************************/
//#define  ZJ_OP_Tris            _TRISB2		
//#define  ZJ_OP_Write            _LATB2
//#define  ZJ_OP_Read            _RB2
//#define  ZJ_OP_Bit            2
/**************************************************/
#define  DA_CS_Tris            _TRISB6		
#define  DA_CS_Write            _LATB6			
//#define  DA_CS_Read            _RB6
#define  DA_CS_Bit            6
/**************************************************/
#define  DA_LD_Tris            _TRISB7		
#define  DA_LD_Write            _LATB7
//#define  DA_LD_Read            _RB7
#define  DA_LD_Bit            7
/**************************************************/
#define  DB0_Tris            _TRISB8		
#define  DB0_Write            _LATB8
#define  DB1_Tris            _TRISB9		
#define  DB1_Write            _LATB9
#define  DB2_Tris            _TRISB10		
#define  DB2_Write            _LATB10
#define  DB3_Tris            _TRISB11		
#define  DB3_Write            _LATB11
#define  DB4_Tris            _TRISB12		
#define  DB4_Write            _LATB12
#define  DB5_Tris            _TRISB13		
#define  DB5_Write            _LATB13
#define  DB6_Tris            _TRISB14		
#define  DB6_Write            _LATB14
#define  DB7_Tris            _TRISB15		
#define  DB7_Write            _LATB15	
            
/**************************************************/
#define  TQ_CL_Tris            _TRISD14		
#define  TQ_CL_Write            _LATD14		
//#define  TQ_CL_Read            _RD14
#define  TQ_CL_Bit            14
/**************************************************/
#define  TQ_OP_Tris            _TRISG1		
#define  TQ_OP_Write            _LATG1
//#define  TQ_OP_Read            _RG1
#define  TQ_OP_Bit            1
/**************************************************/
#define  BUS_LATX_Tris            _TRISF4		
#define  BUS_LATX_Write            _LATF4
#define  BUS_LATX_Read            _RF4
#define  BUS_LATX_Bit            4
/**************************************************/
#define  BAT_EN_Tris            _TRISG3		
#define  BAT_EN_Write            _LATG3		
#define  BAT_EN_Read            _RG3
#define  BAT_EN_Bit            3
/**************************************************/
#define  BAT_W_Tris            _TRISD15		
#define  BAT_W_Write            _LATD15		
#define  BAT_W_Read            _RD15
#define  BAT_W_Bit            15
/**************************************************/
#define  BUS_TX_Tris            _TRISF5		
#define  BUS_TX_Write            _LATF5
#define  BUS_TX_Read            _RF5
#define  BUS_TX_Bit            5
/**************************************************/
#define  BPQ_TX_Tris            _TRISF3		
#define  BPQ_TX_Write            _LATF3
#define  BPQ_TX_Read            _RF3
#define  BPQ_TX_Bit            3
/**************************************************/
#define  BPQ_LATX_Tris            _TRISF2		
#define  BPQ_LATX_Write            _LATF2
#define  BPQ_LATX_Read            _RF2
#define  BPQ_LATX_Bit            2
/**************************************************/
#define  I_Card_Tris            _TRISB15		
//#define  I_Card_Write            _LATB15	
#define  I_Card_Read            _RB15
#define  I_Card_Bit            15
/**************************************************/
#define  P_Card_Tris            _TRISB14		
//#define  P_Card_Write            _LATB14	
#define  P_Card_Read            _RB14
#define  P_Card_Bit            14
/**************************************************/
#define  FB_FW_Tris            _TRISB10		
//#define  FB_FW_Write            _LATB1		
#define  FB_FW_Read            _RB10
#define  FB_FW_Bit            10
/**************************************************/
#define  FB_TQ_Tris            _TRISB9		
//#define  FB_TQ_Write            _LATB9		
#define  FB_TQ_Read            _RB9
#define  FB_TQ_Bit            9
/**************************************************/
#define  R_CV_Tris            _TRISF8		
//#define  R_CV_Write            _LATF8	
#define  R_CV_Read            _RF8
#define  R_CV_Bit            8-8
/**************************************************/
#define  LED_R_Tris            _TRISF7		
#define  LED_R_Write            _LATF7		
//#define  LED_R_Read            _RF7
#define  LED_R_Bit            7
/**************************************************/
#define  IR_Tris            _TRISF6			
//#define  IR_Write            _LATF6		
#define  IR_Read            _RF6
#define  IR_Bit            6
/**************************************************/
//#define  LED_Y_Tris            _TRISG3		
//#define  LED_Y_Write            _LATG3		
//#define  LED_Y_Read            _RG3
//#define  LED_Y_Bit            3
/**************************************************/
#define  LED_G_Tris            _TRISG2		
#define  LED_G_Write            _LATG2		
//#define  LED_G_Read            _RG2
#define  LED_G_Bit            2
/**************************************************/
#define  RESETB_Tris            _TRISA14	
#define  RESETB_Write            _LATA14
//#define  RESETB_Read            _RA14
#define  RESETB_Bit            14-8
/**************************************************/
#define  RW_WRB_Tris            _TRISA15	
#define  RW_WRB_Write            _LATA15	
//#define  RW_WRB_Read            _RA15
#define  RW_WRB_Bit            15-8
/**************************************************/
#define  RS_Tris            _TRISD8		
#define  RS_Write            _LATD8		
//#define  RS_Read            _RD8
#define  RS_Bit            8-8
/**************************************************/
#define  Phase_A_Tris            _TRISD9	
//#define  Phase_A_Write            _LATD9
#define  Phase_A_Read            _RD9
#define  Phase_A_Bit            9-8				
/**************************************************/
#define  Phase_B_Tris            _TRISD10	
//#define  Phase_B_Write            _LATD10
#define  Phase_B_Read            _RD10
#define  Phase_B_Bit            10-8
/**************************************************/
#define  Phase_C_Tris            _TRISD11	
//#define  Phase_C_Write            _LATD11
#define  Phase_C_Read            _RD11
#define  Phase_C_Bit            11-8
/**************************************************/
#define  CLR_WDT_Tris            _TRISD0	
#define  CLR_WDT_Write            _LATD0
//#define  CLR_WDT_Read            _RD0
#define  CLR_WDT_Bit            0
/**************************************************/
#define  Code_Ctrl_Tris            _TRISD1	
#define  Code_Ctrl_Write            _LATD1	
//#define  Code_Ctrl_Read            _RD1
#define  Code_Ctrl_Bit            1
/**************************************************/
#define  OP_Tris            _TRISD2			
#define  OP_Write            _LATD2
//#define  OP_Read            _RD2
#define  OP_Bit            2
/**************************************************/
#define  CL_Tris            _TRISD3			
#define  CL_Write            _LATD3
//#define  CL_Read            _RD3
#define  CL_Bit            3
/**************************************************/
#define  E_S4B_Tris            _TRISD12	
#define  E_S4B_Write            _LATD12
//#define  E_S4B_Read            _RD12
#define  E_S4B_Bit            12-8
/**************************************************/
#define  R_ST_Tris            _TRISD13		
//#define  R_ST_Write            _LATD13	
#define  R_ST_Read            _RD13
#define  R_ST_Bit            13-8
/**************************************************/
#define  R_OP_Tris            _TRISD4		
//#define  R_OP_Write            _LATD4		
#define  R_OP_Read            _RD4
#define  R_OP_Bit            4
/**************************************************/
#define  R_CL_Tris            _TRISD5		
//#define  R_CL_Write            _LATD5		
#define  R_CL_Read            _RD5
#define  R_CL_Bit            5
/**************************************************/
#define  R_ESD_Tris            _TRISD6		
//#define  R_ESD_Write            _LATD6			
#define  R_ESD_Read            _RD6
#define  R_ESD_Bit            6
/**************************************************/
#define  E_S4A_Tris            _TRISD7		
#define  E_S4A_Write            _LATD7
//#define  E_S4A_Read            _RD7
#define  E_S4A_Bit            7
/**************************************************/
#define  E_S3B_Tris            _TRISF0		
#define  E_S3B_Write            _LATF0
//#define  E_S3B_Read            _RF0
#define  E_S3B_Bit            0
/**************************************************/
#define  E_S3A_Tris            _TRISF1		
#define  E_S3A_Write            _LATF1
//#define  E_S3A_Read            _RF1
#define  E_S3A_Bit            1
/**************************************************/
#define  CAN_TX_Tris            _TRISG1		
#define  CAN_TX_Write            _LATG1
#define  CAN_TX_Read            _RG1
#define  CAN_TX_Bit            1
/**************************************************/
#define  CAN_LATX_Tris            _TRISG0		
#define  CAN_LATX_Write            _LATG0
#define  CAN_LATX_Read            _RG0
#define  CAN_LATX_Bit            0
/**************************************************/
#define  E_S5_Tris            _TRISA6		
#define  E_S5_Write            _LATA6
//#define  E_S5_Read            _RA6
#define  E_S5_Bit            6
/**************************************************/
#define  XN_STOP_Tris            _TRISA7	
//#define  XN_STOP_Write            _LATA7	
#define  XN_STOP_Read            _RA7
#define  XN_STOP_Bit            7
/**************************************************/
#define  E_S2B_Tris            _TRISG14	
#define  E_S2B_Write            _LATG14
//#define  E_S2B_Read            _RG14
#define  E_S2B_Bit            14-8
/**************************************************/
#define  E_S2A_Tris            _TRISG12	
#define  E_S2A_Write            _LATG12
//#define  E_S2A_Read            _RG12
#define  E_S2A_Bit            12-8
/**************************************************/
#define  TEMP_Tris            _TRISG13		
//#define  TEMP_Write            _LATG13	
#define  TEMP_Read            _RG13
#define  TEMP_Bit            13-8
/**************************************************/
#define  E_S1B_Tris            _TRISG15	
#define  E_S1B_Write            _LATG15
//#define  E_S1B_Read            _RG15
#define  E_S1B_Bit            15-8
/**************************************************/
#define  E_S1A_Tris            _TRISC1		
#define  E_S1A_Write            _LATC1
//#define  E_S1A_Read            _RC1
#define  E_S1A_Bit            1
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	

