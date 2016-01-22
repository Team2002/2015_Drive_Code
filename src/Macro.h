#ifndef MACRO_H__INCLUDED // check if MACRO_H__INCLUDED has been defined
#define MACRO_H__INCLUDED // define MACRO_H__INCLUDED


#include "WPILib.h" // include WPILib.h library
#include "Drive.h" // include Drive.h library
#include "Lift.h" // include Lift.h library


class Macro{ // define Macro class
public: // info from class available to all programs
	Macro(void);
	~Macro(void);
	
	void StartRecording(bool);
	void SaveStep(float, float, bool, bool);
	void StopRecording(void);
	
	void Play(const int, Drive*, Lift*);
	
private: // info from class only available to this program
	Timer* StepTimer;
	FILE* File;
	
	bool is_recording;
};


#endif /* MACRO_H__INCLUDED */
