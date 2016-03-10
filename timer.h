/* 
 * File:   timer.h
 * Author: Administrator
 *
 * Created on 2016?3?10?, ??2:45
 */

#ifndef TIMER_H
#define	TIMER_H

extern void set_t1(Uint16 num);
extern void t1_init(Uint16 num);
extern void t1_init_dummy();
extern void t1_close();
extern void t4_init(Uint16 num);
extern void time_compensate();

#endif	/* TIMER_H */

