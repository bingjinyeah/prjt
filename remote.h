/* 
 * File:   remote.h
 * Author: Administrator
 *
 * Created on 2016?3?10?, ??2:41
 */

#ifndef REMOTE_H
#define	REMOTE_H

extern void check_card();
extern void check_remote_aux();
extern Uint8 judge_aux_open();
extern Uint8 judge_aux_close();
extern Uint8 judge_r_st();
extern Uint8 judge_r_esd();
extern void button_remote_process();

#endif	/* REMOTE_H */

