/* 
 * File:   port.h
 * Author: Administrator
 *
 * Created on 2016?3?10?, ??1:42
 */

#ifndef PORT_H
#define	PORT_H

extern Uint8 fb_fw_read();
extern Uint8 fb_tq_read();
extern Uint8 in_stop();
extern Uint8 in_local();
extern Uint8 in_remote();
extern Uint8 r_op_hold_read();
extern Uint8 r_cl_hold_read();
extern Uint8 l_op_read();
extern Uint8 l_cl_read();
extern Uint8 r_op_read();
extern Uint8 r_cl_read();
extern Uint8 r_st_read();
extern Uint8 r_cv_read();
extern Uint8 r_esd_read();
extern void led_g_r_set(Uint8 g, Uint8 r);
#endif	/* PORT_H */

