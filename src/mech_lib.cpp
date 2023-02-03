#include "main.h"

double minHeight = 27400;
double maxHeight = 35000;
double capHeight = 10000;
bool shooting = false, catdown = false, catclear = true, indexing = true;
double cataKP = 0.21;
double intakeSpeed = 127;
double targIntakeSpeed = 0;
double threshold = 2650; //2730;
// double cataError = 0;
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
  double cataError = (Rotate.get_angle() > maxHeight ? minHeight : (Rotate.get_angle() < capHeight ? minHeight: Rotate.get_angle() - minHeight));
    if(shooting){
      catdown = false;
      Cata.move(127);
      delay(500);
      Cata.move(0);
      shooting = false;
    }else{
      Cata.move(cataError*cataKP);
      catdown = true;
      // printf("cataError %2f, Rotation Angle %d\n", cataError, Rotate.get_angle());
    }
    // catDown  = Rotate.get_angle() > maxHeight/2;
  }
}

void intakeControl(void*ignore){
  Motor Intake (IntakePort);
  ADIAnalogIn LSensor (Lsensor);
  while(true){
    if(indexing){
      if(catdown && LSensor.get_value() >= threshold){
        // && LSensor.get_value() >= threshold
        Intake.move(targIntakeSpeed);
      }else{
        delay(300);
        Intake.move(-127);
        delay(1000);
        Intake.move(0);
      }
    }else{
      if (catdown){
        Intake.move(targIntakeSpeed);
      }else{
        Intake.move(-127);
        delay(1000);
        Intake.move(0);
      }
    }
  }
}

void checkIndex(){
  indexing = !indexing;
}

void shootCata(){shooting = !shooting;}
void setIntakeSpeed(double s){targIntakeSpeed = s;}
