#include "main.h"

void on_center_button() {

}
void initialize() {
	Motor RGB(RGBPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BR(BRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor FR(FRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor LGB(LGBPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BL(BLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor FL(FLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor Cata(CataPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor Intake(IntakePort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Imu Inertial(ImuPort);
	Inertial.reset();
	Rotation Rotate(RotatePort);
	Rotate.reset();


	Task getRotation(getRotate, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Get Rotation Task");
	Task cataTask(cataControl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Cata Task");
	Task debugTask(Debug, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	Task sensorsTask(Sensors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	FL.tare_position();
	FR.tare_position();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	Imu Inertial(ImuPort);
	Task controlTask(Control, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	double start = millis();

	// control();
	baseMove(31);
	waitBase(1000);
	baseMove(-13);
	waitBase(1000);
	controlTask.suspend();

	// task_suspend(controlTask);
	// control();
	// waitBase(5000);
	// baseTurn(73, 0.9, 0);
	// waitBase(5000);
	// baseMove(-46);

}



void opcontrol() {
	Motor LGB(LGBPort);
	Motor BL(BLPort);
	Motor FL(FLPort);
	Motor RGB(RGBPort);
	Motor FR(FRPort);
	Motor BR(BRPort);
	Motor Cata(CataPort);
	Motor Intake(IntakePort);
	Controller master(E_CONTROLLER_MASTER);

	LGB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	BL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	FL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	RGB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	FR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
	BR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

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

				if (master.get_digital_new_press(DIGITAL_L1)) shootCata();
				// Cata.move(120*(master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)));
				Intake.move(100*(master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)));
		}
}
