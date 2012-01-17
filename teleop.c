////---Controller Config Diagram---\\\\

/*
     --S1----     ---------       --------
    |        |   |         |     |        |
 -----   ------------   ------------   ------------
| NXT | | Drive L (D)| | Not-Arm (F)| |  BallL  (A)| 
|     | | Drive R (E)| | Scissor (G)| |  BallR  (B)|
 -----   ------------   ------------  |  Clamp  (C)|
	    Motor          Motor       ------------
					  Servo
*///End Controller Config Diagram\\\\

#define CLAMP_START 100
#define BALL_SERVO_START 100
#define CLAMP_OUT_BTN 1
#define CLAMP_IN_BTN 2
#define BALL_UP_BTN 3
#define BALL_DOWN_BTN 4


void init()
{
	servo[servoA] = BALL_SERVO_START;
	servo[servoB] = 255 - BALL_SERVO_START;

	servo[servoC] = CLAMP_START;

	//TODO: SET SERVO CHANGE RATES!!!
}


task main()
{
	int ballServo, clampServo, leftMotor, rightMotor, notArmMotor, scissorMotor;
		
	init();

	waitForStart(); //MAY NOT BE NECESSARY!!! CHECK TEMPLATE!!!!!

	while(true)
	{
		// <----THAT THING THAT READS CONTROLLER STUFF GOES RIGHT HERE 
		// Assuming that y1 is left and y2 is right, I can never remember. IF NECESSARY SWITCH!!!

		// SET THE VARIABLES FOR THE DRIVE MOTORS ||| THIS SHOULD BE GOOD TO KEEP \\

		leftMotor = joystick.joy1_y1; 
		rightMotor = joystick.joy1_y2;
		

		// THIS STUFF IS REALLY GHETTO \\

		notArmMotor = joystick.joy2_y1;	//NOT ARM MOTOR IS JOY2 Y1. PROBABLY TEMPORARY AND WILL NEED A SCALE FACTOR!!!

		scissorMotor = joystick.joy2_y2; //Scissor lift on joy2 y2; TODO: CHANGE THIS TO A PUSH BUTTON!!!

		if (joy2Btn(CLAMP_OUT_BTN))
			clampServo = 255; //move it outwards
		else if (joy2Btn(CLAMP_IN_BTN))
			clampServo = 0;  //move it inwards
		else
			clampServo = servoValue[servoC]; //move it to where it is (ie. stay still)

		if (joy2Btn(BALL_UP_BTN))
			ballServo = 255; //move up
		else if (joy2Btn(BALL_DOWN_BTN))
			ballServo = 0; //move down
		else
			ballServo = servoValue[servoA]; //move to where it is (stay still)


		//THIS STUFF SHOULD BE GOOD TO KEEP!!!!\\
		=========================================

		motor[motorD] = leftMotor; //set left motor to left value
		motor[motorE] = rightMotor; //set right motor to right value

		motor[motorF] = notArmMotor; //set not-arm motor to not-arm-motor value
		motor[motorG] = scissorMotor; //set scissor motor to scissor value

		servo[servoA] = ballServo; //setting ball lifter left servo is easy, left is master
		servo[servoB] = 255 - ballServo; //right servo has to be a mirror of left servo, as such is 255 - left (master) value

		servo[servoC] = clampServo; //clamp servo = clamp servo value
		
		
}

