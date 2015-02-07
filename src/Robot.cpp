#include "WPILib.h"
#include "RobotMap.h"

class Robot: public IterativeRobot{
public:
	Joystick Joystick_1;
	Talon Right_Talon_1, Right_Talon_2, Right_Talon_3, Left_Talon_1, Left_Talon_2, Left_Talon_3;
	DoubleSolenoid Lift_Solenoid, Claw_Solenoid;
	Timer Lift_Solenoid_Timer, Claw_Solenoid_Timer;

	// Solenoid toggle variables
	bool lift_solenoid_forward = false,
	claw_solenoid_forward = false,
	lift_solenoid_button_already_pressed = false,
	claw_solenoid_button_already_pressed = false;

	Robot():
		Joystick_1(PORT_JOYSTICK),
		Right_Talon_1(PORT_RIGHT_TALON_1),
		Right_Talon_2(PORT_RIGHT_TALON_2),
		Right_Talon_3(PORT_RIGHT_TALON_3),
		Left_Talon_1(PORT_LEFT_TALON_1),
		Left_Talon_2(PORT_LEFT_TALON_2),
		Left_Talon_3(PORT_LEFT_TALON_3),
		Lift_Solenoid(PORT_1_LIFT_SOLENOID, PORT_2_LIFT_SOLENOID),
		Claw_Solenoid(PORT_1_CLAW_SOLENOID, PORT_2_CLAW_SOLENOID)
		{}

	void RobotInit(){}

	void AutonomousInit(){}

	void AutonomousPeriodic(){}

	void TeleopInit(){
		// Set the state of the solenoids
		Lift_Solenoid.Set(DoubleSolenoid::kReverse);
		Claw_Solenoid.Set(DoubleSolenoid::kReverse);
	}

	void TeleopPeriodic(){
		// Constants
		const float SOLENOID_STATE_TIME_DELAY = 0.25;

		// Cache joystick values
		float y = Joystick_1.GetY(),
		z = Joystick_1.GetZ(),
		slider = Joystick_1.GetThrottle();
		bool lift_solenoid_button = Joystick_1.GetRawButton(2),
		claw_solenoid_button = Joystick_1.GetRawButton(4);

		// Speed multiplier
		float multiplier = 1 - ((slider + 1) / 2);

		// Calculate motor speeds
		float right_speed = multiplier * (y + z),
		left_speed = -multiplier * (y - z);

		// Drive
		Right_Talon_1.Set(right_speed);
		Right_Talon_2.Set(right_speed);
		Right_Talon_3.Set(right_speed);
		Left_Talon_1.Set(left_speed);
		Left_Talon_2.Set(left_speed);
		Left_Talon_3.Set(left_speed);

		// Lift solenoid toggle
		if(lift_solenoid_button && !lift_solenoid_button_already_pressed){
			lift_solenoid_button_already_pressed = true;
			if(lift_solenoid_forward){
				lift_solenoid_forward = false;
				Lift_Solenoid.Set(DoubleSolenoid::kForward);
			}else{
				lift_solenoid_forward = true;
				Lift_Solenoid.Set(DoubleSolenoid::kReverse);
			}
			Lift_Solenoid_Timer.Reset();
			Lift_Solenoid_Timer.Start();
		}else if(!lift_solenoid_button){
			lift_solenoid_button_already_pressed = false;
		}
		if(Lift_Solenoid_Timer.Get() > SOLENOID_STATE_TIME_DELAY){
			Lift_Solenoid.Set(DoubleSolenoid::kOff);
			Lift_Solenoid_Timer.Stop();
		}

		// Claw solenoid toggle
		if(claw_solenoid_button && !claw_solenoid_button_already_pressed){
			claw_solenoid_button_already_pressed = true;
			if(claw_solenoid_forward){
				claw_solenoid_forward = false;
				Claw_Solenoid.Set(DoubleSolenoid::kForward);
			}else{
				claw_solenoid_forward = true;
				Claw_Solenoid.Set(DoubleSolenoid::kReverse);
			}
			Claw_Solenoid_Timer.Reset();
			Claw_Solenoid_Timer.Start();
		}else if(!claw_solenoid_button){
			claw_solenoid_button_already_pressed = false;
		}
		if(Claw_Solenoid_Timer.Get() > SOLENOID_STATE_TIME_DELAY){
			Claw_Solenoid.Set(DoubleSolenoid::kOff);
			Claw_Solenoid_Timer.Stop();
		}
	}
};

START_ROBOT_CLASS(Robot);
