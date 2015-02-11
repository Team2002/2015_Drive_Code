#include "WPILib.h"
#include "RobotMap.h"

class Robot: public SampleRobot{
public:
	Joystick* Joysticks[1];       // 0 = Joystick
	Talon* Talons[6];             // 0-2 = Right Talons, 3-5 = Left Talons
	DoubleSolenoid* Solenoids[2]; // 0 = Lift, 1 = Claw
	Timer* Timers[2];             // 0 = Lift Timer, 1 = Claw Timer

	Robot();

	const float CYCLE_TIME_DELAY = 0.005;         // Time to wait in seconds between each cycle. This gives the motors time to update
	const float SOLENOID_STATE_TIME_DELAY = 0.25; // Time to wait in seconds between toggling a solenoid's state and turning the solenoid off

	void Autonomous();
	void OperatorControl();
};

Robot::Robot(){
	Joysticks[0] = new Joystick(PORT_JOYSTICK);      // All of these constants are defined in RobotMap.h in the USB, PWM, and DIO sections
	Talons[0] = new Talon(PORT_RIGHT_TALON_1);
	Talons[1] = new Talon(PORT_RIGHT_TALON_2);
	Talons[2] = new Talon(PORT_RIGHT_TALON_3);
	Talons[3] = new Talon(PORT_LEFT_TALON_1);
	Talons[4] = new Talon(PORT_LEFT_TALON_2);
	Talons[5] = new Talon(PORT_LEFT_TALON_3);
	Solenoids[0] = new DoubleSolenoid(PORT_1_LIFT_SOLENOID, PORT_2_LIFT_SOLENOID);
	Solenoids[1] = new DoubleSolenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
	Timers[0] = new Timer();
	Timers[1] = new Timer();
}

void Robot::Autonomous(){
	// No autonomous code yet
}

void Robot::OperatorControl(){
	// Variables
	float y, z, slider;                                           // Joystick floats
	bool solenoid_buttons[2];                                     // Joystick booleans
	float right_speed, left_speed;                                // Motor speeds
	bool solenoid_forward[2], solenoid_button_already_pressed[2]; // Used to toggle solenoid states

	// Set the already_pressed variables to false
	for(int i = 0;i < 2;i++)
		solenoid_button_already_pressed[i] = false;

	// Set the default state of all solenoids and the variables that track their states. If you change one of the solenoid states, be sure to also change its respective variable
	Solenoids[0]->Set(DoubleSolenoid::kReverse); // Solenoids can be either forward, reverse, or off (kForward, kReverse, kOff)
	solenoid_forward[0] = false;
	Solenoids[1]->Set(DoubleSolenoid::kReverse);
	solenoid_forward[1] = false;

	while(IsOperatorControl() && IsEnabled()){
		// Cache joystick values
		y = Joysticks[0]->GetY();
		z = Joysticks[0]->GetZ();
		slider = Joysticks[0]->GetThrottle();
		solenoid_buttons[0] = Joysticks[0]->GetRawButton(JOYSTICK_BUTTON_LIFT_SOLENOID); // These two constants are defined in RobotMap.h in the "Joystick Mapping" section
		solenoid_buttons[1] = Joysticks[0]->GetRawButton(JOYSTICK_BUTTON_CLAW_SOLENOID);

		// Calculate motor speeds.
		right_speed = (1 - ((slider + 1) / 2)) * (y + z); // This math takes the slider's input and converts it from -1 - 1 to 1 - 0, then uses that as a speed multiplier
		left_speed = -(1 - ((slider + 1) / 2)) * (y - z);

		// Drive
		for(int i = 0;i < 6;i++){
			if(i < 3)               // Talons 0-2 are on the right side, and 3-5 on the left
				Talons[i]->Set(right_speed);
			else
				Talons[i]->Set(left_speed);
		}

		//Solenoid control
		for(int i = 0;i < 2;i++){
			if(solenoid_buttons[i] && !solenoid_button_already_pressed[i]){ // This section uses logic to toggle between the solenoid being forward or reverse
				solenoid_button_already_pressed[i] = true;                  // Since all of the solenoids and solenoid variables are arrays, they can be looped
				if(solenoid_forward[i]){
					solenoid_forward[i] = false;
					Solenoids[i]->Set(DoubleSolenoid::kReverse);
				}else{
					solenoid_forward[i] = true;
					Solenoids[i]->Set(DoubleSolenoid::kForward);
				}
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

		SmartDashboard::PutNumber("Number", 666);

		//Wait before next cycle
		Wait(CYCLE_TIME_DELAY);
	}
}

START_ROBOT_CLASS(Robot);
