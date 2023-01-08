#ifndef _59X_PID_CONTROL_HPP_
#define _59X_PID_CONTROL_HPP_
extern double errorEncdL, errorEncdR, targPowerL, targPowerR, powerL, powerR, errorBearing;
extern bool turnMode, balanceMode;
void baseMove(double dis, double kp, double kd);
void baseMove(double dis);
void baseTurn(double bearing, double kp, double kd);
void baseTurn(double bearing);
void powerBase(double l, double r);
void timerBase(double l, double r, double t);
void balanceBase();
void unPauseBase();
void waitBase(double cutoff);
void Control(void * ignore);
void resetCoords(double x, double y);
#endif
