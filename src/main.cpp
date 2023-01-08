#include "main.h"

void on_center_button() {

}
void initialize() {
	Motor LGB(LGBPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor CL(CLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BL(BLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor RGB(RGBPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor CR(CRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BR(BRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor Cata(CataPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
	Motor Intake(IntakePort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Imu Inertial(ImuPort);
	Inertial.reset();
	Rotation Rotate(RotatePort);
	Rotate.reset();

	Task getRotation(getRotate, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Get Rotation Task");
	Task cataTask(cataControl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Cata Task");
	Task debugTask(Debug, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task sensorsTask(Sensors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task controlTask(Control, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	int autoncase = 1;
	 switch (autoncase){
		 case 1: blue1(); break;
		 case 2: blue2(); break;
		 case 3: red1(); break;
		 case 4: red2(); break;
		 case 5: skills(); break;
	 }
}

void opcontrol() {
	Motor LGB(LGBPort);
	Motor CL(CLPort);
	Motor BL(BLPort);
	Motor RGB(RGBPort);
	Motor CR(CRPort);
	Motor BR(BRPort);
	Motor Cata(CataPort);
	Motor Intake(IntakePort);
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
				CL.move(left);
				BL.move(left);
				RGB.move(right);
				CR.move(right);
	 			BR.move(right);

			if(master.get_digital_new_press(DIGITAL_R1)){shootCata();}
			Intake.move((master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)) *127);
			}
}
