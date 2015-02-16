#include "WPILib.h"
#include "Robot.h"
#include "Constants.h"
#include "Macro.h"


Robot::Robot(){
	o_Macro = new Macro();
	o_Joysticks[0] = new Joystick(PORT_JOYSTICK_1);
	o_Joysticks[1] = new Joystick(PORT_JOYSTICK_2);
	o_Compressor = new Compressor();
	o_Drive = new Drive();
	o_Intake = new Intake();
	o_Lift = new Lift();
}


Robot::~Robot(){
	delete o_Macro;
	
	for(int i = 0;i < NUMBER_OF_JOYSTICKS;i++)
		delete o_Joysticks[i];

	delete o_Compressor;
	delete o_Drive;
	delete o_Intake;
	delete o_Lift;
}


void Robot::RobotInit(void){
	o_Compressor->Start();
}


void Robot::Autonomous(void){
	o_Macro->Play(0, o_Drive, o_Lift, o_Intake, o_Compressor);
}


void Robot::OperatorControl(void){
	float y1, y2, left_speed, right_speed, left_intake_state, right_intake_state;
	bool b_arm, b_claw, b_intake_clamp, b_intake_left_in, b_intake_left_out, b_intake_right_in, b_intake_right_out;
	
	o_Macro->StartRecording(false);

	while(IsOperatorControl() && IsEnabled()){
		y1 = o_Joysticks[0]->GetRawAxis(AXIS_Y1);
		y2 = o_Joysticks[0]->GetRawAxis(AXIS_Y2);
		b_intake_clamp = o_Joysticks[0]->GetRawButton(BUTTON_INTAKE_CLAMP);
		b_intake_left_in = o_Joysticks[0]->GetRawButton(BUTTON_INTAKE_LEFT_IN);
		b_intake_left_out = o_Joysticks[0]->GetRawButton(BUTTON_INTAKE_LEFT_OUT);
		b_intake_right_in = o_Joysticks[0]->GetRawButton(BUTTON_INTAKE_RIGHT_IN);
		b_intake_right_out = o_Joysticks[0]->GetRawButton(BUTTON_INTAKE_RIGHT_OUT);
		
		b_arm = o_Joysticks[1]->GetRawButton(BUTTON_ARM);
		b_claw = o_Joysticks[1]->GetRawButton(BUTTON_CLAW);
		
		left_speed = -y1;
		right_speed = -y2;
		
		if(b_intake_left_in)
			left_intake_state = 1;
		else if(b_intake_left_out)
			left_intake_state = 2;
		else
			left_intake_state = 0;
		
		if(b_intake_right_in)
			right_intake_state = 1;
		else if(b_intake_right_out)
			right_intake_state = 2;
		else
			right_intake_state = 0;
		
		o_Drive->Set(left_speed, right_speed);
		o_Lift->ToggleUpDown(b_arm);
		o_Lift->ToggleInOut(b_claw);
		o_Intake->Toggle(b_intake_clamp);
		o_Intake->Set(left_intake_state, right_intake_state);

		o_Macro->SaveStep(left_speed, right_speed, b_arm, b_claw, b_intake_clamp, left_intake_state, right_intake_state);

		Wait(CYCLE_TIME_DELAY);
	}

	o_Macro->StopRecording();
}


START_ROBOT_CLASS(Robot);
