// This file stores constants of the robot's electrical components, joystick mapping, and other constants


// Other constants
const int AUTONOMOUS_PROGRAM = 0;     // Macro file number to play in autonomous mode
const float CYCLE_TIME_DELAY = 0.020, // Time to wait in seconds between each cycle. This gives the motors time to update
SOLENOID_STATE_TIME_DELAY = 0.25,     // Time to wait in seconds between toggling a solenoid's state and turning the solenoid off
INTAKE_SPEED = 0.3;                   // Speed to run the intake motors when taking in bins and totes

// Joystick 2 Mapping
const int JOYSTICK_BUTTON_LIFT_SOLENOID = 4,
JOYSTICK_BUTTON_CLAW_SOLENOID = 2,
JOYSTICK_BUTTON_INTAKE_SOLENOID = 1,
JOYSTICK_BUTTON_DOOR_SOLENOID = 3,
JOYSTICK_BUTTON_LEFT_INTAKE_MOTOR_IN = 5,
JOYSTICK_BUTTON_LEFT_INTAKE_MOTOR_OUT = 7,
JOYSTICK_BUTTON_RIGHT_INTAKE_MOTOR_IN = 6,
JOYSTICK_BUTTON_RIGHT_INTAKE_MOTOR_OUT = 8,

// Joysticks
NUMBER_OF_JOYSTICKS = 2,
PORT_JOYSTICK_1 = 0,
PORT_JOYSTICK_2 = 1,

// Talons
NUMBER_OF_TALONS = 6,
PORT_RIGHT_TALON_1 = 4,
PORT_RIGHT_TALON_2 = 5,
PORT_LEFT_TALON_1 = 2,
PORT_LEFT_TALON_2 = 3,
PORT_RIGHT_INTAKE_TALON = 1,
PORT_LEFT_INTAKE_TALON = 0,

// Solenoids
NUMBER_OF_SOLENOIDS = 4,
PORT_1_LIFT_SOLENOID = 0,
PORT_2_LIFT_SOLENOID = 1,
PORT_1_CLAW_SOLENOID = 4,
PORT_2_CLAW_SOLENOID = 5,
PORT_1_INTAKE_SOLENOID = 2,
PORT_2_INTAKE_SOLENOID = 3,
PORT_1_DOOR_SOLENOID = 6,
PORT_2_DOOR_SOLENOID = 7;
