#ifndef DRIVE_H__INCLUDED //Checks to see if DRIVE_H_INCLUDED has been defined 
#define DRIVE_H__INCLUDED //Define the DRIVE_H_INCLUDED variable if it has not already been defined


#include "WPILib.h" //include the WPILib.h library


class Drive{ //Defining the drive class
public: //Variables able to be accessed from outside programs
	Drive(void);
	~Drive(void); 
	
	int Set(float, float);
	
private: //Variables not able to be accessed from outside programs
	Talon* LeftMotor1;
	Talon* LeftMotor2;
	Talon* RightMotor1;
	Talon* RightMotor2;
	Encoder* LeftEncoder;
	Encoder* RightEncoder;

	int distance_since_last;
};


#endif /* DRIVE_H__INCLUDED */
