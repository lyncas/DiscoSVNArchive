#pragma config(Sensor, in1,    PotArm,              sensorPotentiometer)
#pragma config(Sensor, in2,    DetectTube,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  BaseSonar,           sensorSONAR_cm)
#pragma config(Sensor, dgtl11, ArmUp,               sensorTouch)
#pragma config(Sensor, dgtl12, ArmDown,             sensorTouch)
#pragma config(Motor,  port1,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           ArmRL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmLU,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           SuckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           SuckL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          DriveLB,       tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
//#include "delta_lib_v3.c" //Main Funtion Library
//#include "PIDController.c"

#define FULL 127
#define AutonFULL 100
//---------------------
typedef struct {
	int k_P;
	int k_I;
	int k_D;

	bool enabled;

	int minInput;
	int maxInput;
	int minOutput;
	int maxOutput;
	int maxError;

	int setpoint;
	int result;
	int input;
	int error;
	int prevError;
	int totalError;

	int inputSensorIndex;
	int outputMotorIndex;
} PIDController;

void init(PIDController controller) {
	controller.k_P = 0;
	controller.k_I = 0;
	controller.k_D = 0;
	controller.enabled = false;
	controller.minInput = 0;
	controller.maxInput = 0;
	controller.minOutput = -127;
	controller.maxOutput = 127;
	controller.maxError = 0;
	controller.totalError = 0;
	controller.prevError = 0;
}

void init(PIDController controller, int inputIndex) {
	init(controller);
	controller.inputSensorIndex = inputIndex;
}

void init(PIDController controller, int inputIndex, int outputIndex) {
	init(controller);
	controller.inputSensorIndex = inputIndex;
	controller.outputMotorIndex = outputIndex;
}

void enable(PIDController controller) {
	controller.enabled = true;
}

void disable(PIDController controller) {
	controller.enabled = false;
}

void setMaxError(PIDController controller, int maxError) {
	if(maxError >= 0);
	controller.maxError = maxError;
}

bool onTarget(PIDController controller) {
	int error = abs(controller.setpoint - SensorValue[controller.inputSensorIndex]);
	if (error <= controller.maxError) {
		return true;
	} else {
		return false;
	}
}

void setSetpoint(PIDController controller, int newSetpoint) {
	controller.setpoint = newSetpoint;
}

void setPIDs(PIDController controller, int kP, int kI, int kD) {
	controller.k_P = kP;
	controller.k_I = kI;
	controller.k_D = kD;
}

void setInputRange(PIDController controller, int min, int max) {
	if(max > min) {
		controller.minInput = min;
		controller.maxInput = max;
	}
}

void setOutputRange(PIDController controller, int min, int max) {
	if(max > min && min >= -127 && max <= 127) {
		controller.minOutput = min;
		controller.maxOutput = max;
	}
}

int calculatePID(PIDController controller) {

	if (controller.enabled) {
		controller.input = SensorValue[controller.inputSensorIndex];
		controller.error = controller.setpoint - controller.input;
		            if (abs(controller.error) > (controller.maxInput - controller.minInput) / 2) {
		                if (controller.error > 0) {
		                    controller.error = controller.error - controller.maxInput + controller.minInput;
		                } else {
		                    controller.error = controller.error + controller.maxInput - controller.minInput;
		                }
		            }

		        if ( ((controller.totalError + controller.error) * controller.k_I < controller.maxOutput)
		                && ((controller.totalError + controller.error) * controller.k_I > controller.minOutput) ) {
		            controller.totalError += controller.error;
		        }

		        controller.result = (controller.error / controller.k_P +// inverted and switch from "*" to "/"
                                               controller.totalError / controller.k_I + // inverted and switch from "*" to "/"
                                               (controller.error - controller.prevError) / controller.k_D);
		        controller.prevError = controller.error;

		        if (controller.result > controller.maxOutput) {
		            controller.result = controller.maxOutput;
		        } else if (controller.result < controller.minOutput) {
		            controller.result = controller.minOutput;
		        }
		  return controller.result;
    } else {
    return 0.0;
  }
}

