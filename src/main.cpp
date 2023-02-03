#include "main.h"

void on_center_button() {

}
void initialize() {
	Motor RGB(RGBPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BR(BRPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor FR(FRPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor LGB(LGBPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BL(BLPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor FL(FLPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor Cata(CataPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
	Motor Intake(IntakePort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	ADIEncoder encoderL (encdPort_L, encdPort_L +1, false);
	ADIEncoder encoderR (encdPort_R, encdPort_R +1, true);
	encoderL.reset();
	encoderR.reset();
	Imu Inertial(ImuPort);
	Inertial.reset();
	Rotation Rotate(RotatePort);
	Rotate.reset();
	ADIAnalogIn LSensor (Lsensor);

	Task getRotation(getRotate, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Get Rotation Task");
	Task cataTask(cataControl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Cata Task");
	Task intakeTask(intakeControl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");
	// Task indexTask(indexing, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Index Task");
	Task debugTask(Debug, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task sensorsTask(Sensors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task controlTask(Control, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	Imu Inertial(ImuPort);

	double start = millis();
	// int autoncase = 1;
	//  switch (autoncase){
	// 	 case 1: blue1(); break;
	// 	 case 2: blue2(); break;
	// 	 case 3: red1(); break;
	// 	 case 4: red2(); break;
	// 	 case 5: skills(); break;
	//  }
baseMove(-20);
waitBase(1000);
// delay(100);
baseTurn (90, 1.12, 1.1);
waitBase(1000);
baseMove(-4.5, 0.22, 0);
waitBase(1000);
setIntakeSpeed(-127);
delay(110);//50
setIntakeSpeed(0); //enough time for 2 disc intake
baseMove(10);
waitBase(1000);
baseTurn(45);
waitBase(1000);
baseMove(32, 0.15, 1);
waitBase(2000);
baseTurn(116, 1.3, 0.9);
delay(400);
shootCata();
delay(700);
baseTurn(209);
waitBase(1000);
setIntakeSpeed(127);
baseMove(-30);
waitBase(2000);
baseTurn(133);
waitBase(1000);
setIntakeSpeed(0);
baseMove(8);
delay(500);
shootCata();
delay(600);
baseTurn(220);
waitBase(1000);
setIntakeSpeed(127);
baseMove(-60, 0.15, 0.8);
waitBase(5000);
// setIntakeSpeed(0);
// baseTurn();
// waitBase(1000);
// baseMove();
// waitBase(1000);
// setIntakeSpeed(-127);
// delay(110);
// setIntakeSpeed(0);
}

void opcontrol() {
	Motor LGB(LGBPort);
	Motor FL(FLPort);
	Motor BL(BLPort);
	Motor RGB(RGBPort);
	Motor FR(FRPort);
	Motor BR(BRPort);
	Motor Cata(CataPort);
	Motor Intake(IntakePort);
	ADIEncoder encoderL (encdPort_L, encdPort_L + 1);
	ADIEncoder encoderR (encdPort_R, encdPort_R + 1);
	ADIAnalogIn LSensor (Lsensor);
	Controller master(E_CONTROLLER_MASTER);

	bool tankDrive =true;
	while(true) {
			double left, right;
			if(master.get_digital_new_press(DIGITAL_Y)) tankDrive = !tankDrive;

			if(tankDrive) {
				left = master.get_analog(ANALOG_LEFT_Y);
				right = master.get_analog(ANALOG_RIGHT_Y);
			} else {
				double power = master.get_analog(ANALOG_LEFT_Y);
				double turn = master.get_analog(ANALOG_RIGHT_X);

				left = power + turn;
				right = power - turn;
			}
				LGB.move(left);
				FL.move(left);
				BL.move(left);
				RGB.move(right);
				FR.move(right);
	 			BR.move(right);

			if(master.get_digital_new_press(DIGITAL_L1)){shootCata();}
			// Intake.move((master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)) *127);
			// printf("encoderL: %.2f, encoderR: %.2f\n", encoderL.get_value(), encoderR.get_value());
			setIntakeSpeed((master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)) *127);
			// printf("Sensor: %.2f\n", LSensor.get_value());
			}
}
