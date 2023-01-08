#include "main.h"
double encdL = 0, encdR = 0, bearing = 0, angle = halfPI;
double measuredV = 0, measuredVL = 0, measuredVR = 0;
void Sensors(void * ignore){
  Motor LGB(LGBPort);
	Motor CL(CLPort);
	Motor BL(BLPort);
	Motor RGB(RGBPort);
	Motor CR(CRPort);
	Motor BR(BRPort);
  Imu Inertial (ImuPort);
  while(true){
    if(!Inertial.is_calibrating()){
      encdL = CL.get_position();
      encdR = CR.get_position();
      bearing = Inertial.get_rotation();
      angle = halfPI - bearing * toRad;
      measuredVL = ((LGB.get_actual_velocity() + CL.get_actual_velocity() + BL.get_actual_velocity())/ 3);
      measuredVR = ((RGB.get_actual_velocity() + CR.get_actual_velocity() + BR.get_actual_velocity())/ 3);
      measuredV = (measuredVL + measuredVR)/2;
    }
    delay(5);
  }
}
