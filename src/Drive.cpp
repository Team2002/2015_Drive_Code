#include "Drive.h"
#include "WPILib.h"
#include "Constants.h"


Drive::Drive(){
	LeftMotor1 = new Talon(PORT_LEFT_TALON_1);
	LeftMotor2 = new Talon(PORT_LEFT_TALON_2);
	RightMotor1 = new Talon(PORT_RIGHT_TALON_1);
	RightMotor2 = new Talon(PORT_RIGHT_TALON_2);
}


Drive::~Drive(){
	delete LeftMotor1;
	delete LeftMotor2;
	delete RightMotor1;
	delete RightMotor2;
}


void Drive::Set (float left_speed, float right_speed){
	LeftMotor1->Set(-left_speed);
	LeftMotor2->Set(-left_speed);
	RightMotor1->Set(right_speed);
	RightMotor2->Set(right_speed);
}
