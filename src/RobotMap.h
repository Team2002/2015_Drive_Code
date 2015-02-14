// This file stores constants of the robot's electrical components, joystick mapping, and default solenoid states


/* ********************
 * -- JOYSTICK MAPPING --
 *
 * Forward / Reverse:    Y-Axis
 * Turning:              Z-Axis
 * Speed Multiplier:     Slider
 * Lift Solenoid Toggle: Button 2
 * Claw Solenoid Toggle: Button 4
 * Door Solenoid Toggle: Button 1
 ******************** */

 
// Joystick Mapping
const int JOYSTICK_BUTTON_LIFT_SOLENOID = 2,
JOYSTICK_BUTTON_CLAW_SOLENOID = 4,
JOYSTICK_BUTTON_DOOR_SOLENOID = 1,

// Joysticks
NUMBER_OF_JOYSTICKS = 1,
PORT_JOYSTICK = 0,

// Talons
NUMBER_OF_TALONS = 4,
PORT_RIGHT_TALON_1 = 1,
PORT_RIGHT_TALON_2 = 2,
PORT_LEFT_TALON_1 = 3,
PORT_LEFT_TALON_2 = 4,

// Solenoids
NUMBER_OF_SOLENOIDS = 3,
PORT_1_LIFT_SOLENOID = 0,
PORT_2_LIFT_SOLENOID = 1,
PORT_1_CLAW_SOLENOID = 2,
PORT_2_CLAW_SOLENOID = 3,
PORT_1_DOOR_SOLENOID = 4,
PORT_2_DOOR_SOLENOID = 5;
