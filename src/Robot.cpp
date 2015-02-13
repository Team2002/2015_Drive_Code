#include "WPILib.h"
#include "RobotMap.h"
#include "Macro.h"

class Robot: public SampleRobot{
public:
	Joystick* Joysticks[NUMBER_OF_JOYSTICKS];       // 0 = Joystick
	Talon* Talons[NUMBER_OF_TALONS];                // 0-2 = Right Talons, 3-5 = Left Talons
	DoubleSolenoid* Solenoids[NUMBER_OF_SOLENOIDS]; // 0 = Lift, 1 = Claw, 2 = Door
	Timer* Timers[NUMBER_OF_SOLENOIDS];             // 0 = Lift Timer, 1 = Claw Timer, 2 = Door Timer
	MacroRecorder Macro;                            // Allows the recording and playback of macros [in progress..]

	Robot();

	const float CYCLE_TIME_DELAY = 0.005, // Time to wait in seconds between each cycle. This gives the motors time to update
	SOLENOID_STATE_TIME_DELAY = 0.25;     // Time to wait in seconds between toggling a solenoid's state and turning the solenoid off

	void Autonomous();
	void OperatorControl();
};

Robot::Robot(){
	Joysticks[0] = new Joystick(PORT_JOYSTICK);
	Talons[0] = new Talon(PORT_RIGHT_TALON_1);
	Talons[1] = new Talon(PORT_RIGHT_TALON_2);
	Talons[2] = new Talon(PORT_RIGHT_TALON_3);
	Talons[3] = new Talon(PORT_LEFT_TALON_1);
	Talons[4] = new Talon(PORT_LEFT_TALON_2);
	Talons[5] = new Talon(PORT_LEFT_TALON_3);
	Solenoids[0] = new DoubleSolenoid(PORT_1_LIFT_SOLENOID, PORT_2_LIFT_SOLENOID);
	Solenoids[1] = new DoubleSolenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
	Solenoids[2] = new DoubleSolenoid(PORT_1_DOOR_SOLENOID, PORT_2_DOOR_SOLENOID);
	Timers[0] = new Timer();
	Timers[1] = new Timer();
	Timers[2] = new Timer();
}

void Robot::Autonomous(){
	// This will be used to test the macro methods. It should create a .csv file with the data saved to it.
	SmartDashboard::PutString("Done recording: ", "NO");
	Macro.StartRecording();
	Wait(0.5);
	Macro.SaveStep(0.25, 0.75, 0, 0, 1);
	Wait(2);
	Macro.SaveStep(0.5, 0.75, 0, 2, 0);
	Wait(2);
	Macro.SaveStep(0.25, 0.75, 1, 1, 1);
	Wait(1);
	Macro.SaveStep(0.6, 0.75, 0, 1, 2);
	Wait(1);
	Macro.SaveStep(0.25, 0.75, 2, 2, 0);
	Wait(0.75);
	Macro.StopRecording();
	SmartDashboard::PutString("Done recording: ", "YES");
}

void Robot::OperatorControl(){
	// Variables
	float y, z, slider;                         // Joystick floats
	bool solenoid_buttons[NUMBER_OF_SOLENOIDS]; // Joystick booleans
	float right_speed, left_speed;              // Motor speeds
	bool solenoid_forward[NUMBER_OF_SOLENOIDS], solenoid_button_already_pressed[NUMBER_OF_SOLENOIDS]; // Used to toggle solenoid states

	// Set all solenoids in reverse
	for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++){
		Solenoids[i]->Set(DoubleSolenoid::kReverse);
		solenoid_forward[i] = false;
		solenoid_button_already_pressed[i] = false; // These also need to be set before the tele-op loop begins, so I'll juse do that here
	}

	// Set the solenoids back off
	Wait(SOLENOID_STATE_TIME_DELAY);
	for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++)
		Solenoids[i]->Set(DoubleSolenoid::kOff);
	
	while(IsOperatorControl() && IsEnabled()){
		// Cache joystick values
		y = Joysticks[0]->GetY();
		z = Joysticks[0]->GetZ();
		slider = Joysticks[0]->GetThrottle();
		solenoid_buttons[0] = Joysticks[0]->GetRawButton(JOYSTICK_BUTTON_LIFT_SOLENOID);
		solenoid_buttons[1] = Joysticks[0]->GetRawButton(JOYSTICK_BUTTON_CLAW_SOLENOID);
		solenoid_buttons[2] = Joysticks[0]->GetRawButton(JOYSTICK_BUTTON_DOOR_SOLENOID);

		// Calculate motor speeds.
		right_speed = (1 - ((slider + 1) / 2)) * (y + z); // This math takes the slider's input and converts it from -1 - 1 to 1 - 0, then uses that as a speed multiplier
		left_speed = -(1 - ((slider + 1) / 2)) * (y - z);

		// Drive
		for(int i = 0;i < NUMBER_OF_TALONS;i++){
			if(i < NUMBER_OF_TALONS / 2)             // Talons 0-2 are on the right side, and 3-5 on the left
				Talons[i]->Set(right_speed);
			else
				Talons[i]->Set(left_speed);
		}

		//Solenoid control
		for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++){
			if(solenoid_buttons[i] && !solenoid_button_already_pressed[i] && Timers[i]->Get() == 0){ // This section uses logic to toggle between the solenoid being forward or reverse
				solenoid_button_already_pressed[i] = true;                  // Since all of the solenoids and solenoid variables are arrays, they can be looped
				if(solenoid_forward[i]){
					Solenoids[i]->Set(DoubleSolenoid::kReverse);
					solenoid_forward[i] = false;
				}else{
					Solenoids[i]->Set(DoubleSolenoid::kForward);
					solenoid_forward[i] = true;
				}
				Timers[i]->Reset();
				Timers[i]->Start();
			}else if(!solenoid_buttons[i] && solenoid_button_already_pressed[i]){
				solenoid_button_already_pressed[i] = false;
			}
			if(Timers[i]->Get() > SOLENOID_STATE_TIME_DELAY){ // This section waits for a short amount of time before turning the solenoid off again
				Solenoids[i]->Set(DoubleSolenoid::kOff);
				Timers[i]->Stop();
				Timers[i]->Reset();
			}
		}

		//Wait before next cycle
		Wait(CYCLE_TIME_DELAY);
	}
}

START_ROBOT_CLASS(Robot);
