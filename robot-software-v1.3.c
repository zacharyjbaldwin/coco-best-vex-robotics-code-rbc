#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop, driveLeft);
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393_MC29, openLoop, driveRight);
#pragma config(Motor,  port4,           flyWheelMotor, tmotorVex393HighSpeed_MC29, openLoop);
#pragma config(Motor,  port5,           elevatorMotor, tmotorVex393HighSpeed_MC29, openLoop);
#pragma config(Motor,  port6,           aimServo,      tmotorServoStandard, openLoop);
#pragma config(Motor,  port7,           tiltServo,     tmotorServoStandard, openLoop);

int invert(int channel) { return channel * (-1); }

task main {
	bool flyWheelSpinning = false;

	int maxMotorSpeed = 127;
	int minMotorSpeed = -127;
	int zero = 0;

	while (true)
	{
		// DRIVE MOTORS
		motor[leftMotor] = invert(vexRT[Ch3]);
		motor[rightMotor] = invert(vexRT[Ch4]);

		// ACCESSORIES
		motor[aimServo] = vexRT[Ch2];
		motor[tiltServo] = vexRT[Btn7D];

		arcadeControl(Ch3, Ch4, 10);

		// FLYWHEEL CODE
		if (vexRT[Btn6U]) {
			flyWheelSpinning = true;
			} else if (vexRT[Btn6D]) {
			flyWheelSpinning = false;
		}

		if (flyWheelSpinning) {
			setMotor(motor[flyWheelMotor], maxMotorSpeed);
			} else if (!flyWheelSpinning) {
			setMotor(motor[flyWheelMotor], zero);
		}
	}
}
