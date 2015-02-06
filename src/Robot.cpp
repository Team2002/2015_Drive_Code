#include "WPILib.h"
#include "RobotMap.h"

class Robot: public IterativeRobot{
public:
	Joystick Joystick_1;
	Talon Left_Talon_1, Left_Talon_2, Left_Talon_3, Right_Talon_1, Right_Talon_2, Right_Talon_3;

	Robot():
		Joystick_1(PORT_JOYSTICK),
		Left_Talon_1(PORT_LEFT_TALON_1),
		Left_Talon_2(PORT_LEFT_TALON_2),
		Left_Talon_3(PORT_LEFT_TALON_3),
		Right_Talon_1(PORT_RIGHT_TALON_1),
		Right_Talon_2(PORT_RIGHT_TALON_2),
		Right_Talon_3(PORT_RIGHT_TALON_3)
		{}

	void RobotInit(){}

	void AutonomousInit(){}

	void AutonomousPeriodic(){}

	void TeleopInit(){}

	void TeleopPeriodic(){
		// Cache joystick values
		float y = Joystick_1.GetY(),
		z = Joystick_1.GetZ();

		// Speed multiplier (0-1) (To-do: use the joystick's slider to set this)
		float multiplier = 1.0;

		// Calculate motor speeds
		float left = -multiplier * (y - z),
		right = multiplier * (y - z);

		// Drive
		Left_Talon_1.Set(left);
		Left_Talon_2.Set(left);
		Left_Talon_3.Set(left);
		Right_Talon_1.Set(right);
		Right_Talon_2.Set(right);
		Right_Talon_3.Set(right);
	}
};

START_ROBOT_CLASS(Robot);
