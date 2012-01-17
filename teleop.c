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
		
		/*
		//===========================================\\
		||========---------BEGIN PONY--------========||
		\\===========================================//	


                                                                                                                           
                                                   ._.       _i,_.                                                         
                                            .__iaa%^-      _wmZ##qoa,,                                                     
                                       .__awwm#Y":____====vSYYXXX##Z#mas,                                                  
                                   ._<awmWm#X1vvvnvnnoooonnvvvvvvv1XXZ#Zqoi.                                               
                                ._awmmWUS1nvnvnvvvnvnvnvnvvvvvvnvnvvvv3X#Zmos,                                             
                              _iwmm#AY1vvnnnvnvnvnnvnvnvvvn2SXXZZ#U#Z#X2X#Z#Xoi.                                           
                            _iqmm#S1nvvnvnvvnvvvIIIIIlliIlIlllIvv1YSX#ZZ2X#UZ#oa.                                          
                           =wmmBSvnvnvnvIIili|i|ii|i||i|i||i|i|i|iiiiI1XoX#Z###Xc                                          
              ____.       =q#mXnvvvIll|i|i|i|i|i|i|i|i|i|ii|i|i|i|i|i|i|lIXZ#Z#Xo;                                         
            =wqmqqqwoai,,.im#SvIliii|i|i|i|i|i|i|i|i|i|i|i|i|i|i|i|i|i|i|iiIX##UX(                                         
           =X#UZ#UZ##Z#mqwoU1i||i|i|i|i|i|i|iiiviiiiliiiiii|i|i|i|i|i|i|i|iii3UZXc                                         
           vXZ##Z##Z##Z#Z#Zmooviiiiiiiiii|iiiiI3XU#UZUZr-=2^-+++++++||v%iii|iiXZo'                                         
           {XZ#Z#UZ#UZ#UUU#Z##mXqqqqqqqwo2++vaasivX#U#Z(_Z`<gQm/ . --.-?$mc-{ouS(                                          
           )o#Z##ZX#Z##Z#Z#Z##ZZX??!"""--.+?S#Z#ZmXUZ#U##k dQQQf _s,  -. )Qa.)#o,                                          
           -1XZ#Z#XX#Z#UUUUX#ZZa%: __wwwgggw,+X#Z#Z##Z#Z#Zc"??" =$H(    - +Qc.X#X>                                         
            -1X##Z#X2XZ#Z#Za%|}~ _yWV!^~-+"?HqZ##Z##Z#UUZ#Zc.;..         : 3f_m#ZX>                                        
             -{XZ##UUX2XXXY!!"` jWY=awwc  -..+YZ#U#Z#Z#Z##U#qc.:.      ..  =<d#Z#Uo;                                       
               ~{X#Z#Z#qXXowu( <W(_QWWW[     : ]#Z#Z##ZZXXXXXX#wai_s_i_%_aw###Z##ZX(                                       
                 "*XZ##Z#ZZ|_c jW.-YYT" vyw.  :-X##UXSXZ##UZSd#ZZ##ZXZmq#mX#Z#U#Z#S(                                       
                   -!1XXUU####,+Qc :    -"~   - 3#Z#XZXXXZ#UZ#ZXXSXqZ#ZUZ#Z##Z#Z#Xe`                                       
                      -"*1SSXX6.]m> :        . .mZ##U####ZZXXoqqZ#Z#UU#Z##Z#Z#UUXe`                      ___iiii=>,        
                          -{ooon,"Vw,:..    - _w#UUXXUXX2XqmX##Z#Z#Z#Z#U#Z##UUZSos__.               ._sawqmZ#ZZZ#mXa,      
                           =2S22Sas=?!=:...__wm##Z#X2XqZ#UZZ#Z#U##U#Z#UZ#Z#ZZXoXZZmqwos,         _=uqmZZ#ZZ##U##ZZUZXs.    
                           ivvSo2oXXmowuwuq#m##Z#UU#ZUZ#UZ##Z##Z#ZUZ##Z##ZZXSX####ZZ#Z#ma=.   ._uX##ZUZ##U#Z#Z#Z#####Xa.   
                          .>illv1SooXXZ#Z#Z#Z#U#Z#Z#Z##UZ##Z##Z#Z#U#Z#ZXXSXmX#ZUZ#Z###ZZ#ma,_iumZ#Z##U##Z#Z##Z##Z#ZUZ#Za,  
                          =|=i+illIv1o2XXXqXqXXXXX#Z##Z##UZ##Z#Z#XXXXXqmZ#XX#U#Z##U#Z#U#ZZ#mo2XZ###Z#Z#Z#Z##Z##Z##Z##Z#Xa. 
            .....         --:|==+|inwmZ#U#Z#Z#UZ#qXXX2XX2XSSSSXXqqZ##UZUZ#Zm2XZ##Z#Z#Z#Z##ZZ#moXX#Z#UUUUU#UZ#UZ#UZ##Z###X; 
        __awwqqwwoas,_.     ->==<iwmXZ#Z#Z##UUZ##Z#XXXZZZZZ#Z#Z#Z##Z#Z##UU#Z#moXX#UU#UU#Z###ZZ##UZ#UZ#Z#Z#Z##Z##Z#ZZXXS1"` 
     .<um##UZ#ZXZ##Z#moa,,   ==inmXZ##U#Z#UZ#Z##Z#Z#Z######Z#Z##Z#Z##UUZ#Z#Z#Z#moX#ZUZ#Z##Z###Z#Z##Z##UU#Z##Z#XX1!""--     
   .<wmZ#Z#Z#Xo#Z#Z##Z##mXa,, )XmX##Z#Z#U#Z##Z#Z###Z##Z#ZUZ###Z##Z##Z#Z##Z##Z#Z#UX2X##Z##Z#Z#Z##Z#Z##Z#Z#Z#X1!~-           
  .uXZUZ##Z#XX#Z##U#Z#UZUZ#moao#Z#Z##Z#UZ#UUZ###Z#Z#XSX#Z##Z#Z#UZ##Z#Z##Z##Z###Z##moXXX#Z##UUUUZ###Z#UZ#Xe(`               
  vX##U#Z#Xo#Z#UUZ#Z#Z##Z#ZZZXXX#Z##Z##Z#UZ##Z#Z#ZSoXmZ#U#Z##Z#Z##Z###Z#UUZ#UZ#Z#ZZ#on>!YXZUZ#Z##Z#UZXe!~                  
 :XZ#ZUZXXmZ##Z#Z#UU#UUZ#####ZXo##Z#Z#Z##Z#UZ#ZZS}^{nXZ#Z#Z#Z###Z#UUZ#Z#Z##Z##Z##U#Z#Xn. -"!YSXXXXS*"`                     
 -nX#XXqZ#Z#UZ##Z#Z#Z#Z##Z#Z#UmXZ#U#U#U#Z##Z#Xo}`   {2#Z#U###Z#Z##Z#UU#U#Z#UUZ##Z#Z##ZXn.     ---                          
  -"!?XXUZ#Z##Z##U#Z#U#Z#Z#UZ#ZZ#Z#Z#Z#Z#UZX1"`     -Sn##Z#ZU#Z##Z#Z#Z#Z#UZ#Z##Z#Z##Z#ZXs                                  
       -"!1XX#UZ#Z##Z#Z##U#Z##Z###Z#UZ#UZX*^         )oZ#UZ#UZ##Z#U#Z#UUZ##Z##Z#U#Z#U#Zmn>                                 
           -"!1XX#Z#U#UUZ#Z##Z##Z#U#Z#ZS*`           -nX#Z##Z##Z#UZ##Z#Z##Z##Z#UZ##Z#Z#ZXn,                                
               -"*SXXUZ##Z#UZ#UZ#Z#Z#X}`              {X##Z##Z#UUZ#UZ###Z#UZ#UUZ#UZ##Z###Xc                                
                   -"!?XXZ#Z#UZ##UZX!`                )nX#UUZ##Z##Z##Z#Z#UZ##Z##Z##Z##Z#ZXn;                               
                        -^"!!?YY*!"`                  :oX#Z##Z#Z#Z##Z##Z#Z##Z#Z##Z##Z#UU##X(                               
                                                      :oX##Z#U#U#UUZ#UZ###Z##Z##Z#UZ#Z#Z#ZXn.                              
                                                      :2X#Z#UZ#Z#Z##Z##Z#Z##Z##Z#Z##Z##UZ##o;                              
		//===========================================\\
		||========----------END PONY---------========||
		\\===========================================//	

*/

}

