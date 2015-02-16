#ifndef INTAKE_H__INCLUDED
#define INTAKE_H__INCLUDED


#include "WPILib.h"


class Intake{
public:
	Intake();
	~Intake();
	
	void Toggle(bool);
	void Set(int, int);
	
private:
	DoubleSolenoid* Clamp;
	Timer* ClampTimer;
	Talon* LeftMotor;
	Talon* RightMotor;
	
	bool clamp_button_already_pressed, clamp_forward;
};


#endif /* INTAKE_H__INCLUDED */
