#ifndef _59X_PID_ODOM_HPP_
#define _59X_PID_ODOM_HPP_
extern double X, Y;
extern const double inPerDeg;
void setCoords(double x, double y);
void Odometry(void * ignore);
void resetPrevEncd();
#endif
