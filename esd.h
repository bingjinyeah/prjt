/* 
 * File:   esd.h
 * Author: Administrator
 *
 * Created on 2016?3?7?, ??9:50
 */

#ifndef ESD_H
#define	ESD_H

#include "basic.h"

#define  ESD_OP         0x69    
#define  ESD_CL         0x96
#define  ESD_HD         0xff

extern void esd_thread();
extern Uint8 com_esd();
//extern void esd_inactive();
//extern void esd_active();

#endif	/* ESD_H */

