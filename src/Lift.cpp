//Include header files
#include "Lift.h"
#include "WPILib.h"
#include "Config.h"

//Declare Lift function
Lift::Lift(void){
	//Create Arm/Claw objects
	Arm = new DoubleSolenoid(PORT_1_ARM_SOLENOID, PORT_2_ARM_SOLENOID);
	Claw = new DoubleSolenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
	ArmTimer = new Timer();
	ClawTimer = new Timer();
	
	//Set variables
	arm_button_already_pressed = false;
	claw_button_already_pressed = false;
	arm_forward = false;
	claw_forward = false;
}

//Delete Lift objects
Lift::~Lift(void){
	delete Arm;
	delete Claw;
	delete ArmTimer;
	delete ClawTimer;
}

//Declare SetArm function
void Lift::SetArm(int state){
	if(state == 0){
		//Put it in reverse
		Arm->Set(DoubleSolenoid::kReverse);
		//Send debug information
		SmartDashboard::PutBoolean(" ARM", false);
	}else if(state == 1){
		//Put it in drive
		Arm->Set(DoubleSolenoid::kForward);
		//Send debug information
		SmartDashboard::PutBoolean(" ARM", true);
	}
	
	//Reset and restart timer
	ArmTimer->Reset();
	ArmTimer->Start();
}

//Declare ToggleArm function
void Lift::ToggleArm(bool button_pressed){
	//If you pushed a button and aren't already pushing it
	if(button_pressed && !arm_button_already_pressed){
		//Now you're pushing it
		arm_button_already_pressed = true;
		//If it's in drive...
		if(arm_forward){
			//Put it in reverse
			Arm->Set(DoubleSolenoid::kReverse);
			arm_forward = false;
			//Send debug information
			SmartDashboard::PutBoolean(" ARM", false);
		//If it's in reverse...
		}else{
			//Put it in drive
			Arm->Set(DoubleSolenoid::kForward);
			arm_forward = true;
			//Send debug information
			SmartDashboard::PutBoolean(" ARM", true);
		}
		//Reset and restart timer
		ArmTimer->Reset();
		ArmTimer->Start();
	//Or, if you aren't pushing a button and you were
	}else if(!button_pressed && arm_button_already_pressed){
		//You aren't pushing it anymore
		arm_button_already_pressed = false;
	}
}

//Declare CheckArm function
void Lift::CheckArm(void){
	//If the timer is bigger than the time delay
	if(ArmTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		//Turn off the Double Solenoid
		Arm->Set(DoubleSolenoid::kOff);
		//Stop and reset the timer
		ArmTimer->Stop();
		ArmTimer->Reset();
	}
}

//Declare SetClaw function
void Lift::SetClaw(int state){
	if(state == 0){
		//Put it in reverse
		Claw->Set(DoubleSolenoid::kReverse);
		//Send debug information
		SmartDashboard::PutBoolean(" CLAW", false);
	}else if(state == 1){
		//Put it in drive
		Claw->Set(DoubleSolenoid::kForward);
		//Send debug information
		SmartDashboard::PutBoolean(" CLAW", true);
	}
	//Reset and restart the timer
	ClawTimer->Reset();
	ClawTimer->Start();
}

//Declare ToggleClaw function
void Lift::ToggleClaw(bool button_pressed){
	//If you pushed a button and aren't already pushing it
	if(button_pressed && !claw_button_already_pressed){
		//Now you're pushing it
		claw_button_already_pressed = true;
		//If it's in drive...
		if(claw_forward){
			//Put it in reverse
			Claw->Set(DoubleSolenoid::kReverse);
			claw_forward = false;
			//Send debug information
			SmartDashboard::PutBoolean(" CLAW", false);
		//If it's in reverse...
		}else{
			//Put it in drive
			Claw->Set(DoubleSolenoid::kForward);
			claw_forward = true;
			//Send debug information
			SmartDashboard::PutBoolean(" CLAW", true);
		}
		//Reset and restart the timer
		ClawTimer->Reset();
		ClawTimer->Start();
	//Or, if you aren't pushing a button and you were
	}else if(!button_pressed && claw_button_already_pressed){
		//You aren't pushing it anymore
		claw_button_already_pressed = false;
	}
}

//Declare CheckClaw function
void Lift::CheckClaw(void){
	//If the timer is bigger than the time delay
	if(ClawTimer->Get() >= SOLENOID_STATE_TIME_DELAY){
		//Turn off the Double Solenoid
		Claw->Set(DoubleSolenoid::kOff);
		//Stop and reset the timer
		ClawTimer->Stop();
		ClawTimer->Reset();
	}
}