int calculatePID(PIDController controller, int input) {

        if (controller.enabled) {
                controller.input = input;
                controller.error = controller.setpoint - controller.input;
                            if (abs(controller.error) > (controller.maxInput - controller.minInput) / 2) {
                                if (controller.error > 0) {
                                    controller.error = controller.error - controller.maxInput + controller.minInput;
                                } else {
                                    controller.error = controller.error + controller.maxInput - controller.minInput;
                                }
                            }

                        if ( ((controller.totalError + controller.error) * controller.k_I < controller.maxOutput)
                                && ((controller.totalError + controller.error) * controller.k_I > controller.minOutput) ) {
                            controller.totalError += controller.error;
                        }

                        controller.result = (controller.error / controller.k_P +// inverted and switch from "*" to "/"
                                               controller.totalError / controller.k_I + // inverted and switch from "*" to "/"
                                               (controller.error - controller.prevError) / controller.k_D);
                        controller.prevError = controller.error;

                        if (controller.result > controller.maxOutput) {
                            controller.result = controller.maxOutput;
                        } else if (controller.result < controller.minOutput) {
                            controller.result = controller.minOutput;
                        }
                  return controller.result;
    } else {
    return 0.0;
  }
}

PIDController arm;

//---------------------
//-------------------------------------------| MOTOR SHORTCUTS |---------------------------------------
/*Set Arm Speed*/
void setArmSpeed(int speed) {
  motor[ArmLL] = motor[ArmLU] = motor[ArmRL] = motor[ArmRU] = speed;
}

/*Set Suck Speed*/
void setSuckSpeed(int speed) {
  motor[SuckR] = motor[SuckL] = speed;
}

/*Set Drive Speed: Left & Right*/
void setDriveSpeed(int speed) {
  motor[DriveRF] = motor[DriveRB] = motor[DriveLF] = motor[DriveLB] = speed;
}

/*Set Drive Right Speed*/
void setDriveRSpeed(int speed) {
  motor[DriveRF] = motor[DriveRB] = speed;
}

/*Set Drive Left Speed*/
void setDriveLSpeed(int speed) {
  motor[DriveLF] = motor[DriveLB] = speed;
}

/*Kill Drive Train Motors*/
void killdrive() {
  setDriveSpeed(0);
}
/*Kill Arm Motors*/
void killarm() {
  setArmSpeed(0);
}
/*Kill Suck Motors*/
void killsuck() {
  setSuckSpeed(0);
}


//---------------------------------/ Functions Prototypes /--------------------------------------//
//--------------------------------/                        /-------------------------------------//
//-------------------------------/                          /------------------------------------//
/*void drive(int driveSpeed, float r);
void drive_suck(int driveSpeed, int suckSpeed, float r);
void turn_left(int, driveSpeed, float r);
void turn_right(int, driveSpeed, float r);
void raise_arm(int armSpeed, int finalPos);
void lower_arm(int armSpeed, int finalPos);
void suck(int suckSpeed, int msec);
*/
//--/ PID /-------------------------------------------------------/

int startpoint = 0;
int goal_value = startpoint;
int change = -1000;
int k_P = 10;
int k_I = 0;
int k_D = 0;

//--/ Dead Zone /-------------------------------------------------/
int DeadZone = 10; //dead zone value for joysticks

//--/ Arm Position /----------------------------------------------/
int low_descore;
int low_lock;
int high_descore;
int high_lock;

//--Declare Global Variables--------------------------------------/
/* 'rotations' will be a counter for every 360 encoder clicks */
/* which is one full rotation of the wheel (ie. 2 'rotations' */
/* will equal 720.0 clicks, 2 full rotations of the wheel).   */
const float rotations = 360.0;

//---------------------------------/ Pre Autonomous /-------------------------------------------//
//--------------------------------/                  /------------------------------------------//
//-------------------------------/                    /-----------------------------------------//

//---------------------------------/ Library /-------------------------------------------------//
//--------------------------------/           /------------------------------------------------//
//-------------------------------/             /-----------------------------------------------//

//--| FORWARD |---------------------------------------------
void drive(int driveSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL] = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (r * rotations) ie (3.0 * 360.0) or "three rotations"
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] < (r * rotations))
  {
    setDriveSpeed(driveSpeed); /* Run all motors */ /* at driveSpeed. */
  }
  killdrive();
}
//----------------------------------------------------------------------------------------------------

