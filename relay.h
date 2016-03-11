/* 
 * File:   relay.h
 * Author: Administrator
 *
 * Created on 2016?3?10?, ??1:38
 */

#ifndef RELAY_H
#define	RELAY_H


extern void sx_status(Uint8 n);
extern void rush_relay_tor(Uint16 num, Uint16 flag);
extern void rush_relay_midtor();
extern void relay_position_judge();
extern void rush_relays();
extern void rush_relay_main();
extern void rush_monitor();
extern void monitor_release();
extern void monitor_release_dummy();
extern void rush_relay_close();
extern void rush_relay_concl();
extern void rush_relay_open();
extern void rush_relay_conop();
extern void rush_relay_run();
extern void rush_relay_conrun();
extern void rush_relay_jam();
extern void rush_relay_conjam();
extern void rush_relay_esd();
extern void rush_relay_conesd();

#endif	/* RELAY_H */

