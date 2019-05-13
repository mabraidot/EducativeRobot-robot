// PIN
#define BUZZER                      2
#define RF_CE                       7
#define RF_CSN                      8
#define LIGHT_RED                   1
#define LIGHT_GREEN                 0
#define LIGHT_BLUE                  A4
#define MOTOR_LEFT_ENCODER          3
#define MOTOR_LEFT_INPUT            5   
#define MOTOR_RIGHT_ENCODER         4
#define MOTOR_RIGHT_INPUT           10
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
#define WHEEL_CIRCUMFERENCE         59      // (26.9cm)+ Wheel circumference in cm. Radius times pi
#define ROBOT_CIRCUMFERENCE         10.5      // (48.7) Wheel to wheel diameter in cm times pi
#define DIDACTIC_MAP_BLOCK_SIZE     20      // Size of the map grid where robot moves on in cm

// ENCODER
#define ENCODER_HOLES               30 //13
#define ENCODER_STEPS_X_CM          ENCODER_HOLES / WHEEL_CIRCUMFERENCE
#define ENCODER_CM_TO_ROTATE_90     ROBOT_CIRCUMFERENCE / 4 
#define ENCODER_ISR_QUERY_INTERVAL  50      // microseconds
#define ENCODER_RPM_QUERY_INTERVAL  200000  // microseconds

// MOTOR
#define SERVO_LEFT_FORWARD_SPEED    117
#define SERVO_LEFT_BACKWARD_SPEED   49
#define SERVO_RIGHT_FORWARD_SPEED   42
#define SERVO_RIGHT_BACKWARD_SPEED  110

// LIGHT
#define STATE_LED_OFF               0
#define STATE_LED_ON                1
#define STATE_LED_BLINK             2

// RF
#define RF_CLIENT_ADDRESS           1
#define RF_SERVER_ADDRESS           2
#define RF_WAIT_TIMEOUT             7000    // milliseconds

// GENERAL
#define DEBUG                       true
#define SILENT                      false