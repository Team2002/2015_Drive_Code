/*
	This class is designed to record and play robot macros. It saves data in "steps". Each "step" is like a frame in a video, but because the time between each step can vary due to any number of things, the time between each step is saved, to get the most accurate playback. The SaveStep method receives arguments of the robot's current state, and uses a timer to determine how long has passed since the last step was saved. The Play method then reads in those values and plays it back. 

	For now, the only parameters that are passed to SaveStep are the left and right motor values, but once those work, other components can be added.

	Basically, you just add the methods to your current tele-op program, and drive it like you normally would, then use the saved macros where ever they are needed.

	Not only could this be used for autonomous, but it could be used to create subroutines for use in tele-op.
	
	The main issue with this is the fact that battery voltage fluctuates over time, so if your battery has a different voltage than when the macro was recorded, then your results may vary.
	
	To Do / Ideas
		-White space deletion: remove any buffer time before and after the macro in which nothing is happening
		-Create an Info method to get information about a macro (such as how long it takes to complete)
		-Make a version of this that uses motor encoder data, rather than motor speed, to solve the voltage issue
 */
 
 /* *** USAGE EXAMPLE *** */
 
 
	// Recording
	
	while(IsOperatorControl() && IsEnabled()){
		
		// Tele-op code
		
		if(/* Button Pressed */)
			SmartDashboard::PutString("Macro Being Recorded: ", Macro.StartRecording()); // Convert int to string
		else if(/* Another Button Pressed */){
			SmartDashboard::PutNumber("Macro Being Recorded: ", "None");
			Macro.StopRecording();
		}
			
		Macro.SaveStep(right_speed, left_speed); // Note that if a macro is not being recorded, calling this function will just return back with no effect
	}

	
	// Play back (macro number 5)
	
	if(Macro.Play(5)){
		// Macro successfully completed
	}else{
		// Macro file cannot be found
	}
	
	
/* *** END OF USAGE EXAMPLE *** */
 
 

#include "WPILib.h"

class MacroRecorder{
public:
	MacroRecorder();

	int StartRecording(void); // Returns the name of the macro that is being recorded. Names of macros are integers to make them easier to deal with inside the program
	void SaveStep(const float right_speed, const float left_speed);
	void StopRecording(void);
	
	bool Play(const int log_file_to_play); // Returns true if the macro exists (AFTER the macro has completed), or false if it does not
	
private:
	Timer* StepTimer;
	
	
	MacroRecorder(){
		StepTimer = new Timer();
	}
	
	
	bool is_recording = false;
	int log_file;

	
	int StartRecording(void){
		if(is_recording) return;
		is_recording = true;
		
		// Check macros already created to determine name for new macro
		// Set log_file to the name determined in the above step
		// Make log file with the name stored in log_file
		
		StepTimer->Reset();
		StepTimer->Start();
		
		return log_file;
	}

	
	void SaveStep(const float right_speed, const float left_speed){
		if(!is_recording) return;
		
		StepTimer->Stop();
		StepTimer->Reset();
		
		// Save timer value ( StepTimer->Get() ) and passed parameters into log file
		// Save passed robot parameters to the log file
		
		StepTimer->Reset();
		StepTimer->Start();
	}
	
	
	void StopRecording(void){
		if(!is_recording) return;
		is_recording = false;
		
		StepTimer->Stop();
		StepTimer->Reset();
		
		// Do anything needed to save and close the log file
	}
	
	
	bool Play(const int log_file_to_play){
		if(/* log file does not exist */) return false;
		
		for(/* Iterate through steps */){
			// Wait for amount of time
			// Set robot component values
		}
		
		// Stop motors and turn off solenoids, just in case the macro ends with anything still going
		
		return true;
	}
} Macro;
