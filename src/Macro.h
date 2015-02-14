#include "WPILib.h"
#include "RobotMap.h"
#include <iostream>
#include <string>
#include <cstdio>


class MacroRecorder{
public:
	MacroRecorder();
	~MacroRecorder();

	void StartRecording(void);
	void SaveStep(float, float, int, int, int);
	void StopRecording(void);

	void Play(const int, Talon*[6], DoubleSolenoid*[3]);
	
	/* **********
	-- Return Values for Non-Void Functions --
	
		* StartRecording:
			-1 = another macro is currently being recorded (a new macro won't be recorded)
			other int = file number that is now being recorded on
		
		* Play:
			0 = macro completed successfully 
			1 = a macro is currently being recorded (called macro won't play) 
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


MacroRecorder::~MacroRecorder(){
	delete StepTimer;
	delete File;
}


void MacroRecorder::StartRecording(void){
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


void MacroRecorder::SaveStep(float left_speed, float right_speed, int lift_state, int claw_state, int door_state){
	if(!is_recording) return;
	
	StepTimer->Stop();
	
	fprintf(File, "%f,%f,%f,%d,%d,%d\n", StepTimer->Get(), left_speed, right_speed, lift_state, claw_state, door_state);
	
	StepTimer->Reset();
	StepTimer->Start();
}


void MacroRecorder::StopRecording(void){
	if(!is_recording) return;
	is_recording = false;

	StepTimer->Stop();

	fclose(File);
}


void MacroRecorder::Play(const int file_number, Talon* Talons[NUMBER_OF_TALONS], DoubleSolenoid* Solenoids[NUMBER_OF_SOLENOIDS]){
	if(is_recording) return;

	File = fopen(("/home/lvuser/" + std::to_string(file_number) + ".csv").c_str(), "r");
	if(File == NULL) return;

	float time, left_speed, right_speed;
	int lift_state, claw_state, door_state;
	
	while(true){
		if(fscanf(File, "%f,%f,%f,%d,%d,%d\n", &time, &left_speed, &right_speed, &lift_state, &claw_state, &door_state) < 6)
			break;

		Wait(time);

		for(int i = 0;i < NUMBER_OF_TALONS;i++){
			if(i < NUMBER_OF_TALONS / 2)
				Talons[i]->Set(right_speed);
			else
				Talons[i]->Set(left_speed);
		}

		if(lift_state == 0){
			Solenoids[0]->Set(DoubleSolenoid::kOff);
		}else if(lift_state == 1){
			Solenoids[0]->Set(DoubleSolenoid::kForward);
		}else if(lift_state == 2){
			Solenoids[0]->Set(DoubleSolenoid::kReverse);
		}

		if(claw_state == 0){
			Solenoids[1]->Set(DoubleSolenoid::kOff);
		}else if(claw_state == 1){
			Solenoids[1]->Set(DoubleSolenoid::kForward);
		}else if(claw_state == 2){
			Solenoids[1]->Set(DoubleSolenoid::kReverse);
		}

		if(door_state == 0){
			Solenoids[2]->Set(DoubleSolenoid::kOff);
		}else if(door_state == 1){
			Solenoids[2]->Set(DoubleSolenoid::kForward);
		}else if(door_state == 2){
			Solenoids[2]->Set(DoubleSolenoid::kReverse);
		}
	}

	for(int i = 0;i < NUMBER_OF_TALONS;i++){
		if(i < NUMBER_OF_TALONS / 2)
			Talons[i]->Set(0);
		else
			Talons[i]->Set(0);
	}

	Solenoids[0]->Set(DoubleSolenoid::kOff);
	Solenoids[1]->Set(DoubleSolenoid::kOff);
	Solenoids[2]->Set(DoubleSolenoid::kOff);

	fclose(File);

	return;
}
