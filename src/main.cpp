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
	// ADIEncoder encoderL (encdPort_L, encdPort_L +1, true);
	// ADIEncoder encoderR (encdPort_R, encdPort_R +1, true);
	// encoderL.reset();
	// encoderR.reset();
	Imu Inertial(ImuPort);
	Inertial.reset();
	Rotation Rotate(RotatePort);
	Rotate.reset();

	Task getRotation(getRotate, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Get Rotation Task");
	Task cataTask(cataControl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Cata Task");
	Task intakeTask(intakeControl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");
	Task debugTask(Debug, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task sensorsTask(Sensors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task controlTask(Control, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	// int autoncase = 1;
	//  switch (autoncase){
	// 	 case 1: blue1(); break;
	// 	 case 2: blue2(); break;
	// 	 case 3: red1(); break;
	// 	 case 4: red2(); break;
	// 	 case 5: skills(); break;
	//  }
baseTurn(720);

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
	// ADIEncoder encoderL (encdPort_L, encdPort_L +1, true);
	// ADIEncoder encoderR (encdPort_R, encdPort_R +1, true);
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
			setIntakeSpeed((master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)) *127);
			// printf("encoderL: %.2f, encoderR: %.2f\n", encoderL.get_value(), encoderR.get_value());
			}
}
