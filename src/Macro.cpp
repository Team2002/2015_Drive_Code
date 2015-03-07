#include "Macro.h"
#include "Constants.h"
#include "WPILib.h"
#include "Drive.h"
#include "Lift.h"
#include <iostream>
#include <string>
#include <cstdio>


Macro::Macro(void){
	StepTimer = new Timer();
	File = new FILE;
	
	is_recording = false;
}


Macro::~Macro(void){
	delete StepTimer;
	delete File;
}


void Macro::StartRecording(bool start){
	if(is_recording || !start) return;
		is_recording = true;

	int log_file = 0;

	while(true){
		File = fopen(("/home/lvuser/" + std::to_string(log_file) + ".csv").c_str(), "r");

		if(File == NULL)
			break;
		else
			log_file++;
	}

	File = fopen(("/home/lvuser/" + std::to_string(log_file) + ".csv").c_str(), "w");

	StepTimer->Reset();
	StepTimer->Start();

	return;
}


void Macro::SaveStep(float left_speed, float right_speed, bool b_arm, bool b_claw){
	if(!is_recording) return;

	StepTimer->Stop();

	fprintf(File, "%f,%f,%f,%d,%d\n", StepTimer->Get(), &left_speed, &right_speed, &b_arm, &b_claw);

	StepTimer->Reset();
	StepTimer->Start();
}


void Macro::StopRecording(void){
	if(!is_recording) return;
	is_recording = false;

	StepTimer->Stop();

	fclose(File);
}


void Macro::Play(const int file_number, Drive* o_Drive, Lift* o_Lift){
	if(is_recording) return;

	File = fopen(("/home/lvuser/" + std::to_string(file_number) + ".csv").c_str(), "r");
	if(File == NULL) return;

	float time, left_speed, right_speed;
	bool b_arm, b_claw;

	o_Lift->SetArm(2);
	o_Lift->SetClaw(2);

	while(fscanf(File, "%f,%f,%f,%d,%d\n", &time, &left_speed, &right_speed, &b_arm, &b_claw) < 5){
		Wait(time);

		o_Drive->Set(left_speed, right_speed);

		o_Lift->ToggleArm(b_arm);
		o_Lift->ToggleClaw(b_claw);

		o_Lift->CheckArm();
		o_Lift->CheckClaw();
	}

	fclose(File);

	return;
}