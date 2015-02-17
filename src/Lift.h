#ifndef LIFT_H__INCLUDED
#define LIFT_H__INCLUDED


#include "WPILib.h"


class Lift{
public:
	Lift();
	~Lift();
	
	void SetArmReverse();
	void SetClawReverse();

	void ToggleUpDown(bool);
	void ToggleInOut(bool);
	
private:
	DoubleSolenoid* Arm;
	DoubleSolenoid* Claw;
	Timer* ArmTimer;
	Timer* ClawTimer;
	
	bool arm_button_already_pressed, claw_button_already_pressed, arm_forward, claw_forward;
};


#endif /* LIFT_H__INCLUDED */
