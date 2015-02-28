#ifndef DRIVE_H__INCLUDED
#define DRIVE_H__INCLUDED


#include "WPILib.h"


class Drive{
public:
	Drive(void);
	~Drive(void);
	
	void Set(float, float);
	
private:
	Talon* LeftMotor1;
	Talon* LeftMotor2;
	Talon* RightMotor1;
	Talon* RightMotor2;
};


#endif /* DRIVE_H__INCLUDED */