#include "WPILib.h"
#include <iostream>
#include <string>
#include <cstdio>


class MacroRecorder{
public:
	MacroRecorder();

	int StartRecording(void); 
	void SaveStep(const float right_speed, const float left_speed, const int lift_state, const int claw_state, const int door_state);
	void StopRecording(void);

	int Play(const int file_number);
	
	/* **********
	-- Return Values for Non-Void Functions --
	
		* StartRecording:
			-1 = another macro is currently being recorded (a new macro won't be recorded)
			other int = file number that is now being recorded on
		
		* Play:
			0 = macro completed successfully 
			1 = another macro is currently being recorded (called macro won't play) 
			2 = file cannot be found
	********** */
	
private:
	Timer* StepTimer;
	FILE* File;
	bool is_recording;
};


MacroRecorder::MacroRecorder(){
	StepTimer = new Timer();
	File = new FILE();
	is_recording = false;
}


int MacroRecorder::StartRecording(void){
	if(is_recording) return -1;
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

	return log_file;
}


void MacroRecorder::SaveStep(const float right_speed, const float left_speed, const int lift_state, const int claw_state, const int door_state){
	if(!is_recording) return;
	
	StepTimer->Stop();
	
	fprintf(File, "%f,%f,%f,%d,%d,%d\n", StepTimer->Get(), right_speed, left_speed, lift_state, claw_state, door_state);
	
	StepTimer->Reset();
	StepTimer->Start();
}


void MacroRecorder::StopRecording(void){
	if(!is_recording) return;
	is_recording = false;

	StepTimer->Stop();

	fclose(File);
}


int MacroRecorder::Play(const int file_number){
	if(is_recording) return 1;

	File = fopen(("/home/lvuser/" + std::to_string(file_number) + ".csv").c_str(), "r");
	if(File == NULL) return 2;
	
	// Playback
	
	fclose(File);

	return 0;
}
