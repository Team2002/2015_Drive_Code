#ifndef MACRO_H__INCLUDED
#define MACRO_H__INCLUDED


#include "WPILib.h"
#include "Drive.h"
#include "Lift.h"


class Macro{
public:
	Macro();
	~Macro();
	
	void StartRecording(void);
	void SaveStep(float, float, bool, bool);
	void StopRecording(void);
	
	void Play(const int, Drive*, Lift*, Compressor*);
	
private:
	Timer* StepTimer;
	FILE* File;
	bool is_recording;
};


#endif /* MACRO_H__INCLUDED */
