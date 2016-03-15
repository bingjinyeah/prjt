/*****************************************************************************
*                                                                            *
*                                
*****************************************************************************/


/* ===========================================================================

FILE_NAME          basic.h



DESCRIPTION        This file contains the  basic data types

=========================================================================== */
#ifndef __BASIC_H__
#define __BASIC_H__

#define TEST
//#define LANGUAGE_EN
#define PHASE1
#define LITTLE_ENDIAN
/* --- basic type definitions ---------------------------------------------- */
#define SYS_ENTER_CRI {     \
  unsigned int DISI_save;        \
  DISI_save = DISICNT;           \
  asm volatile ("disi #0x3FFF"); \
  __builtin_write_DISICNT( DISI_save); } 
#define SYS_EXIT_CRI  {__builtin_write_DISICNT(0);}
#define VOID            void

#ifndef NULL
#define NULL            ((VOID *) 0UL)
#endif

typedef unsigned long 	Uint32;
typedef unsigned short 	Uint16;
typedef unsigned char 	Uint8;
typedef	char            Int8;
typedef	short           Int16;
typedef	long            Int32;
typedef char	        VisualString;
typedef char	        OctetString;
typedef char	        BitString;
typedef short	        BString;
typedef unsigned char	Bool8;

#ifdef TRUE
#undef TRUE
#endif
#define TRUE            0xFF

#ifdef FALSE
#undef FALSE
#endif
#define FALSE           0x00

#define false			0x00
#define fail			0x00
#define success			0xff
#define true			0xff

#define ufalse          0x69
#define utrue           0x96
#define wfalse          0xa569
#define wtrue           0xa596

#define E_ERR           0xff
#define E_OK            0        /* no error */
#define E_POS_RES       0
#define E_NEG_RES       1
#define E_PENDING_RES   0xFF

#define INIT_STATUS     0x55aa
#define NOINIT_STATUS   0xaa55

#define CONST_DATA      const
#define ArrElemCnt(Arr) (sizeof (Arr) / sizeof *(Arr))

#define BIT0            0x0001
#define BIT1            0x0002
#define BIT2            0x0004
#define BIT3            0x0008
#define BIT4            0x0010
#define BIT5            0x0020
#define BIT6            0x0040
#define BIT7            0x0080
#define BIT8            0x0100
#define BIT9            0x0200
#define BIT10           0x0400
#define BIT11           0x0800
#define BIT12           0x1000
#define BIT13           0x2000
#define BIT14           0x4000
#define BIT15           0x8000
/* ------------------------------------------------------------------------- */
/* macros                                                                    */
/* ------------------------------------------------------------------------- */

/* ---- macro elemsize, to calculate the size of an element of a record ---- */

#ifndef elemsize
#define elemsize(type,member) sizeof (((type *) 0)->member)
#endif

/* --- macro min(a,b), to calculate the minimum of two values  ------------- */

#ifndef min
#define min(a,b)        (((a) < (b)) ? (a) : (b))
#endif

/* --- macro max(a,b), to calculate the maximum of two values  ------------- */

#ifndef max
#define max(a,b)        (((a) > (b)) ? (a) : (b))
#endif

#if defined (offsetof)
  #undef offsetof
  #define offsetof(t,m)   (USIGN16)((USIGN32)&((t*)0)->m)
#endif /* defined (offsetof) */

extern void delayms(Uint16 num);
extern void delayus(Uint16 num);

/* --- define for additional tests ONLY for BFD_HW ------------------------- */
//efine ADDITIONAL_TEST
#define _AUTO_PSV __attribute__((space(psv)))
#endif /* __BASIC_H__ */
