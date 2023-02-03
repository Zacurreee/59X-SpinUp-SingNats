#include "main.h"
#define DEFAULT_KP 0.14
#define DEFAULT_KD 0.09
#define DEFAULT_TURN_KP 1.2
#define DEFAULT_TURN_KD 0.9
#define RAMPING_POW 5
#define DISTANCE_LEEWAY 30
#define BEARING_LEEWAY 2
#define STOP_VEL 5.0
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 0, errorEncdR = 0, errorBearing = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD;

bool turnMode = false, pauseBase = false;

void baseMove(double dis, double kp, double kd){
  printf("baseMove(%.2f)\n", dis);
  turnMode = false;
  targEncdL += dis/inPerDeg;
  targEncdR += dis/inPerDeg;
  kP = kp;
  kD = kd;
}
void baseMove(double dis){
  baseMove(dis, DEFAULT_KP, DEFAULT_KD);
}

void baseTurn(double p_bearing, double kp, double kd){
  printf("baseTurn(%.2f, %.2f, %.2f)\n", p_bearing, kp, kd);
  turnMode = true;
  targBearing = p_bearing;
	kP = kp;
	kD = kd;
}
void baseTurn(double bearing){
  baseTurn(bearing, DEFAULT_TURN_KP, DEFAULT_TURN_KD);
}

void powerBase(double l, double r) {
  printf("powerBase(%.2f, %.2f)\n", l, r);
  pauseBase = true;
  powerL = l;
  powerR = r;
}

void timerBase(double l, double r, double t) {
  printf("timerBase(%.2f, %.2f, %.2f)\n", l, r, t);
  pauseBase = true;
  powerL = l;
  powerR = r;
  delay(t);
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y);
}

void unPauseBase() {
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y);
}

void waitBase(double cutoff){
  delay(200);
	double start = millis();
  if(turnMode) {
    while(fabs((targBearing - bearing) > BEARING_LEEWAY || fabs(measuredVL) > STOP_VEL || fabs(measuredVR) > STOP_VEL) && millis()-start < cutoff) {
      delay(20);
      // printf("stop :%.2f, %d, %d\n", (targBearing-bearing), fabs(measuredVL) > STOP_VEL, fabs(measuredVR) > STOP_VEL);
    }
  }else{
    while((fabs(targEncdL - encdL) > DISTANCE_LEEWAY || fabs(targEncdR - encdR) > DISTANCE_LEEWAY || fabs(measuredV) > STOP_VEL)&& millis() - start < cutoff) {
      delay(20);
    }
  }

  targEncdL = encdL;
  targEncdR = encdR;
  printf("Time taken %.2f\n", (millis() - start));
}

void Control(void * ignore){
  Motor LGB(LGBPort);
	Motor FL(FLPort);
	Motor BL(BLPort);
	Motor RGB(RGBPort);
	Motor FR(FRPort);
	Motor BR(BRPort);
  Imu Inertial(ImuPort);
  // ADIEncoder encoderL (encdPort_L, encdPort_L + 1);
  // ADIEncoder encoderR (encdPort_R, encdPort_R + 1);

  double prevErrorEncdL = 0, prevErrorEncdR = 0, prevErrorBearing = 0;
  while(competition::is_autonomous()){
    if(!Inertial.is_calibrating() && !pauseBase) {
      if(turnMode){
        errorBearing = targBearing - bearing;
        double deltaErrorBearing = errorBearing - prevErrorBearing;

        targPowerL = errorBearing * kP + deltaErrorBearing * kD;
        targPowerR = -targPowerL;

        prevErrorBearing = errorBearing;

        powerL = targPowerL;
        powerR = targPowerR;
      }else{
        errorEncdL = targEncdL - encdL;
        errorEncdR = targEncdR - encdR;

        double deltaErrorEncdL = errorEncdL - prevErrorEncdL;
        double deltaErrorEncdR = errorEncdR - prevErrorEncdR;

        targPowerL = errorEncdL * kP + deltaErrorEncdL * kD;
        targPowerR = errorEncdR * kP + deltaErrorEncdR * kD;

        prevErrorEncdL = errorEncdL;
        prevErrorEncdR = errorEncdR;

        double deltaPowerL = targPowerL - powerL;
        powerL += abscap(deltaPowerL, RAMPING_POW);
        double deltaPowerR = targPowerR - powerR;
        powerR += abscap(deltaPowerR, RAMPING_POW);
      }

      powerL = abscap(powerL, MAX_POW);
      powerR = abscap(powerR, MAX_POW);
    }
    LGB.move(powerL);
    FL.move(powerL);
    BL.move(powerL);
    RGB.move(powerR);
    FR.move(powerR);
    BR.move(powerR);
    delay(5);
  }
}

void resetCoords(double x, double y){
  Motor LGB(LGBPort);
	Motor FL(FLPort);
	Motor BL(BLPort);
	Motor RGB(RGBPort);
	Motor FR(FRPort);
	Motor BR(BRPort);
  ADIEncoder encoderL (encdPort_L, encdPort_L +1);
  ADIEncoder encoderR (encdPort_R, encdPort_R +1);

  LGB.tare_position();
  FL.tare_position();
  BL.tare_position();
  RGB.tare_position();
  FR.tare_position();
  BR.tare_position();
  encoderL.reset();
  encoderR.reset();
  resetPrevEncd();

  targBearing = bearing;
  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y);
}

void resetBearing(double bearing){
  bearing = 0;
}
