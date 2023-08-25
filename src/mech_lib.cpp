#include "main.h"

double minHeight = 8000;
double maxHeight = 35000;
double capHeight = 10000;
bool shooting = false;
double cataKP = 0.31;
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
  // double cata_error = 36000 - Rotate.get_angle();
  while(true){
   double cataError = (Rotate.get_angle() < maxHeight ? (minHeight - Rotate.get_angle()): (Rotate.get_angle() < capHeight ? minHeight: Rotate.get_angle() - minHeight));
     if(shooting){
       Cata.move(127);
       delay(500);
       Cata.move(0);
       shooting = false;
     }else{
       Cata.move(cataError*cataKP);
       // printf("cataError %2f, Rotation Angle %d\n", cataError, Rotate.get_angle());
     }
     // catDown  = Rotate.get_angle() > maxHeight/2;
   }

}




void shootCata(){shooting = !shooting;}
