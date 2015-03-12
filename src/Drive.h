#ifndef DRIVE_H__INCLUDED
#define DRIVE_H__INCLUDED


#include "WPILib.h"


class Drive{
public:
	Drive(void);
	~Drive(void);
	
	int Set(float, float);
	
private:
	Talon* LeftMotor1;
	Talon* LeftMotor2;
	Talon* RightMotor1;
	Talon* RightMotor2;
	Encoder* LeftEncoder;
	Encoder* RightEncoder;

	int distance_since_last;
};


#endif /* DRIVE_H__INCLUDED */
