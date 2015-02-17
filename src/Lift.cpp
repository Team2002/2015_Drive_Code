#include "Lift.h"
#include "WPILib.h"
#include "Constants.h"

Lift::Lift(){
	Arm = new DoubleSolenoid(PORT_1_ARM_SOLENOID, PORT_2_ARM_SOLENOID);
	Claw = new DoubleSolenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
	ArmTimer = new Timer();
	ClawTimer = new Timer();
	
	arm_button_already_pressed = false;
	claw_button_already_pressed = false;
	arm_forward = false;
	claw_forward = false;
}

Lift::~Lift(){
	delete Arm;
	delete Claw;
	delete ArmTimer;
	delete ClawTimer;
}


void Lift::SetArmReverse(){
	Arm->Set(DoubleSolenoid::kReverse);
}


void Lift::SetClawReverse(){
	Claw->Set(DoubleSolenoid::kReverse);
}


void Lift::ToggleUpDown(bool button_pressed){
	if(button_pressed && !arm_button_already_pressed){
		arm_button_already_pressed = true;
		if(arm_forward){
			Arm->Set(DoubleSolenoid::kReverse);
			arm_forward = false;
		}else{
			Arm->Set(DoubleSolenoid::kForward);
			arm_forward = true;
		}
		ArmTimer->Reset();
		ArmTimer->Start();
	}else if(!button_pressed && arm_button_already_pressed){
		arm_button_already_pressed = false;
	}
	if(ArmTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		Arm->Set(DoubleSolenoid::kOff);
		ArmTimer->Stop();
		ArmTimer->Reset();
	}
}


void Lift::ToggleInOut(bool button_pressed){
	if(button_pressed && !claw_button_already_pressed){
		claw_button_already_pressed = true;
		if(claw_forward){
			Claw->Set(DoubleSolenoid::kReverse);
			claw_forward = false;
		}else{
			Claw->Set(DoubleSolenoid::kForward);
			claw_forward = true;
		}
		ClawTimer->Reset();
		ClawTimer->Start();
	}else if(!button_pressed && claw_button_already_pressed){
		claw_button_already_pressed = false;
	}
	if(ClawTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		Claw->Set(DoubleSolenoid::kOff);
		ClawTimer->Stop();
		ClawTimer->Reset();
	}
}
