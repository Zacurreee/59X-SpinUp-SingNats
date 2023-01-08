#include "main.h"

double minHeight = 28000;
double maxHeight = 34000;
bool shooting = false, catdown = true;
double cataKP = 0.1;
double intakeSpeed = 127;
void getRotate(void*ignore){
  Rotation Rotate(RotatePort);
  while (true){
    // printf ("Angle: %d\n", Rotate.get_angle());
  }
}

 void cataControl(void*ignore) {
  Motor Cata(CataPort);
  Rotation Rotate(RotatePort);
  while(true){
    double cataError = Rotate.get_angle() > maxHeight ? minHeight : Rotate.get_angle() - minHeight;
    if(shooting){
      Cata.move(127);
      delay(100);
      Cata.move(0);
      shooting = false;
      catdown = false;
    }else{
      Cata.move(cataError*cataKP);
      catdown = true;
      printf("cataError %2f, Rotation Angle %d\n", cataError, Rotate.get_angle());
    }
  }
}

void shootCata(){shooting = !shooting;}
