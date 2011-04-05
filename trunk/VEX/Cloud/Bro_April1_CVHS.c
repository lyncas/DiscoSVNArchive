#pragma config(Sensor, in1,    armPot,              sensorPotentiometer)
#pragma config(Sensor, in2,    clawPot,             sensorPotentiometer)
#pragma config(Sensor, in3,    LineFollowTL,        sensorNone)
#pragma config(Sensor, in4,    LineFollowTR,        sensorNone)
#pragma config(Sensor, in5,    LineFollowC,         sensorNone)
#pragma config(Sensor, in6,    LineFollowBL,        sensorNone)
#pragma config(Sensor, in7,    LineFollowBR,        sensorNone)
#pragma config(Sensor, dgtl1,  rightEnc,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEnc,             sensorQuadEncoder)
#pragma config(Motor,  port1,           backleft,      tmotorNormal, openLoop)
#pragma config(Motor,  port2,           left,          tmotorNormal, openLoop)
#pragma config(Motor,  port3,           armright1,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           armleft1,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           claw,          tmotorNormal, openLoop)
#pragma config(Motor,  port7,           armleft2,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           armright2,     tmotorNormal, openLoop)
#pragma config(Motor,  port9,           right,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          backright,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  LineFollowBL, LineFollowBR, LineFollowC, lineFollowTL, LineFollowTR are all sensors for following the line with the sensors set up in an "X" configuration. The "X" configuration is for more
  advanced line following and until we need it, only three will be used in normal line following (lineFollowTL, LineFollowC, and LineFollowTR
*/

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void pre_auton()
{

}

/****************************************************************************************DRIVING FUNCTIONS*****************************************************************************************/
int leftDrivePower, rightDrivePower, x, y, rampLimit = 5, leftDrivePrevious, rightDrivePrevious;//drivetrain variables


void resetDriveVariables(){
  leftDrivePower = rightDrivePower = x = y = leftDrivePrevious = rightDrivePrevious = 0;
}

void setDriveMotors(){
  motor[left] = leftDrivePower;
  motor[backleft] = leftDrivePower;
  motor[right] = rightDrivePower;
  motor[backright] = rightDrivePower;
}

void stopDrive(){
  rightDrivePower = leftDrivePower = 0;
  setDriveMotors();
}

void driveTank(int left, int right, bool square, bool ramp){
  if(square){
    if(left!=0){
      leftDrivePower = ((left*left)/128)*(left/abs(left));
    }
    else{
      leftDrivePower = 0;
    }

    if(right!=0){
      rightDrivePower = ((right*right)/128)*(right/abs(right));
    }
    else{
      rightDrivePower = 0;
    }
  }
  else{
    leftDrivePower = left;
    rightDrivePower = right;
  }

  if(ramp == true){//ramping code by taking a running average of the past two motor values and the current motor value and averaging the three together

  }

  setDriveMotors();
}

void driveArcade(int power, int turn, bool square, bool ramp){
  if(square){
    if(power != 0){
      y = ((power*power)/128)*(power/abs(power));
    }
    else{
      y = 0;
    }

    if(turn!=0){
      x = ((turn*turn)/128)*(turn/abs(turn));
    }
    else{
      x = 0;
    }
  }
  else{
    y = power;
    x = turn;
  }

  leftDrivePower = y+x;
  rightDrivePower = y-x;

  if(ramp == true){//ramping code by taking a running average of the past two motor values and the current motor value and averaging the three together.
    if(abs(rightDrivePower) > abs(rightDrivePrevious) + rampLimit){
      if(rightDrivePower > (rightDrivePower + rampLimit)){
        rightDrivePower = rightDrivePrevious + rampLimit;
      }
      else{
        rightDrivePower = rightDrivePrevious - rampLimit;
      }
    }

    if(abs(leftDrivePower) > abs(leftDrivePrevious) + rampLimit){
      if(leftDrivePower > (leftDrivePower + rampLimit)){
        leftDrivePower = leftDrivePrevious + rampLimit;
      }
      else{
        leftDrivePower = leftDrivePrevious - rampLimit;
      }
    }
  }

  setDriveMotors();

  leftDrivePrevious = leftDrivePower;
  rightDrivePrevious = rightDrivePower;
}
/*******************************************************************************************Arm & Claw Code****************************************************************************************/
int armPower, clawPower, armPosition, clawPosition, armTolerance, clawTolerance, initialArmPosition, initialClawPosition, armOffset, clawOffset;//arm and claw tolerance to be set
int armFloor = 2213, armLowPlace = 3079, armLowScore = 2472, armHighPlace = 3303, armHighScore = 2872, armMax = 3845;//arm positions. Place is position above goal, Score is on goal for tubes, floor is start position
int clawOpen = 2253, clawClosed = 3616, clawGuiding = 2989;//claw positions. Open is initial position, close is closed on tubes, Guiding is open slightly to better align on tubes for close
int armInput, clawInput;//arm variables used in competitions code. Placed here to keep them with the rest of the arm variables
bool armPositionReached, clawPositionReached;
/*
  setInitialPosition() is used to save the beginning values of the arm and claw at the start of the program. The program will assume that the arm and claw start out with the arm at the lowest
  point and the claw to be fully open. This will allow for relative positions of the arm and claw throughout programs to account for any possible shift in the potentiometers.
  Possible addition is to add a limitswitch to the bar that is the physical limit for the arm to reset the initial position of the arm whenever the arm is fully lowered to account for any
  possible shift of the potentiometer during the match. (STILL TO BE DONE, NOT NECESSARY BUT WOULD BE NICE)
*/
void setInitialPosition(){
  initialArmPosition = SensorValue[armPot];
  initialClawPosition = SensorValue[clawPot];

  armOffset = armFloor - initialArmPosition;
  clawOffset = clawOpen - initialClawPosition;
}

void setArmPosition(){
  initialArmPosition = SensorValue[armPot];

  armOffset = armFloor - initialArmPosition;
}

void setArmMotors(){
  motor[armleft1] = motor[armleft2] = motor[armright1] = motor[armright2] = armPower;
  motor[claw] = clawPower;
}

bool armMove(int aPower, int cPower, int armPos, int clawPos){//basic controls right now. Should be replaced with a proper PID loop control on the arm position when the programmer isn't tired.
  if((SensorValue[armPot] <= (armPos - armTolerance))||(SensorValue[armPot] >= (armPos + armTolerance))){
    armPower = ((armPos - armPot)/armPos) * aPower;
    armPositionReached = false;
  }
  else{
    armPower = 0;
    armPositionReached = true;
  }

  if((SensorValue[clawPot] <= (clawPos - clawTolerance))||(SensorValue[clawPot] >= (clawPos + clawTolerance))){
    clawPower = ((clawPos - clawPot)/clawPos) * cPower;
    clawPositionReached = false;
  }
  else{
    clawPower = 0;
    clawPositionReached = true;
  }

  setArmMotors();
  return clawPositionReached && armPositionReached;
}

void armMove(int aPower, int cPower){
  armPower = aPower;
  clawPower = cPower;
  setArmMotors();
}

/*****************************************************************************************Competition Code*****************************************************************************************/
task autonomous()
{
  time1[T1] = 0;
  while(time1[T1] < 1500){
    driveArcade(128,0,false,false);//leave both square and ramp as false until the code is proven to work
  }
  stopDrive();
}

task usercontrol()
{
  resetDriveVariables();
	while (true)
	{
    driveArcade(vexRT[Ch3],vexRT[Ch4],true,true);//leave both square and ramp as false until the code is proven to work

    if (vexRT[Btn6U] != 0 ||vexRT[Btn5U] != 0 )
      clawInput = 110;
    else if(vexRT[Btn6D] != 0 || vexRT[Btn5D] != 0)
      clawInput = -63;
    else
      clawInput = 0;

    armMove(vexRT[Ch2], clawInput);
	}
}