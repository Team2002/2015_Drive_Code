#ifndef MACRO_H__INCLUDED
#define MACRO_H__INCLUDED


#include "WPILib.h"
#include "Drive.h"
#include "Lift.h"
#include "Intake.h"


class Macro{
public:
	Macro();
	~Macro();
	
	void StartRecording(bool);
	void SaveStep(float, float, bool, bool, bool, int, int);
	void StopRecording(void);
	
	void Play(const int, Drive*, Lift*, Intake*, Compressor*);
	
private:
	Timer* StepTimer;
	FILE* File;
	bool is_recording;
};


#endif /* MACRO_H__INCLUDED */
