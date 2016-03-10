/* 
 * File:   action.h
 * Author: Administrator
 *
 * Created on 2016?3?7?, ??1:44
 */

#ifndef ACTION_H
#define	ACTION_H

#define ACTION_OP       0x69
#define ACTION_CL       0x96

extern Uint8 open_phase1();
extern Uint8 open_phase2();
extern Uint8 open_phase3();
extern Uint8 open_phase4();
extern Uint8 close_phase1();
extern Uint8 close_phase2();
extern Uint8 close_phase3();
extern Uint8 close_phase4();
extern void forbid();
extern void stop();
extern void dis_open_lock();
extern void dis_close_lock();
extern Uint8 judge_opdir_protect();
extern Uint8 judge_optor_protect();
extern Uint8 judge_cldir_protect();
extern Uint8 judge_cltor_protect();
extern Uint8 judge_open_dir();
extern Uint8 judge_close_dir();

#endif	/* ACTION_H */

