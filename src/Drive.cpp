#include "Drive.h"
#include "WPILib.h"
#include "Config.h"


Drive::Drive(void){
	LeftMotor1 = new Talon(PORT_LEFT_TALON_1);
	LeftMotor2 = new Talon(PORT_LEFT_TALON_2);
	RightMotor1 = new Talon(PORT_RIGHT_TALON_1);
	RightMotor2 = new Talon(PORT_RIGHT_TALON_2);
	LeftEncoder = new Encoder(PORT_1_LEFT_ENCODER, PORT_2_LEFT_ENCODER);
	RightEncoder = new Encoder(PORT_1_RIGHT_ENCODER, PORT_2_RIGHT_ENCODER);

	distance_since_last = 0;
}


Drive::~Drive(void){
	delete LeftMotor1;
	delete LeftMotor2;
	delete RightMotor1;
	delete RightMotor2;
	delete LeftEncoder;
	delete RightEncoder;
}


int Drive::Set(float left_speed, float right_speed){
	distance_since_last = 0;

	LeftMotor1->Set(left_speed); // The right motors are reversed so that passing two positive values to this function will result in the robot moving forward
	LeftMotor2->Set(left_speed);
	RightMotor1->Set(-right_speed);
	RightMotor2->Set(-right_speed);

	return distance_since_last;
}
