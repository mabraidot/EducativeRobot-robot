// PIN
#define BUZZER                      2
#define RF_CE                       7
#define RF_CSN                      8
#define LIGHT_RED                   1
#define LIGHT_RED_MASK_LOW          B11111101
#define LIGHT_RED_MASK_HIGH         B00000010
#define LIGHT_GREEN                 0
#define LIGHT_GREEN_MASK_LOW        B11111110
#define LIGHT_GREEN_MASK_HIGH       B00000001
#define LIGHT_BLUE                  A4
#define LIGHT_BLUE_MASK_LOW         B11101111
#define LIGHT_BLUE_MASK_HIGH        B00010000
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
#define MODE_SLAVE_WAIT_LIGHT       7
#define MODE_SLAVE_WAIT_SOUND       8
#define MODE_SLAVE_SOUND            9
#define MODE_SLAVE_LIGHT            10
#define MODE_WHILE_START            11
#define MODE_WHILE_END              12
#define MODE_END_OF_PROGRAM         99

// ROBOT DIMENTIONS
#define WHEEL_CIRCUMFERENCE         26.9    // Wheel circumference in cm. Diameter times pi
#define DIDACTIC_MAP_BLOCK_SIZE     20      // Size of the map grid where robot moves on in cm
#define CM_TO_ROTATE_90             11.7 
#define ROBOT_SPEED                 16      // RPM
#define ROBOT_TURN_SPEED            16      // RPM

// ENCODER
#define ENCODER_HOLES               60
#define ENCODER_STEPS_X_CM          ENCODER_HOLES / WHEEL_CIRCUMFERENCE
#define ENCODER_ISR_QUERY_INTERVAL  50      // Microseconds
#define TICKS_RPM_COUNTER           5       // Encoder holes to count before rpm calculations

// MOTOR
#define MOTOR_PID_SAMPLE_TIME       10     // Milliseconds
//k1,0.5,4.2,0
#define MOTOR_LEFT_PID_kP           0.50
#define MOTOR_LEFT_PID_kI           4.20
#define MOTOR_LEFT_PID_kD           0.00
//k2,0.6,6.6,0
#define MOTOR_RIGHT_PID_kP          0.60
#define MOTOR_RIGHT_PID_kI          6.70
#define MOTOR_RIGHT_PID_kD          0.00


// LIGHT
#define STATE_LED_OFF               0
#define STATE_LED_ON                1
#define STATE_LED_BLINK             2

// RF
#define RF_CLIENT_ADDRESS           1
#define RF_SERVER_ADDRESS           2
#define RF_WAIT_TIMEOUT             7000    // milliseconds

// GENERAL
#define DEBUG                       false //Disable to use RGB headlights
#define SILENT                      false