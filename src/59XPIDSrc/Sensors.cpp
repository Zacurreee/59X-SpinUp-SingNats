#include "main.h"
double encdL = 0, encdR = 0, bearing = 0, angle = halfPI;
double measuredV = 0, measuredVL = 0, measuredVR = 0;
void Sensors(void * ignore){
  Motor LGB(LGBPort);
	Motor FL(FLPort);
	Motor BL(BLPort);
	Motor RGB(RGBPort);
	Motor FR(FRPort);
	Motor BR(BRPort);
  Imu Inertial (ImuPort);
  ADIEncoder encoderL (encdPort_L, encdPort_L + 1);
  ADIEncoder encoderR (encdPort_R, encdPort_R + 1);
  while(true){
    if(!Inertial.is_calibrating()){
      encdL = FL.get_position();
      encdR = FR.get_position();
      bearing = Inertial.get_heading();
      angle = halfPI - bearing * toRad;
      measuredVL = ((LGB.get_actual_velocity() + FL.get_actual_velocity() + BL.get_actual_velocity())/ 3);
      measuredVR = ((RGB.get_actual_velocity() + FR.get_actual_velocity() + BR.get_actual_velocity())/ 3);
      measuredV = (measuredVL + measuredVR)/2;
    }
    delay(5);
  }
}
