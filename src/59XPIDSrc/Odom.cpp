#include "main.h"
const double inPerDeg = 0.036029505385762668;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0;
void setCoords(double x, double y){
  X = x;
  Y = y;
}
void Odometry(void * ignore){
  Imu Inertial (ImuPort);
  while(true){
    if(Inertial.is_calibrating()){
      resetCoords(0, 0);
    }else {
      double encdChangeL = encdL-prevEncdL;
      double encdChangeR = encdR-prevEncdR;

      double distance = (encdChangeL + encdChangeR)/2*inPerDeg;
      X += distance*cos(angle);
      Y += distance*sin(angle);
      /** update prev variables */
      prevEncdL = encdL;
      prevEncdR = encdR;
    }
    delay(5);
  }
}
void resetPrevEncd() {
  prevEncdL = 0;
  prevEncdR = 0;
}
