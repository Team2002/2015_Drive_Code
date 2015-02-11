/*
	This class is designed to record and play robot macros. It saves data in "steps". Each "step" is like a frame in a video, but because the time between each step can vary due to any number of things, the time between each step is saved, to get the most accurate playback. The SaveStep method receives arguments of the robot's current state, and uses a timer to determine how long has passed since the last step was saved. The Play method then reads in those values and plays it back. 

	For now, the only parameters that are passed to SaveStep are the left and right motor values, but once those work, other components can be added.

	Usage examples are shown below. Basically, you just add the methods to your current tele-op program, and drive it like you normally would, then use the saved macros where ever they are needed.

	Not only could this be used for autonomous, but it could be used to create subroutines for use in tele-op.
	
	The main issue with this is the fact that battery voltage fluctuates over time, so if your battery has a different voltage than when the macro was recorded, then your results may vary.
	
	To Do / Ideas
		-Use strings to name log files instead of characters
		-White space deletion: remove any buffer time before and after the macro in which nothing is happening
		-Create an Info method to get information about a macro (such as how long it takes to complete)
		-Make a version of this that uses motor encoder data, rather than motor speed, to solve the voltage issue
 */

 
 
#include "WPILib.h"

class MacroRecorder{
public:
	MacroRecorder();

	void StartRecording(const char log_file_name_passed);
	void SaveStep(const float right_speed, const float left_speed);
	void StopRecording(void);
	
	bool Play(const char log_file_name); // Returns false if the macro file cannot be found
	
private:
	Timer* StepTimer;             // This timer is used to time the length of time between steps
	bool is_recording = false; // This will track if a macro is being recorded, and prevent multiple macros from being recorded at once
	char log_file_name;          // This is set in StartRecording, and is referenced in SaveStep and StopRecording
	
	
	MacroRecorder(){
		StepTimer = new Timer();
	}

	
	void StartRecording(const char log_file_name_passed){
		if(is_recording) return;
		is_recording = true;
		
		log_file_name = log_file_name_passed;
		
		// Create log file
		
		StepTimer.Reset();
		StepTimer.Start();
	}

	
	void SaveStep(const float right_speed, const float left_speed){
		if(!is_recording) return;
		
		StepTimer.Stop();
		
		// Save timer value ( StepTimer.Get() ) and passed parameters into log file
		// Save passed robot parameters to the log file
		
		StepTimer.Reset();
		StepTimer.Start();
	}
	
	
	void StopRecording(void){
		if(!is_recording) return;
		is_recording = false;
		
		StepTimer.Stop();
		
		// Do anything needed to save and close the log file
	}
	
	
	bool Play(const char log_file_name){
		if(/* log file does not exist */) return false;
		
		for(/* Iterate through steps */){
			// Wait for amount of time
			// Set robot component values
		}
		
		// Stop motors and turn off solenoids, just in case the macro ends with anything still going
		
		return true;
	}
} Macro; // An object of this class is automatically created, so that the methods can be accessed with Macro.method() without having to create another object
 
 
 
 /* Usage Examples */
 
// Recording a macro
Macro.StartRecording('a', true);  // If another file named "autonomous" exists, it will be overwritten because of the second argument bool overwrite
while(IsOperatorControl() && IsEnabled()){ // This overwritting function is useful if you need to record a macro multiple times until you get it right
	// Tele-op code
	Macro.SaveStep(right_speed, left_speed);
}
Macro.StopRecording();


// Playing a macro back
if(Macro.Play('a')){
	// Macro successfully completed
}else{
	// Macro file cannot be found
}


