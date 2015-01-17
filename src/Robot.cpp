#include "WPILib.h"

class Robot: public IterativeRobot{
public:
	Talon motor;
	DigitalInput button;
	Encoder encoder;

	Robot():
		motor(0),
		button(0),
		encoder(1,2)
		{
			encoder.SetSamplesToAverage(5);
			encoder.SetDistancePerPulse(1);
			encoder.SetMinRate(1);
		}
	
	void RobotInit(){

	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){

	}

	void TeleopPeriodic(){
		if(button.Get() == true){
			motor.Set(0.2);
		}else{
			motor.Set(0);
		}

		SmartDashboard::PutNumber("Encoder Rate", encoder.GetRate());
		SmartDashboard::PutNumber("Encoder Distance", encoder.GetDistance());
		SmartDashboard::PutBoolean("Encoder Stopped", encoder.GetStopped());
	}
};

START_ROBOT_CLASS(Robot);
