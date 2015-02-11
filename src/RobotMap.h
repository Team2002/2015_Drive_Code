// This file maps all of the robot's electrical components and the joystick buttons


/* ********************
 * -- JOYSTICK MAPPING --
 *
 * Forward / Reverse:    Y-Axis
 * Turning:              Z-Axis
 * Speed Multiplier:     Slider
 * Lift Solenoid Toggle: Button 2
 * Claw Solenoid Toggle: Button 4
 ******************** */


// USB
const int PORT_JOYSTICK = 0,

// PWM
PORT_RIGHT_TALON_1 = 1,
PORT_RIGHT_TALON_2 = 2,
PORT_RIGHT_TALON_3 = 3,
PORT_LEFT_TALON_1 = 5,
PORT_LEFT_TALON_2 = 6,
PORT_LEFT_TALON_3 = 7,

// DIO
PORT_1_LIFT_SOLENOID = 0,
PORT_2_LIFT_SOLENOID = 1,
PORT_1_CLAW_SOLENOID = 3,
PORT_2_CLAW_SOLENOID = 4,

// Joystick Mapping
JOYSTICK_BUTTON_LIFT_SOLENOID = 2,
JOYSTICK_BUTTON_CLAW_SOLENOID = 4;