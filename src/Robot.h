#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED


#include "WPILib.h"
#include "Constants.h"
#include "Drive.h"
#include "Lift.h"
#include "Macro.h"


class Robot: public SampleRobot{
public:
	Robot(void);
	~Robot(void);

	void RobotInit(void);        // Each of these functions is called once when the robot enters that state
	void Autonomous(void);
	void OperatorControl(void);
	
private:
	Macro* o_Macro;                             // o_ has been appended to the beginning of each object to avoid naming conflicts (o for object)
	PowerDistributionPanel* o_PowerDist;
	Joystick* o_Joysticks[NUMBER_OF_JOYSTICKS];
	Compressor* o_Compressor;
	Drive* o_Drive;
	Lift* o_Lift;
};


#endif /* ROBOT_H__INCLUDED */
