#include "WPILib.h"
#include "Robot.h"
#include "Constants.h"
#include "Macro.h"
#include <iostream>
#include <string>


Robot::Robot(void){
	o_Macro = new Macro();
	o_PowerDist = new PowerDistributionPanel();
	o_Joysticks[0] = new Joystick(PORT_JOYSTICK_1);
	o_Joysticks[1] = new Joystick(PORT_JOYSTICK_2);
	o_Compressor = new Compressor();
	o_Drive = new Drive();
	o_Lift = new Lift();
}


Robot::~Robot(void){
	for(int i = 0;i < NUMBER_OF_JOYSTICKS;i++)
		delete o_Joysticks[i];
	
	delete o_Macro;
	delete o_PowerDist;
	delete o_Compressor;
	delete o_Drive;
	delete o_Lift;
}


void Robot::RobotInit(void){
	// Start the air compressor
	o_Compressor->Start();

	// Add smart dashboard data
	SmartDashboard::PutNumber("VOLTAGE", 0);
	SmartDashboard::PutNumber("TEMPERATURE", 0);
	SmartDashboard::PutNumber("LEFT DRIVE SPEED", 0);
	SmartDashboard::PutNumber("RIGHT DRIVE SPEED", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_LEFT_TALON_1_PDP) + ")", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_LEFT_TALON_2_PDP) + ")", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_RIGHT_TALON_1_PDP) + ")", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_RIGHT_TALON_2_PDP) + ")", 0);
	SmartDashboard::PutBoolean(" ARM", false);
	SmartDashboard::PutBoolean(" CLAW", false);
}


void Robot::Autonomous(void){
	// Play macro file
	o_Macro->Play(0, o_Drive, o_Lift);
}


void Robot::OperatorControl(void){
	// Variables for caching joystick values and calculating motor speeds
	float y, z, left_speed, right_speed;
	bool b_arm, b_claw;

	// Start recording macro (if arg 'true' is sent)
	o_Macro->StartRecording(false);

	// Set solenoids to reverse as default state
	o_Lift->SetArm(2);
	o_Lift->SetClaw(2);

	while(IsOperatorControl() && IsEnabled()){ // Loop while in teleop mode
		// Cache joystick 1 variables
		y = -o_Joysticks[0]->GetRawAxis(AXIS_Y); // Set to negative to counteract the joystick's problem of having a reversed y axis
		z = o_Joysticks[0]->GetRawAxis(AXIS_Z);
		
		// Cache joystick 2 variables
		b_arm = o_Joysticks[1]->GetRawButton(BUTTON_ARM);
		b_claw = o_Joysticks[1]->GetRawButton(BUTTON_CLAW);

		// Calculate motor speeds
		left_speed = (pow(fabs(y), CURVE - 1) * y) + (pow(fabs(z), CURVE - 1) * z);
		right_speed = (pow(fabs(y), CURVE - 1)  * y) - (pow(fabs(z), CURVE - 1) * z);
		if(left_speed > 1) left_speed = 1;
		if(left_speed <-1) left_speed = -1;
		if(right_speed > 1) right_speed = 1;
		if(right_speed <-1) right_speed = -1;
		
		// Set drive motors
		o_Drive->Set(left_speed, right_speed);
		
		// Set solenoids
		o_Lift->ToggleArm(b_arm);
		o_Lift->ToggleClaw(b_claw);
		
		// Check if solenoids need to be turned off
		o_Lift->CheckArm();
		o_Lift->CheckClaw();

		// Output data to smart dashboard
		SmartDashboard::PutNumber("VOLTAGE", o_PowerDist->GetVoltage());
		SmartDashboard::PutNumber("TEMPERATURE", o_PowerDist->GetTemperature());
		SmartDashboard::PutNumber("LEFT DRIVE SPEED", left_speed);
		SmartDashboard::PutNumber("RIGHT DRIVE SPEED", right_speed);
		SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_LEFT_TALON_1_PDP) + ")", o_PowerDist->GetCurrent(PORT_LEFT_TALON_1_PDP));
		SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_LEFT_TALON_2_PDP) + ")", o_PowerDist->GetCurrent(PORT_LEFT_TALON_2_PDP));
		SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_RIGHT_TALON_1_PDP) + ")", o_PowerDist->GetCurrent(PORT_RIGHT_TALON_1_PDP));
		SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_RIGHT_TALON_2_PDP) + ")", o_PowerDist->GetCurrent(PORT_RIGHT_TALON_2_PDP));

		// Save macro step
		o_Macro->SaveStep(left_speed, right_speed, b_arm, b_claw);

		// Wait until looping again
		Wait(CYCLE_TIME_DELAY);
	}

	// Stop recording macro
	o_Macro->StopRecording();

	// Reset smart dashboard data
	SmartDashboard::PutNumber("VOLTAGE", 0);
	SmartDashboard::PutNumber("TEMPERATURE", 0);
	SmartDashboard::PutNumber("LEFT DRIVE SPEED", 0);
	SmartDashboard::PutNumber("RIGHT DRIVE SPEED", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_LEFT_TALON_1_PDP) + ")", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_LEFT_TALON_2_PDP) + ")", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_RIGHT_TALON_1_PDP) + ")", 0);
	SmartDashboard::PutNumber("CURRENT (CHANNEL " + std::to_string(PORT_RIGHT_TALON_2_PDP) + ")", 0);
}


START_ROBOT_CLASS(Robot);
