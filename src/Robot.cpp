#include "WPILib.h"
#include "Macro.h"

class Robot: public SampleRobot{
public:
	Joystick* Joysticks[NUMBER_OF_JOYSTICKS];       // 0 = Joystick
	Talon* Talons[NUMBER_OF_TALONS];                // 0-2 = Right Talons, 3-5 = Left Talons
	DoubleSolenoid* Solenoids[NUMBER_OF_SOLENOIDS]; // 0 = Lift, 1 = Claw, 2 = Door
	Timer* Timers[NUMBER_OF_SOLENOIDS];             // 0 = Lift Timer, 1 = Claw Timer, 2 = Door Timer
	MacroRecorder* Macro;                           // Object to record and play back macros

	Robot();
	~Robot();

	void Autonomous();      // Called on start of autonomous
	void OperatorControl(); // Called on start of tele-op
};


Robot::Robot(){
	Joysticks[0] = new Joystick(PORT_JOYSTICK_1);
	Joysticks[1] = new Joystick(PORT_JOYSTICK_2);
	Talons[0] = new Talon(PORT_RIGHT_TALON_1);
	Talons[1] = new Talon(PORT_RIGHT_TALON_2);
	Talons[2] = new Talon(PORT_LEFT_TALON_1);
	Talons[3] = new Talon(PORT_LEFT_TALON_2);
	Talons[4] = new Talon(PORT_RIGHT_INTAKE_TALON);
	Talons[5] = new Talon(PORT_LEFT_INTAKE_TALON);
	Solenoids[0] = new DoubleSolenoid(PORT_1_LIFT_SOLENOID, PORT_2_LIFT_SOLENOID);
	Solenoids[1] = new DoubleSolenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
	Solenoids[2] = new DoubleSolenoid(PORT_1_INTAKE_SOLENOID, PORT_2_INTAKE_SOLENOID);
	Solenoids[3] = new DoubleSolenoid(PORT_1_DOOR_SOLENOID, PORT_2_DOOR_SOLENOID);
	Timers[0] = new Timer();
	Timers[1] = new Timer();
	Timers[2] = new Timer();
	Macro = new MacroRecorder();
}


Robot::~Robot(){
	for(int i = 0;i < NUMBER_OF_JOYSTICKS;i++)
		delete Joysticks[i];

	for(int i = 0;i < NUMBER_OF_TALONS;i++)
		delete Talons[i];

	for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++)
		delete Solenoids[i];

	for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++)
		delete Timers[i];

	delete Macro;
}


void Robot::Autonomous(){
<<<<<<< HEAD
	Macro->Play(AUTONOMOUS_PROGRAM, Talons, Solenoids);
=======
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
>>>>>>> 2dcf3a18bae4496bf057c1412c15eba825730dc1
}


