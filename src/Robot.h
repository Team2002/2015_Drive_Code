#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED


#include "WPILib.h"
#include "Constants.h"
#include "Drive.h"
#include "Lift.h"
#include "Intake.h"
#include "Macro.h"


class Robot: public SampleRobot{
public:
	Robot();
	~Robot();

	void RobotInit(void);
	void Autonomous(void);
	void OperatorControl(void);
	
private:
	Macro* o_Macro;
	Joystick* o_Joysticks[NUMBER_OF_JOYSTICKS];
	Compressor* o_Compressor;
	Drive* o_Drive;
	Intake* o_Intake;
	Lift* o_Lift;
};


#endif /* ROBOT_H__INCLUDED */
