#include "WPILib.h"
#include "RobotMap.h"

class Robot: public SampleRobot{
public:
	Joystick Joysticks[1];       // 0 = Joystick
	Talon Talons[6];             // 0-2 = Right Talons, 3-5 = Left Talons
	DoubleSolenoid Solenoids[2]; // 0 = Lift, 1 = Claw
	Timer Timers[2];             // 0 = Lift Timer, 1 = Claw Timer

	Robot();

	const float CYCLE_TIME_DELAY = 0.05;          // Time to wait between each cycle in seconds. No, don't set it to 0.. the motors won't have time to update.
	const float SOLENOID_STATE_TIME_DELAY = 0.25; // Time to wait between toggling a solenoids state and turning the solenoid off (also in seconds)

	void Autonomous();
	void OperatorControl();
};

Robot::Robot(){
	Joysticks[0](PORT_JOYSTICK);      // All of these constants are defined in RobotMap.h
	Talons[0](PORT_RIGHT_TALON_1);
	Talons[1](PORT_RIGHT_TALON_2);
	Talons[2](PORT_RIGHT_TALON_3);
	Talons[3](PORT_LEFT_TALON_1);
	Talons[4](PORT_LEFT_TALON_2);
	Talons[5](PORT_LEFT_TALON_3);
	Solenoids[0](PORT_1_LIFT_SOLENOID, PORT_2_LIFT_SOLENOID);
	Solenoids[1](PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID);
}

void Robot::Autonomous(){}

void Robot::OperatorControl(){
	// Variables
	float y, z, slider;                                           // Joystick floats
	bool solenoid_buttons[2];                                     // Joystick booleans
	float multiplier, right_speed, left_speed;                    // Calculate and store motor speeds
	bool solenoid_forward[2], solenoid_button_already_pressed[2]; // Used to toggle solenoid states

	// Set the already_pressed variables to false
	for(int i = 0;i < 2;i++)
		solenoid_button_already_pressed[i] = false;

	// Set the default state of all solenoids and the variables that track their states. If you change one of the solenoid values, be sure to also change its respective variable.
	Solenoids[0].Set(DoubleSolenoid::kReverse);
	solenoid_forward[0] = false;
	Solenoids[1].Set(DoubleSolenoid::kReverse);
	solenoid_forward[1] = false;

	while(IsOperatorControl() && IsEnabled()){
		// Cache joystick values
		y = Joysticks[0].GetY();
		z = Joysticks[0].GetZ();
		slider = Joysticks[0].GetThrottle();
		solenoid_buttons[0] = Joysticks[0].GetRawButton(JOYSTICK_BUTTON_LIFT_SOLENOID); // Again, these two constants are defined in RobotMap.h
		solenoid_buttons[1] = Joysticks[0].GetRawButton(JOYSTICK_BUTTON_CLAW_SOLENOID);

		// Speed multiplier. The math takes the joystick's slider, reverses it, makes it 0-1
		multiplier = 1 - ((slider + 1) / 2);

		// Calculate motor speeds
		right_speed = multiplier * (y + z);
		left_speed = -multiplier * (y - z);

		// Drive
		for(int i = 0;i < 5;i++){
			if(i <= 3)
				Talons[i].Set(right_speed);
			else
				Talons[i].Set(left_speed);
		}

		//Solenoid control
		for(int i = 0;i < 2;i++){
			if(solenoid_buttons[i] && !solenoid_button_already_pressed[i]){ // This section uses logic to toggle between the solenoid being forward or reverse
				solenoid_button_already_pressed[i] = true;
				if(solenoid_forward[i]){
					solenoid_forward[i] = false;
					Solenoids[i].Set(DoubleSolenoid::kForward);
				}else{
					solenoid_forward[i] = true;
					Solenoids[i].Set(DoubleSolenoid::kReverse);
				}
				Timers[i].Start();
			}else if(!solenoid_buttons[i]){
				solenoid_button_already_pressed[i] = false;
			}
			if(Timers[i].Get() > SOLENOID_STATE_TIME_DELAY){ // This section waits for a short amount of time before turning the solenoid off again
				Solenoids[i].Set(DoubleSolenoid::kOff);
				Timers[i].Stop();
				Timers[i].Reset();
			}
		}

		//Wait before next cycle
		Wait(CYCLE_TIME_DELAY);
	}
}

START_ROBOT_CLASS(Robot);
