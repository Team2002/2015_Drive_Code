//Include header files
#include "Macro.h"
#include "Config.h"
#include "WPILib.h"
#include "Drive.h"
#include "Lift.h"
//Include other things
#include <iostream>
#include <string>
#include <cstdio>

//Define Macro function
Macro::Macro(void){
	//Create new objects
	StepTimer = new Timer();
	File = new FILE;
	//It's not recording right now
	is_recording = false;
}

//Delete Macro objects
Macro::~Macro(void){
	delete StepTimer;
	delete File;
}

//Declare StartRecording function
void Macro::StartRecording(bool start){
	//If it's already recording or you don't actually want to start, exit the function
	if(is_recording || !start) return;
		//You've started recording
		is_recording = true;
	//Declare log_file integer
	int log_file = 0;

	//Keep doing this forever
	while(true){
		//Open: /home/lvuser/"log_file integer".csv
		File = fopen(("/home/lvuser/" + std::to_string(log_file) + ".csv").c_str(), "r");
		
		//If it doesn't exist
		if(File == NULL)
			//Exit
			break;
		//Otherwise...
		else
			//Add 1 to log_file
			log_file++;
	}
	
	//Open: /home/lvuser/"log_file integer".csv
	File = fopen(("/home/lvuser/" + std::to_string(log_file) + ".csv").c_str(), "w");

	//Reset and restart the timer
	StepTimer->Reset();
	StepTimer->Start();

	//...art
	return;
}

//Declare SaveStep function
void Macro::SaveStep(float left_speed, float right_speed, bool b_arm, bool b_claw){
	//If it's not recording, exit the function
	if(!is_recording) return;

	//Stop the timer
	StepTimer->Stop();

	//Print the timer's time, left and right speed, arm and claw
	fprintf(File, "%f,%f,%f,%d,%d\n", StepTimer->Get(), left_speed, right_speed, b_arm, b_claw);

	//Reset and restart the timer
	StepTimer->Reset();
	StepTimer->Start();
}

//Declare StopRecording function
void Macro::StopRecording(void){
	//If it's not recording, exit the function
	if(!is_recording) return;
	//It's no longer recording
	is_recording = false;

	//Stop the timer
	StepTimer->Stop();

	//Close the file
	fclose(File);
}

//Declare Play function
void Macro::Play(const int file_number, Drive* o_Drive, Lift* o_Lift){
	//If it's recording, exit the function
	if(is_recording) return;

	//Open: /home/lvuser/"file_number".csv
	File = fopen(("/home/lvuser/" + std::to_string(file_number) + ".csv").c_str(), "r");
	//If it doesn't exist, exit the function
	if(File == NULL) return;

	//Declare time, left and right speeds, arm and claw
	float time, left_speed, right_speed;
	bool b_arm, b_claw;

	//Set the arm and claw to their default states
	o_Lift->SetArm(ARM_DEFAULT_STATE);
	o_Lift->SetClaw(CLAW_DEFAULT_STATE);

	//Keep doing this as long as the scan returns 5
	while(fscanf(File, "%f,%f,%f,%d,%d\n", &time, &left_speed, &right_speed, &b_arm, &b_claw) == 5){
		//Wait for "time" milliseconds
		Wait(time);

		//Set the speeds
		o_Drive->Set(left_speed, right_speed);

		//Toggle the arm and claw
		o_Lift->ToggleArm(b_arm);
		o_Lift->ToggleClaw(b_claw);

		//Check the arm and claw
		o_Lift->CheckArm();
		o_Lift->CheckClaw();
	}

	//Close the file
	fclose(File);

	//More art
	return;
}
