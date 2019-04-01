// PIN
#define BUZZER                      2
#define RF_CE                       7
#define RF_CSN                      8
#define LIGHT_YELLOW                0
#define LIGHT_RED                   1
#define LIGHT_BLUE                  A4
#define MOTOR_LEFT_ENCODER          3
#define MOTOR_LEFT_INPUT_1          5   
#define MOTOR_LEFT_INPUT_2          6
#define MOTOR_RIGHT_ENCODER         4
#define MOTOR_RIGHT_INPUT_1         9
#define MOTOR_RIGHT_INPUT_2         10
#define SENSOR_LIGHT                A0
#define SENSOR_SOUND                A1
#define SENSOR_ULTRASONIC_TRIGGER   A2
#define SENSOR_ULTRASONIC_ECHO      A3

// SLAVE MODES
#define MODE_FUNCTION               1
#define MODE_MODIFIER_LOOP          2
#define MODE_SLAVE_FORWARD_ARROW    3
#define MODE_SLAVE_BACKWARD_ARROW   4
#define MODE_SLAVE_LEFT_ARROW       5
#define MODE_SLAVE_RIGHT_ARROW      6
#define MODE_SLAVE_LIGHT            7
#define MODE_SLAVE_SOUND            8

// ROBOT DIMENTIONS
#define WHEEL_GEAR_RATIO            5       // Motor gearbox reduction
#define WHEEL_CIRCUMFERENCE         25      // Wheel circumference in cm
#define ROBOT_CIRCUMFERENCE         37      // Wheel to wheel distance in cm
#define ROBOT_SPEED                 4       // RPM

// ENCODER
#define ENCODER_HOLES               30 * WHEEL_GEAR_RATIO
#define ENCODER_STEPS_X_CM          ENCODER_HOLES / WHEEL_CIRCUMFERENCE
#define ENCODER_CM_TO_ROTATE_90     ROBOT_CIRCUMFERENCE / 4 
#define ENCODER_ISR_QUERY_INTERVAL  50      // microseconds
#define ENCODER_RPM_QUERY_INTERVAL  200000  // microseconds

// MOTOR
#define MOTOR_PID_kP                0.80
#define MOTOR_PID_kI                14.00
#define MOTOR_PID_kD                0.00
#define MOTOR_PWM_PINS_QTY          4
#define MOTOR_PWM_FREQUENCY         1       // microseconds. 1/(2*freq)

// LIGHT
#define STATE_LED_OFF               0
#define STATE_LED_ON                1
#define STATE_LED_BLINK             2

// RF
#define RF_CLIENT_ADDRESS           1
#define RF_SERVER_ADDRESS           2
#define RF_WAIT_TIMEOUT             7000    // milliseconds

// SLAVE MODES
#define MODE_MODIFIER_LOOP          1
#define MODE_SLAVE_FORWARD_ARROW    2
#define MODE_SLAVE_LEFT_ARROW       2
#define MODE_SLAVE_RIGHT_ARROW      3
#define MODE_FUNCTION               4


// GENERAL
#define DEBUG                       true
#define SILENT                      false