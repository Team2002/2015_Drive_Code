#ifndef LIFT_H__INCLUDED //Check to see if the variable LIFT_H_INCLUDED has been defined yet
#define LIFT_H__INCLUDED //If variable has not yet been defined, define it


#include "WPILib.h" //Include the WPLib.h library in the program


class Lift{ 
public: //Declare variables available for use in outside programs
	Lift(void);
	~Lift(void);
	
	void SetArm(int);
	void ToggleArm(bool);
	void CheckArm(void);
	
	void SetClaw(int);
	void ToggleClaw(bool);
	void CheckClaw(void);
	
private: //Declare variables that are not able to be accessed from outside programs
	DoubleSolenoid* Arm;
	DoubleSolenoid* Claw;
	Timer* ArmTimer;
	Timer* ClawTimer;
	
	bool arm_button_already_pressed, claw_button_already_pressed, arm_forward, claw_forward;
};


#endif /* LIFT_H__INCLUDED */
