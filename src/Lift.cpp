#include "Lift.h"
#include "WPILib.h"
#include "Config.h"


Lift::Lift(void){
	Arm = new DoubleSolenoid(PORT_1_ARM_SOLENOID, PORT_2_ARM_SOLENOID);
	Claw = new DoubleSolenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
	ArmTimer = new Timer();
	ClawTimer = new Timer();
	
	arm_button_already_pressed = false;
	claw_button_already_pressed = false;
	arm_forward = false;
	claw_forward = false;
}


Lift::~Lift(void){
	delete Arm;
	delete Claw;
	delete ArmTimer;
	delete ClawTimer;
}


void Lift::SetArm(int state){
	if(state == 0){
		Arm->Set(DoubleSolenoid::kReverse);
		SmartDashboard::PutBoolean(" ARM", false);
	}else if(state == 1){
		Arm->Set(DoubleSolenoid::kForward);
		SmartDashboard::PutBoolean(" ARM", true);
	}
	
	ArmTimer->Reset();
	ArmTimer->Start();
}


void Lift::ToggleArm(bool button_pressed){
	if(button_pressed && !arm_button_already_pressed){
		arm_button_already_pressed = true;
		if(arm_forward){
			Arm->Set(DoubleSolenoid::kReverse);
			arm_forward = false;
			SmartDashboard::PutBoolean(" ARM", false);
		}else{
			Arm->Set(DoubleSolenoid::kForward);
			arm_forward = true;
			SmartDashboard::PutBoolean(" ARM", true);
		}
		ArmTimer->Reset();
		ArmTimer->Start();
	}else if(!button_pressed && arm_button_already_pressed){
		arm_button_already_pressed = false;
	}
}


void Lift::CheckArm(void){
	if(ArmTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		Arm->Set(DoubleSolenoid::kOff);
		ArmTimer->Stop();
		ArmTimer->Reset();
	}
}


void Lift::SetClaw(int state){
	if(state == 0){
		Claw->Set(DoubleSolenoid::kReverse);
		SmartDashboard::PutBoolean(" CLAW", false);
	}else if(state == 1){
		Claw->Set(DoubleSolenoid::kForward);
		SmartDashboard::PutBoolean(" CLAW", true);
	}
	
	ClawTimer->Reset();
	ClawTimer->Start();
}


void Lift::ToggleClaw(bool button_pressed){
	if(button_pressed && !claw_button_already_pressed){
		claw_button_already_pressed = true;
		if(claw_forward){
			Claw->Set(DoubleSolenoid::kReverse);
			claw_forward = false;
			SmartDashboard::PutBoolean(" CLAW", false);
		}else{
			Claw->Set(DoubleSolenoid::kForward);
			claw_forward = true;
			SmartDashboard::PutBoolean(" CLAW", true);
		}
		ClawTimer->Reset();
		ClawTimer->Start();
	}else if(!button_pressed && claw_button_already_pressed){
		claw_button_already_pressed = false;
	}
}


void Lift::CheckClaw(void){
	if(ClawTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		Claw->Set(DoubleSolenoid::kOff);
		ClawTimer->Stop();
		ClawTimer->Reset();
	}
}
