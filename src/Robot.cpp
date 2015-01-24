#include "WPILib.h"

class Robot: public IterativeRobot{
public:
	Joystick Joystick1;
	Talon Talon1;
	Talon Talon2;
	Solenoid SingleSolenoid1;
	DoubleSolenoid DoubleSolenoid1;

	Robot():
		Joystick1(0),
		Talon1(4),
		Talon2(6),
		SingleSolenoid1(2),
		DoubleSolenoid1(0,1)
		{}

	void RobotInit(){}

	void AutonomousInit(){}

	void AutonomousPeriodic(){}

	void TeleopInit(){}

	void TeleopPeriodic(){
		// Cache Joystick Values
		int Y = Joystick1.GetY(),
		Z = Joystick1.GetZ();
		float Slider = (Joystick1.GetThrottle()/2)+1;

		// Motor Control
		Talon1.Set(-Slider * (Y - Z));
		Talon2.Set(Slider * (Y + Z));

		// Single Solenoid
		SingleSolenoid1.Set(Joystick1.GetRawButton(7));

		// Double Solenoid
		if(Joystick1.GetRawButton(9)) DoubleSolenoid1.Set(DoubleSolenoid::kForward);
		else if (Joystick1.GetRawButton(10)) DoubleSolenoid1.Set(DoubleSolenoid::kReverse);
		else DoubleSolenoid1.Set(DoubleSolenoid::kOff);
	}
};

START_ROBOT_CLASS(Robot);
