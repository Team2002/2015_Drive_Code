#ifndef ROBOT_H__INCLUDED // see if ROBOT_H__INCLUDED is already defined
#define ROBOT_H__INCLUDED // define ROBOT_H__INCLUDED


#include "WPILib.h" // include WPILib.h library
#include "Config.h" // include Config.h library
#include "Drive.h" // include Drive.h library
#include "Lift.h" // include Lift.h library
#include "Macro.h" // include Macro.h library


class Robot: public SampleRobot{
public: // info that is available to all programs
	Robot(void);
	~Robot(void);

	void RobotInit(void);        // Each of these functions is called once when the robot enters that state
	void Autonomous(void);
	void OperatorControl(void);
	
private: // info only available for this program
	Macro* o_Macro;                             // o_ has been appended to the beginning of each object to avoid naming conflicts (o for object)
	PowerDistributionPanel* o_PowerDist;
	Joystick* o_Joysticks[NUMBER_OF_JOYSTICKS];
	Compressor* o_Compressor;
	Drive* o_Drive;
	Lift* o_Lift;
};


#endif /* ROBOT_H__INCLUDED */