void Robot::OperatorControl(){
	//Start recording macro
	Macro->StartRecording();

	// Variables
	float y, z, slider;                         // Joystick floats
	int left_intake_state, right_intake_state;  //Joystick integers
	bool solenoid_buttons[NUMBER_OF_SOLENOIDS]; // Joystick booleans
	float right_speed, left_speed;              // Motor speeds
	int solenoid_state[NUMBER_OF_SOLENOIDS];    // 0 = Off, 1 = Forward, 2 = Reverse
	bool solenoid_forward[NUMBER_OF_SOLENOIDS], solenoid_button_already_pressed[NUMBER_OF_SOLENOIDS]; // Used to toggle solenoid states

	// Set all solenoids in reverse
	for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++){
		Solenoids[i]->Set(DoubleSolenoid::kReverse);
		solenoid_state[i] = 2;
		solenoid_forward[i] = false;
		solenoid_button_already_pressed[i] = false; // These also need to be set before the tele-op loop begins, so I'll just do that here
	}

	Macro->SaveStep(0, 0, 0, 0, solenoid_state[0], solenoid_state[1], solenoid_state[2], solenoid_state[3]);

	// Set the solenoids back off
	Wait(SOLENOID_STATE_TIME_DELAY);
	for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++){
		Solenoids[i]->Set(DoubleSolenoid::kOff);
		solenoid_state[i] = 0;
	}

	Macro->SaveStep(0, 0, 0, 0, solenoid_state[0], solenoid_state[1], solenoid_state[2], solenoid_state[3]);
	
	while(IsOperatorControl() && IsEnabled()){
		// Cache joystick values
		y = Joysticks[0]->GetY();
		z = Joysticks[0]->GetZ();
		slider = Joysticks[0]->GetThrottle();
		solenoid_buttons[0] = Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_LIFT_SOLENOID);
		solenoid_buttons[1] = Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_CLAW_SOLENOID);
		solenoid_buttons[1] = Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_INTAKE_SOLENOID);
		solenoid_buttons[2] = Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_DOOR_SOLENOID);

		// Calculate motor speeds.
		right_speed = (1 - ((slider + 1) / 2)) * (y + z); // This math takes the slider's input and converts it from -1 - 1 to 1 - 0, then uses that as a speed multiplier
		left_speed = -(1 - ((slider + 1) / 2)) * (y - z);

		// Drive
		for(int i = 0;i < NUMBER_OF_TALONS - 2;i++){
			if(i < (NUMBER_OF_TALONS - 2) / 2)             // Talons 0-1 are on the right side, and 2-3 on the left. Subtract 2 to account for the two claw talons
				Talons[i]->Set(right_speed);
			else
				Talons[i]->Set(left_speed);
		}

		// Left intake motor
		if(Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_LEFT_INTAKE_MOTOR_IN)){
			left_intake_state = 1;
			Talons[PORT_LEFT_INTAKE_TALON]->Set(INTAKE_SPEED);
		}else if(Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_LEFT_INTAKE_MOTOR_OUT)){
			left_intake_state = 2;
			Talons[PORT_LEFT_INTAKE_TALON]->Set(-INTAKE_SPEED);
		}else{
			left_intake_state = 0;
			Talons[PORT_LEFT_INTAKE_TALON]->Set(0);
		}

		// Right intake motor
		if(Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_RIGHT_INTAKE_MOTOR_IN)){
			right_intake_state = 1;
			Talons[PORT_RIGHT_INTAKE_TALON]->Set(INTAKE_SPEED);
		}else if(Joysticks[1]->GetRawButton(JOYSTICK_BUTTON_RIGHT_INTAKE_MOTOR_OUT)){
			right_intake_state = 2;
			Talons[PORT_RIGHT_INTAKE_TALON]->Set(-INTAKE_SPEED);
		}else{
			right_intake_state = 0;
			Talons[PORT_RIGHT_INTAKE_TALON]->Set(0);
		}

		//Solenoid control
		for(int i = 0;i < NUMBER_OF_SOLENOIDS;i++){
			if(solenoid_buttons[i] && !solenoid_button_already_pressed[i] && Timers[i]->Get() == 0){ // This section uses logic to toggle between the solenoid being forward or reverse
				solenoid_button_already_pressed[i] = true;                  // Since all of the solenoids and solenoid variables are arrays, they can be looped
				if(solenoid_forward[i]){
					Solenoids[i]->Set(DoubleSolenoid::kReverse);
					solenoid_forward[i] = false;
					solenoid_state[i] = 2;
				}else{
					Solenoids[i]->Set(DoubleSolenoid::kForward);
					solenoid_forward[i] = true;
					solenoid_state[i] = 1;
				}
				Timers[i]->Reset();
				Timers[i]->Start();
			}else if(!solenoid_buttons[i] && solenoid_button_already_pressed[i]){
				solenoid_button_already_pressed[i] = false;
			}
			if(Timers[i]->Get() > SOLENOID_STATE_TIME_DELAY){ // This section waits for a short amount of time before turning the solenoid off again
				Solenoids[i]->Set(DoubleSolenoid::kOff);
				solenoid_state[i] = 0;
				Timers[i]->Stop();
				Timers[i]->Reset();
			}
		}

		// Record macro step
		Macro->SaveStep(left_speed, right_speed, left_intake_state, right_intake_state, solenoid_state[0], solenoid_state[1], solenoid_state[2], solenoid_state[3]);

		//Wait before next cycle
		Wait(CYCLE_TIME_DELAY);
	}

	// Stop recording macro
	Macro->StopRecording();
}

START_ROBOT_CLASS(Robot);
