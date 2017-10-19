#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           flyWheelMotor, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           aimServo,      tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           tiltServo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           elevatorMotor, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           rightMotor,    tmotorVex393_MC29, openLoop, driveRight)

// INVERTS THE POLARITY OF THE SIGNAL
int invert(int channel) { return channel * (-1); }

// FUNCTION TO SET FLY-WHEEL-MOTOR SPEED AND WAIT
int setFlyWheelSpeedAndWait(int speed) {
	motor[flyWheelMotor] = invert(speed);
	wait1Msec(800);
	return 0;
}

task main {
	// CONSTANTS
	int maxMotorSpeed = 127;         // MAX MOTOR SPEED CONSTANT
	int midMotorSpeed = 0;           // MID MOTOR SPEED CONSTANT
	int minMotorSpeed = invert(127); // MIN MOTOR SPEED CONSTANT
	int zero = 0;                    // ZERO CONSTANT
	int stateOn = 1;                 // STATE 'ON' CONSTANT
	int stateOff = 0;                // STATE 'OFF' CONSTANT

	while (true) // REPEAT FOREVER
	{
		// DRIVE MOTORS //
		//arcadeControl(invert(Ch3), invert(Ch4), 10); // MAKES IT POSSIBLE TO USE ONE JOYSTICK TO CONTROL BOTH DRIVE MOTORS

		motor[rightMotor] = ((vexRT[Ch3] - vexRT[Ch4])/-2);
		motor[leftMotor] = ((vexRT[Ch3] + vexRT[Ch4])/-2);
	
		// ACCESSORIES //
		motor[aimServo] = invert(vexRT[Ch2]);

		// FLYWHEEL //
		if (vexRT[Btn6U] == stateOn) {
			setFlyWheelSpeedAndWait(15); // GRADUALLY RAMP-UP MOTOR SPEED
			setFlyWheelSpeedAndWait(30);
			setFlyWheelSpeedAndWait(45);
			setFlyWheelSpeedAndWait(60);
			setFlyWheelSpeedAndWait(75);
			setFlyWheelSpeedAndWait(90);
			setFlyWheelSpeedAndWait(105);
			setFlyWheelSpeedAndWait(120);
			setFlyWheelSpeedAndWait(127);
			} else if (vexRT[Btn6D] == stateOn) {
			motor[flyWheelMotor] = zero;
		}

		// ELEVATOR MOTOR //
		// CHECK IF 5U IS PRESSED
		if (vexRT[Btn5U] == stateOn) {
			motor[elevatorMotor] = 127;
		}
		
		// CHECK IF 6U AND 6D ARE BOTH UNPRESSED
		if ((vexRT[Btn5U] == stateOff) && (vexRT[Btn5D] == stateOff)) {
			motor[elevatorMotor] = zero;
		}

		// CHECK IF 5D IS PRESSED
		if (vexRT[Btn5D] == stateOn) {
			motor[elevatorMotor] = invert(maxMotorSpeed);
		}

		// TILT SERVO (FIRE) //
		if (vexRT[Btn7D] == stateOn) { // CHECK IF 7D IS PRESSED
			motor[tiltServo] = 127;
			wait1Msec(750); // GIVES THE SERVO 750 MILLISECONDS TO MOVE.
		}

		// RETURN THE HOPPER TO NORMAL POSITION IF BOTH BUTTONS ARE UNPRESSED
		if ((vexRT[Btn7D] == stateOff) && (vexRT[Btn7U] == stateOff)) {
			motor[tiltServo] = invert(50);
			wait1Msec(750);
		}

		// TILT SERVO (SHAKE) //
		if (vexRT[Btn7U] == stateOn) {
			motor[tiltServo] = -127;
			wait1Msec(500); // GIVES THE SERVO 500 MILLISECONDS TO MOVE.
		}
	}
}