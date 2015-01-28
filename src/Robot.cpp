#include "WPILib.h"

class Robot: public IterativeRobot{
public:
	Joystick Joystick1;
	Talon Talon1;
	Talon Talon2;
	DoubleSolenoid DoubleSolenoid1;

	Robot():
		Joystick1(0),
		Talon1(4),
		Talon2(6),
		DoubleSolenoid1(0,1)
		{}

	void RobotInit(){}

	void AutonomousInit(){}

	void AutonomousPeriodic(){}

	void TeleopInit(){}

	void TeleopPeriodic(){
		// Cache Joystick Values
		double Y = Joystick1.GetY(),
		Z = Joystick1.GetZ(),
		Slider = Joystick1.GetThrottle();
		bool JoyBtn9 = Joystick1.GetRawButton(9),
		JoyBtn10 = Joystick1.GetRawButton(10);

		// Drive
		Talon1.Set(-((Slider+1)/2) * (Y - Z));
		Talon2.Set(((Slider+1)/2) * (Y + Z));

		// Double Solenoid Control
		if (JoyBtn9) DoubleSolenoid1.Set(DoubleSolenoid::kForward);
		else if (JoyBtn10) DoubleSolenoid1.Set(DoubleSolenoid::kReverse);
		else DoubleSolenoid1.Set(DoubleSolenoid::kOff);

		// Smart Dashboard
		SmartDashboard::PutNumber("Y", Y);
		SmartDashboard::PutNumber("Z", Z);
		SmartDashboard::PutNumber("Slider", Slider);
		SmartDashboard::PutNumber("Talon1 Speed", -((Slider+1)/2) * (Y - Z));
		SmartDashboard::PutNumber("Talon1 Speed", ((Slider+1)/2) * (Y + Z));
	}
};

START_ROBOT_CLASS(Robot);
