#ifndef LIFT_H__INCLUDED
#define LIFT_H__INCLUDED


#include "WPILib.h"


class Lift{
public:
	Lift(void);
	~Lift(void);
	
	void SetArm(int);
	void ToggleArm(bool);
	void CheckArm(void);
	
	void SetClaw(int);
	void ToggleClaw(bool);
	void CheckClaw(void);
	
private:
	DoubleSolenoid* Arm;
	DoubleSolenoid* Claw;
	Timer* ArmTimer;
	Timer* ClawTimer;
	
	bool arm_button_already_pressed, claw_button_already_pressed, arm_forward, claw_forward;
};


#endif /* LIFT_H__INCLUDED */