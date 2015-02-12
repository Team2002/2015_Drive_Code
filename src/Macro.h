#include "WPILib.h"
#include <iostream>
#include <string>
#include <cstdio>


class MacroRecorder{
public:
	Timer* StepTimer;
	FILE* file;

	MacroRecorder();

	bool is_recording;

	int StartRecording(void);
	void SaveStep(float right_speed, float left_speed);
	void StopRecording(void);

	bool Play(int file_number);
};


MacroRecorder::MacroRecorder(){
	StepTimer = new Timer();
	file = new FILE();
	is_recording = false;
}


int MacroRecorder::StartRecording(void){
	if(is_recording) return -1;
	is_recording = true;

	int log_file = 0;

	while(true){
		file = fopen(("/home/lvuser/" + std::to_string(log_file) + ".txt").c_str(), "r");

		if(file == NULL)
			break;
		else
			log_file++;
	}

	file = fopen(("/home/lvuser/" + std::to_string(log_file) + ".txt").c_str(), "w");

	StepTimer->Reset();
	StepTimer->Start();

	return log_file;
}


void MacroRecorder::SaveStep(float right_speed, float left_speed){
	if(!is_recording) return;
}


void MacroRecorder::StopRecording(void){
	if(!is_recording) return;
	is_recording = false;

	StepTimer->Stop();
	StepTimer->Reset();

	fclose(file);
}


bool MacroRecorder::Play(int file_number){
	if(is_recording) return false;

	return true;
}
