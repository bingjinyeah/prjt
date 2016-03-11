/* 
 * File:   code.h
 * Author: Administrator
 *
 * Created on 2016?3?10?, ??1:47
 */

#ifndef CODE_H
#define	CODE_H

extern void get_code_vp();
extern Uint16 circle_to_line(Uint16 vp);
extern Uint8 set_logic();
extern Uint16 alu_dbd();
extern void alu_nx();
extern void alu_nnx();
extern Uint8 set_dp_logic();
extern void alu_dp_nx();
extern void alu_dp_nnx();
extern Uint16 alu_dis_ic();
extern Uint16 alu_dis_position_back();
extern Uint16 alu_dis_tor_back();
extern void cal_zero(Uint16 cll, Uint16 opl);
extern void cal_limit_length();
extern Uint8 cal_length(Uint16 low, Uint16 high);
extern Uint8 cal_limit(Uint16 opl, Uint16 cll, Uint16 lz);
#endif	/* CODE_H */

