#include "Drive.h" // includes the Drive.h library
#include "WPILib.h" // includes the WPILib.h library
#include "Config.h" // includes the Config.h library


Drive::Drive(void){ // Drive class
// Talon is a motor controller
// Encoder measures how far it has gone
	LeftMotor1 = new Talon(PORT_LEFT_TALON_1); // creates new variable/constant PORT_LEFT_TALON_1 for object Talon
	LeftMotor2 = new Talon(PORT_LEFT_TALON_2); // creates new variable/constant PORT_LEFT_TALON_2 for object Talon
	RightMotor1 = new Talon(PORT_RIGHT_TALON_1); // creates new variable/constant PORT_LEFT_TALON_1 for object Talon
	RightMotor2 = new Talon(PORT_RIGHT_TALON_2); // creates new variable/constant PORT_RIGHT_TALON_2 for object Talon
	LeftEncoder = new Encoder(PORT_1_LEFT_ENCODER, PORT_2_LEFT_ENCODER); // creates new variable/constant PORT_1_LEFT_ENCODER and PORT_2_LEFT_ENCODER for object Talon
	RightEncoder = new Encoder(PORT_1_RIGHT_ENCODER, PORT_2_RIGHT_ENCODER); // creates new variable/constant PORT_1_RIGHT_ENCODER and PORT_1_RIGHT_ENCODER for onject Encoder

	distance_since_last = 0;
}


Drive::~Drive(void){ // destroy Drive
	// delete all old variables to not waste memory
	delete LeftMotor1; // delete LeftMotor1 variable
	delete LeftMotor2; // delete LeftMotor2 variable
	delete RightMotor1; // delete RightMotor1 variable
	delete RightMotor2; // delete RightMotor2 variable
	delete LeftEncoder; // delete LeftEncoder variable
	delete RightEncoder; // delete RightEncoder variable
}


int Drive::Set(float left_speed, float right_speed){ // function to set left speed and right speed
	distance_since_last = 0;

	LeftMotor1->Set(left_speed); // The right motors are reversed so that passing two positive values to this function will result in the robot moving forward
	LeftMotor2->Set(left_speed);
	RightMotor1->Set(-right_speed);
	RightMotor2->Set(-right_speed);

	return distance_since_last; // return info about back to computer
}
