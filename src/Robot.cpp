#include "WPILib.h"
#include "Robot.h"
#include "Constants.h"
#include "Macro.h"
#include <iostream>
#include <string>


Robot::Robot(){
	o_Macro = new Macro();
	o_PowerDist = new PowerDistributionPanel();
	o_Joysticks[0] = new Joystick(PORT_JOYSTICK_1);
	o_Joysticks[1] = new Joystick(PORT_JOYSTICK_2);
	o_Compressor = new Compressor();
	o_Drive = new Drive();
	o_Lift = new Lift();
}


Robot::~Robot(){
	delete o_Macro;
	delete o_PowerDist;
	
	for(int i = 0;i < NUMBER_OF_JOYSTICKS;i++)
		delete o_Joysticks[i];

	delete o_Compressor;
	delete o_Drive;
	delete o_Lift;
}


void Robot::RobotInit(void){
	o_Compressor->Start();
}


void Robot::Autonomous(void){
	// o_Macro->Play(0, o_Drive, o_Lift, o_Compressor);
}


void Robot::OperatorControl(void){
	// o_Macro->StartRecording();

	float y1, x2, left_speed, right_speed;
	bool b_arm, b_claw;

	o_Lift->SetArmReverse();
	o_Lift->SetClawReverse();

	Wait(SOLENOID_STATE_TIME_DELAY);

	while(IsOperatorControl() && IsEnabled()){
		y1 = o_Joysticks[0]->GetRawAxis(AXIS_Y1);
		x2 = o_Joysticks[0]->GetRawAxis(AXIS_X2);
		
		b_arm = o_Joysticks[1]->GetRawButton(BUTTON_ARM);
		b_claw = o_Joysticks[1]->GetRawButton(BUTTON_CLAW);

		left_speed = y1 - x2;
		right_speed = y1 + x2;
		
		o_Drive->Set(left_speed, right_speed);
		o_Lift->ToggleUpDown(b_arm);
		o_Lift->ToggleInOut(b_claw);

		o_Macro->SaveStep(left_speed, right_speed, b_arm, b_claw);

		SmartDashboard::PutNumber("Voltage", o_PowerDist->GetVoltage());
		SmartDashboard::PutNumber("Temperature", o_PowerDist->GetTemperature());

		Wait(CYCLE_TIME_DELAY);
	}

	o_Macro->StopRecording();
}


START_ROBOT_CLASS(Robot);
