#ifndef CONFIG_H__INCLULDED // checks to see if CONFIG_H__INCLUDED has been defined
#define CONFIG_H__INCLULDED // define CONFIG_H__INCLUDED if it is not already defined


// This file is used to set all constants, including joystick setup and electrical configurations


// Time delays
const float CYCLE_TIME_DELAY = 0.020; // set constant/variable CYCLE_TIME_DELAY to 0.020
const float SOLENOID_STATE_TIME_DELAY = 0.500; // set constant/variable SOLENOID_STATE_TIME_DELAY to 0.500

// Joystick setup
const int NUMBER_OF_JOYSTICKS = 2; // set constant/variable NUMBER_OF_JOYSTICKS to 2
const int PORT_JOYSTICK_1 = 0; // set constant/variable PORT_JOYSTICKS_1 to 0
const int PORT_JOYSTICK_2 = 1; // set constant/variable PORT_JOYSTICKS_2 to 1

// Joystick curve (input^CURVE)
const float CURVE = 1; // set constant/variable CURVE to l

// Joystick 1 (Thrustmaster)
const int AXIS_Y = 1; // set constant/variable AXIS_Y to l
const int AXIS_Z = 2; // set constant/variable AXIS_Z to 2

// Joystick 2 (Logitech)
const int BUTTON_ARM = 8; // set constant/variable BUTTON_ARM to 8
const int BUTTON_CLAW = 7; // set constant/variable BUTTON_CLAW to 7

// Talon ports
const int PORT_LEFT_TALON_1 = 2; // set constant/variable PORT_LEFT_TALON_1 to 2
const int PORT_LEFT_TALON_2 = 3; // set constant/variable PORT_LEFT_TALON_2 to 3
const int PORT_RIGHT_TALON_1 = 0; // set constant/variable PORT_RIGHT_TALON_1 to 0
const int PORT_RIGHT_TALON_2 = 1; // set constant/variable PORT_RIGHT_TALON_2 to 1

// Talon PDP ports (for outputting smart dashboard data)
const int PORT_LEFT_TALON_1_PDP = 0; // set constant/variable PORT_LEFT_TALON_1_PDP to 0
const int PORT_LEFT_TALON_2_PDP = 1; // set constant/variable PORT_LEFT_TALON_2_PDP to 1
const int PORT_RIGHT_TALON_1_PDP = 2; // set constant/variable PORT_RIGHT_TALON_1_PDP to 2
const int PORT_RIGHT_TALON_2_PDP = 3; // set constant/variable PORT_RIGHT_TALON_2_PDP to 3

// Encoder ports
const int PORT_1_LEFT_ENCODER = 0; // set constant/variable PORT_1_LEFT_ENCODER to 0
const int PORT_2_LEFT_ENCODER = 1; // set constant/variable PORT_2_LEFT_ENCODER to 1
const int PORT_1_RIGHT_ENCODER =2; // set constant/variable PORT_1_RIGHT_ENCODER to 2
const int PORT_2_RIGHT_ENCODER = 3; // set constant/variable PORT_2_RIGHT_ENCODER to 3

// Solenoid ports
const int PORT_1_ARM_SOLENOID = 3; // set constant/variable PORT_1_ARM_SOLENOID to 3
const int PORT_2_ARM_SOLENOID = 2; // set constant/variable PORT_2_ARM_SOLENOID to 2
const int PORT_1_CLAW_SOLENOID = 5; // set constant/variable PORT_1_CLAW_SOLENOID to 5
const int PORT_2_CLAW_SOLENOID = 4; // set constant/variable PORT_2_CLAW_SOLENOID to 4

// Solenoid default states
const int ARM_DEFAULT_STATE = 0; // set constant/variable ARM_DEFAULT_STATE to 0
const int CLAW_DEFAULT_STATE = 0; // set constant/variable CLAW_DEFAULT_STATE to 0


#endif /* CONFIG_H__INCLUDED */
