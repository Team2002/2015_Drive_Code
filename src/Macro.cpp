#include "Macro.h"
#include "Constants.h"
#include "WPILib.h"
#include "Drive.h"
#include "Lift.h"
#include <iostream>
#include <string>
#include <cstdio>


Macro::Macro(){
	StepTimer = new Timer();
	File = new FILE;
	is_recording = false;
}


Macro::~Macro(){
	delete StepTimer;
	delete File;
}


void Macro::StartRecording(){
	if(is_recording) return;
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

	fprintf(File, "%f,%f,%f,%d,%d\n", StepTimer->Get(), left_speed, right_speed, b_arm, b_claw);

	StepTimer->Reset();
	StepTimer->Start();
}


void Macro::StopRecording(void){
	if(!is_recording) return;
	is_recording = false;

	StepTimer->Stop();

	fclose(File);
}


void Macro::Play(const int file_number, Drive* o_Drive, Lift* o_Lift, Compressor* o_Compressor){
	if(is_recording) return;

	File = fopen(("/home/lvuser/" + std::to_string(file_number) + ".csv").c_str(), "r");
	if(File == NULL) return;

	o_Compressor->Start();

	float time, left_speed, right_speed;
	int b_arm, b_claw;

	o_Lift->SetArmReverse();
	o_Lift->SetClawReverse();

	Wait(SOLENOID_STATE_TIME_DELAY);

	while(true){
		if(fscanf(File, "%f,%f,%f,%d,%d\n", &time, &left_speed, &right_speed, &b_arm, &b_claw) < 5)
			break;

		Wait(time * MACRO_TIME_MULTIPLIER);

		o_Drive->Set(left_speed, right_speed);
		o_Lift->ToggleUpDown(b_arm);
		o_Lift->ToggleInOut(b_claw);
	}

	o_Drive->Set(0, 0);

	fclose(File);

	return;
}