//--------------------------------------------| FORWARD + SUCK |---------------------------------------------
void drive_suck(int driveSpeed, int suckSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for     */
  SensorValue[EncoderL] = 0;    /* consistancy and accuracy. */
  // While the encoders have not yet met their goal: (r * rotations) ie (3.0 * 360.0) or "three rotations"
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] < (r * rotations))
  {
    setDriveSpeed(driveSpeed);
    setSuckSpeed(suckspeed);
  }
  killdrive();
  killsuck();
}
//--------------------------------------------| Arc |---------------------------------------------
void drive_arc(int rightSpeed, int leftSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL] = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (r * rotations) ie (3.0 * 360.0) or "three rotations"
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] < (r * rotations))
  {
    setDriveRSpeed(rightSpeed);
    setDriveLSpeed(leftSpeed);
  }
  killdrive();
}
//-------------------------------------------| TURN LEFT |--------------------------------------------
void turn_left(int driveSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL]  = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (left is compared negativly since it will in reverse)
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] > (-1 * r * rotations))
  {
    setDriveRSpeed(driveSpeed);
    setDriveLSpeed(-driveSpeed);
  }
  killdrive();
}
//-------------------------------------------| TURN RIGHT |-------------------------------------------
void turn_right(int driveSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL]  = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (left is compared negativly since it will in reverse)
  while(SensorValue[EncoderL] < (r * rotations) && SensorValue[EncoderR] > (-1 * r * rotations))
  {
    setDriveRSpeed(-driveSpeed);
    setDriveLSpeed(driveSpeed);


  }
  killdrive()
}
//-------------------------------------------| MOVE ARM |---------------------------------------------
void move_arm(int armSpeed, int target)
{
  //Upper limit is 610, lower limit is 990
  //While the pot value is greater than +5 of the target, or less than -5 of the target...

  while(SensorValue(PotArm) > target + 5 || SensorValue(PotArm) < target - 5)
  {
    //If the pot value is greater than the target...move the arm up
    if (SensorValue(PotArm) > target)
    {
      setArmSpeed(-armSpeed);
      //motor[port5] = (speed) + 35;
      //motor[port6] = (speed * -1) + 35;
    }
    //If the pot value is less than the target...move the arm down
    if (SensorValue(PotArm) < target)
    {
      setArmSpeed(armSpeed);
      //motor[port5] = (speed * -1) + 35;
      //motor[port6] = (speed) + 35;
    }
  }
  setArmSpeed(0);
  //motor[port5] = 15;
  //motor[port6] = -15;
}
//-------------------------------------------| RAISE ARM |---------------------------------------------
void raise_arm(int armSpeed, int finalPos)
{
  if (SensorValue[PotArm] < finalPos){
    motor[ArmRU] = armSpeed;
    motor[ArmRL] = armSpeed;
    motor[ArmLU] = armSpeed;
    motor[ArmLL] = armSpeed;
  }
  else {/*Zero Arm Motors*/
    motor[ArmRU] = 0;
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmLL] = 0;
  }
}
//-------------------------------------------| LOWER ARM |---------------------------------------------
void lower_arm(int armSpeed, int finalPos)
{
  if (SensorValue[PotArm] > finalPos) {
    motor[ArmRU] = -armSpeed;
    motor[ArmRL] = -armSpeed;
    motor[ArmLU] = -armSpeed;
    motor[ArmLL] = -armSpeed;
  }
  else {/*Zero Arm Motors*/
      killarm();
  }
}
//-------------------------------------------| SUCK |--------------------------------------------------
void Suck(int suckSpeed, int msec) {
  setSuckSpeed(suckSpeed);
  wait1Msec(msec);
  killsuck();
}
//-------------------------------------------| Dead Zone |-------------------------------------------
int checkDeadZone(int x) {
  if (abs(x) < DeadZone) {
    return 0;
    } else {
    if (x < 0)
      return (x + DeadZone)*(FULL / (FULL - DeadZone)
    else
      return (x - DeadZone)*(FULL / (FULL - DeadZone)
  }
}

void pre_auton()
{
  //--/ Encoders /-------------------------/
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;

  //--/ Arm Points /-----------------------/
  //goal_value = startpoint + change;
  startpoint/*arm_grounded*/ = SensorValue[PotArm];  // sets ground point           (0 inches)
  low_descore = startpoint + 1556 - 1247;          // sets low descore arm point  (4.5 inches)
  low_lock = startpoint+ 2326 - 1247;             //...lowgoal                   (15 inches)
  high_descore = startpoint + 1879- 1247;          //...high descore              (x inches)
  high_lock = startpoint + 2599 - 1247;            // ...high goal                (18.5 inches)

  //--/ PID /------------------------------/
  init(arm);

  setPIDs(arm, k_P, k_I, k_D);
  setSetpoint(arm, goal_value);

  enable(arm);

  arm.k_P = 10;
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

//---------------------------------/ Autonomous /-----------------------------------------------//
//--------------------------------/              /----------------------------------------------//
//-------------------------------/                /---------------------------------------------//

task autonomous()
{
  while(true)		// Creates an infinite loop, since "true" always evaluates to true
  {
    int i;
    for(i=0; i<4; i++)      // While 'i' is less than 4:
    {
      drive_suck(AutonFULL, FULL, 3.0);//drive forward and inhale redstack, scoring cheater tube
      //move_arm(FULL, 2326);//raise arm
      setSetPoint(arm, low_lock);//raise arm
      turn_left(AutonFULL, 3.0);//turn to face goal
      drive(AutonFULL, 3.0);// drive to goal
      //move_arm(FULL, 1556);//score tubes
      setSetPoint(arm, low_descore);//score tubes
      drive_suck(AutonFULL, -FULL, 3.0);//back up while exhaling
      turn_left(AutonFULL, 3.0);//turn around to face blue stack
      drive_suck(AutonFULL, FULL, 3.0);//drive to and inhale blue stack
      //arc(-AutonFULL, -FULL, 3.0);// drive back wards in an arc to tower
      turn_left(AutonFULL, 3.0);// turn left away put parallel to tower
      drive(-AutonFULL, 3.0);// back up, parallel to tower
      turn_right(AutonFULL, 3.0);// turn right to face tower
      //move_arm(127, low_lock)//raise arm
      setSetPoint(arm, low_lock);//raise arm
      drive(AutonFULL, 3.0);//drive up against tower
      suck(FULL,1500);//spit tubes into tower
    }
  }//while
}//task auto

//---------------------------------/ User Control /---------------------------------------------//
//--------------------------------/                /--------------------------------------------//
//-------------------------------/                  /-------------------------------------------//

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
  pre_auton();
    //--/ Manual_Arm /------------------------------/
    //if(checkDeadZone(vexRT[Ch3]) != 0) {
    if (vexRT[Ch3] > 10 || (vexRT[Ch3]) < -15){
        setArmSpeed(vexRT[Ch3]);
    }

else {
  if (vexRT[Btn7U] == 1) {
   //setSetPoint(arm, low_lock);
   setArmSpeed(calculatePID(arm, SensorValue[PotArm]));
 }
      //}
      /*else if (vexRT[Btn7D] == 1) {
        //setSetPoint(arm, low_descore);
        calculatePID(arm, low_descore);
      }
      else if (vexRT[Btn6U] == 1) {
        //setSetPoint(arm, high_descore);
        calculatePID(arm, high_descore);
      }
      else if (vexRT[Btn6D] == 1) {
        //setSetPoint(arm, high_lock);
        calculatePID(arm, high_lock);
      }
     */
    }

    //--/ INHALE /----------------------------------/
    switch(vexRT[Btn5U] - vexRT[Btn5D])
    {
    case  1:motor[SuckR] = FULL;
      motor[SuckL] = FULL;
      break;
    case -1:motor[SuckR] = -FULL;
      motor[SuckL] = -FULL;
      break;
    case  0:motor[SuckR] = 0;
      motor[SuckL] = 0;
      break;
    }//: switch

    //--/ Drive_Train /---------------------------/
    setDriveRSpeed((vexRT[Ch2] - vexRT[Ch1]));// (y + x)
    setDriveLSpeed((vexRT[Ch2] + vexRT[Ch1]));// (y - x)
  }
}
