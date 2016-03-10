/* 
 * File:   power.h
 * Author: Administrator
 *
 * Created on 2016?3?10?, ??1:53
 */

#ifndef POWER_H
#define	POWER_H

extern Uint8 check_powerdown();
extern void power_down();
extern void poweron_init();
extern void power_init();
extern void rush_power();
extern void check_power();
extern void process_power_down();
extern Uint8 check_hot();


#endif	/* POWER_H */

