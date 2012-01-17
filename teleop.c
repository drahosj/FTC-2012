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


void init()
{
	servo[servoA] = BALL_SERVO_START;
	servo[servoB] = 255 - BALL_SERVO_START;

	servo[servoC] = CLAMP_START;
}


task main()
{
	int ballServo, clampServo, leftMotor, rightMotor, notArmMotor, scissorMotor;
		
	init();

	waitForStart(); //MAY NOT BE NECESSARY!!! CHECK TEMPLATE!!!!!

	while(true)
	{
		// <----THAT THING THAT READS CONTROLLER STUFF GOES RIGHT HERE 
		
