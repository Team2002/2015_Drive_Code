#ifndef CONSTANTS_H__INCLULDED
#define CONSTANTS_H__INCLULDED


// This file is used to set all constants, including joystick setup and electrical configurations


// Time delays
const float CYCLE_TIME_DELAY = 0.020;
const float SOLENOID_STATE_TIME_DELAY = 0.500;

// Joystick setup
const int NUMBER_OF_JOYSTICKS = 2;
const int PORT_JOYSTICK_1 = 0;
const int PORT_JOYSTICK_2 = 1;

// Joystick curve (input^CURVE)
const float CURVE = 1;

// Joystick 1 (Thrustmaster)
const int AXIS_Y = 1;
const int AXIS_Z = 2;

// Joystick 2 (Logitech)
const int BUTTON_ARM = 8;
const int BUTTON_CLAW = 7;

// Talon ports
const int PORT_LEFT_TALON_1 = 0;
const int PORT_LEFT_TALON_2 = 1;
const int PORT_RIGHT_TALON_1 = 2;
const int PORT_RIGHT_TALON_2 = 3;

// Talon PDP ports (for outputting smart dashboard data)
const int PORT_LEFT_TALON_1_PDP = 0;
const int PORT_LEFT_TALON_2_PDP = 1;
const int PORT_RIGHT_TALON_1_PDP = 2;
const int PORT_RIGHT_TALON_2_PDP = 3;

// Solenoid ports
const int PORT_1_ARM_SOLENOID = 3;
const int PORT_2_ARM_SOLENOID = 2;
const int PORT_1_CLAW_SOLENOID = 5;
const int PORT_2_CLAW_SOLENOID = 4;


#endif /* CONSTANTS_H__INCLUDED */
