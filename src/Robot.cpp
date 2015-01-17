#include "WPILib.h"

class Robot: public IterativeRobot{
public:
	Talon motor;
	DigitalInput button;
	Encoder encoder;

	Robot():
		motor(0),
		button(0),
		encoder(1, 2, false, Encoder::k4X)
		{
			encoder.SetSamplesToAverage(5);
			encoder.SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 1.5);
			encoder.SetMinRate(1.0);
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
			motor.Set(0.5);
		}else{
			motor.Set(0);
		}

		SmartDashboard::PutBoolean("Button Pushed", button.Get());
		SmartDashboard::PutBoolean("Encoder Stopped", encoder.GetStopped());
		SmartDashboard::PutNumber("Encoder Rate", encoder.GetRate());
		SmartDashboard::PutNumber("Encoder Distance", encoder.GetDistance());
	}
};

START_ROBOT_CLASS(Robot);
