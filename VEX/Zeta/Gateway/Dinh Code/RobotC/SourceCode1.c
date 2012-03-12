#pragma config(Sensor, dgtl1,  sonarSensor,         sensorSONAR_cm)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                 - Forward until Close Proximity -                                  *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to drive forward at half speed until the Ultrasonic Sensor       *|
|*  detects an obstruction within 20 inches of it.                                                    *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  The Ultrasonic Sensor returns a value of '-1' when it is out of range from the nearest      *|
|*        object.  The range is from 0 to 255 inches, so make sure that the robot is within this      *|
|*        range or it may never run.                                                                  *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 9,10 sonarSensor         VEX Sonar Sensor      Front mounted, facing forward     *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);						// Robot waits for 2000 millis54econds before executing program

	while(SensorValue(sonarSensor) > 20  || SensorValue(sonarSensor) == -1)		// Loop while robot's Ultrasonic sensor is further than 20 inches away from an object
	{                                                                         // || (or) it is '-1'.  (-1 is the value returned when nothing is in it's visable range)
		motor[rightMotor] = 63;			// Motor on port2 is run at half (63) power forward
		motor[leftMotor]  = 63;			// Motor on port3 is run at half (63) power forward
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
