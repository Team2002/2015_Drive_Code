#include "Intake.h"
#include "WPILib.h"
#include "Constants.h"


Intake::Intake(){
	Clamp = new DoubleSolenoid(PORT_1_CLAMP_SOLENOID, PORT_2_CLAMP_SOLENOID);
	ClampTimer = new Timer();
	LeftMotor = new Talon(PORT_LEFT_INTAKE_TALON);
	RightMotor = new Talon(PORT_RIGHT_INTAKE_TALON);
	
	clamp_button_already_pressed = false;
	clamp_forward = false;

	Clamp->Set(DoubleSolenoid::kReverse);
}


Intake::~Intake(){
	delete Clamp;
	delete ClampTimer;
	delete LeftMotor;
	delete RightMotor;
}


void Intake::Toggle(bool button_pressed){
	if(button_pressed && !clamp_button_already_pressed){
		clamp_button_already_pressed = true;
		if(clamp_forward){
			Clamp->Set(DoubleSolenoid::kReverse);
			clamp_forward = false;
		}else{
			Clamp->Set(DoubleSolenoid::kForward);
			clamp_forward = true;
		}
		ClampTimer->Reset();
		ClampTimer->Start();
	}else if(!button_pressed && clamp_button_already_pressed){
		clamp_button_already_pressed = false;
	}
	if(ClampTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		Clamp->Set(DoubleSolenoid::kOff);
		ClampTimer->Stop();
		ClampTimer->Reset();
	}
}


void Intake::Set(int left_state, int right_state){
	if(left_state == 1)
		LeftMotor->Set(INTAKE_SPEED);
	else if(left_state == 2)
		LeftMotor->Set(-INTAKE_SPEED);
	else if(left_state == 0)
		LeftMotor->Set(0);
	
	if(right_state == 1)
		RightMotor->Set(INTAKE_SPEED);
	else if(right_state == 2)
		RightMotor->Set(-INTAKE_SPEED);
	else if(right_state == 0)
		RightMotor->Set(0);
}
