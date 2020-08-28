#include <Ultrasonic.h>
#include <SoftwareSerial.h>

/*
  Konstantin 2wd robot - Arduino sketch
  - https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
  - https://github.com/ErickSimoes/Ultrasonic
*/

/* motors */
#define HG7881_B_IA 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 3 // D11 --> Motor B Input B --> MOTOR B -
#define HG7881_A_IA 5 // D6  --> Motor A Input A --> MOTOR A +
#define HG7881_A_IB 11 // D5  --> Motor A Input B --> MOTOR A -
#define MOTOR_LEFT_PWM HG7881_A_IA // Motor B PWM Speed
#define MOTOR_LEFT_DIR HG7881_A_IB // Motor B Direction
#define MOTOR_RIGHT_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_RIGHT_DIR HG7881_B_IB // Motor B Direction

/* drive */
#define PWM_SLOW 100  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 255 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 250 // brief delay for abrupt motor changes

/* sonar */
#define SONAR_TRIG A0
#define SONAR_ECHO A1
#define SONAR_TIMEOUT 40000UL
Ultrasonic sonar(SONAR_TRIG, SONAR_ECHO, SONAR_TIMEOUT);

/* status */
#define FORWARD_LEFT 1
#define FORWARD 2
#define FORWARD_RIGHT 3
#define LEFT 4
#define STOP 5
#define RIGHT 6
#define BACKWARD_LEFT 7
#define BACKWARD 8
#define BACKWARD_RIGHT 9
byte STATUS = STOP;


/* infrared */
#define IR_LEFT 6
#define IR_RIGHT 7

/* Serial */
#define SERIAL_BAUD 115200

/* Bluetooth */
#define BLUETOOTH_RX 9
#define BLUETOOTH_TX 8
#define BLUETOOTH_BAUD 9600
const String BLUETOOTH_NAME = "Konstantin";
SoftwareSerial Bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

/* Buzzer */
const int buzzer = 4; //buzzer to arduino pin 9

int distance;
int ir_left;
int ir_right;

void setup()
{
  Serial.begin( SERIAL_BAUD );
  Bluetooth.begin(BLUETOOTH_BAUD);
  Bluetooth.print("AT+NAME" + BLUETOOTH_NAME);

  pinMode(IR_LEFT, INPUT );
  pinMode(IR_RIGHT, INPUT);

  pinMode( MOTOR_LEFT_DIR, OUTPUT );
  pinMode( MOTOR_LEFT_PWM, OUTPUT );
  pinMode( MOTOR_RIGHT_DIR, OUTPUT );
  pinMode( MOTOR_RIGHT_PWM, OUTPUT );

  pinMode(buzzer, OUTPUT);
  
  stop();
}

void loop()
{
//
//tone(buzzer, 50); // Send 1KHz sound signal...
//  delay(1000);        // ...for 1 sec
//  noTone(buzzer);     // Stop sound...
//  delay(1000);        // ...for 1sec
//
//  return;
  
  distance = sonar.read(CM);
  ir_left = digitalRead(IR_LEFT);
  ir_right = digitalRead(IR_RIGHT);

  if (!canGoForward() && isGoingForward()) {
    stop();
    Bluetooth.print("stop forward ");
    Bluetooth.print(distance);
    Bluetooth.println("cm");
  }

  if (Bluetooth.available()) {
    switch ( Bluetooth.read() )
    {
      case '1':
        Bluetooth.print( "forward left " );
        Bluetooth.print(distance);
        Bluetooth.println("cm");
        forwardLeftSafe(PWM_FAST);
        break;

      case '2':
        Bluetooth.print( "forward " );
        Bluetooth.print(distance);
        Bluetooth.println("cm");
        forwardSafe(PWM_FAST);
        break;

      case '3':
        Bluetooth.print( "forward right " );
        Bluetooth.print(distance);
        Bluetooth.println("cm");
        forwardRightSafe(PWM_FAST);
        break;

      case '4':
        Bluetooth.println( "left" );
        left(PWM_FAST);
        break;

      case '5':
        Bluetooth.println( "stop" );
        stop();
        break;

      case '6':
        Bluetooth.println( "right" );
        right(PWM_FAST);
        break;

      case '7':
        Bluetooth.print( "backward left" );
        backwardLeft(PWM_FAST);
        break;

      case '8':
        Bluetooth.println( "backward " );
        backward(PWM_FAST);
        break;

      case '9':
        Bluetooth.print( "backward right" );
        backwardRight(PWM_FAST);
        break;
    }
  }


  return;

  if (canGoForward()) {
    forward(PWM_FAST);
  } else {
    if (STATUS == LEFT) left(PWM_FAST);
    else if (STATUS == RIGHT) right(PWM_FAST);
    else left(PWM_FAST);
    delay(250);
    stop();
  }

  //    delay(200/);//


  return;

  boolean isValidInput;
  // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Fast forward" );
  Serial.println( "2) Forward" );
  Serial.println( "3) Soft stop (coast)" );
  Serial.println( "4) Reverse" );
  Serial.println( "5) Fast reverse" );
  Serial.println( "6) Hard stop (brake)" );
  Serial.println( "7) left" );
  Serial.println( "8) right" );
  Serial.println( "-----------------------------" );
  do
  {
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while ( !Serial.available() )
      ; // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch ( c )
    {
      case '1': // 1) Fast forward
        Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        stop();
        delay( DIR_DELAY );
        // set the motor speed and direction
        forward(PWM_FAST);
        isValidInput = true;
        break;

      case '2': // 2) Forward
        Serial.println( "Forward..." );
        // always stop motors briefly before abrupt changes
        stop();
        delay( DIR_DELAY );
        // set the motor speed and direction
        forward(PWM_SLOW);
        isValidInput = true;
        break;

      case '3': // 3) Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        stop();
        isValidInput = true;
        break;

      case '4': // 4) Reverse
        Serial.println( "Reverse..." );
        // always stop motors briefly before abrupt changes
        stop();
        delay( DIR_DELAY );
        // set the motor speed and direction
        backward(PWM_SLOW);
        isValidInput = true;
        break;

      case '5': // 5) Fast reverse
        Serial.println( "Fast reverse..." );
        // always stop motors briefly before abrupt changes
        stop();
        delay( DIR_DELAY );
        // set the motor speed and direction
        backward(PWM_FAST);
        isValidInput = true;
        break;

      case '6': // 6) Hard stop (use with caution)
        Serial.println( "Hard stop (brake)..." );
        digitalWrite( MOTOR_LEFT_DIR, HIGH );
        digitalWrite( MOTOR_LEFT_PWM, HIGH );
        digitalWrite( MOTOR_RIGHT_DIR, HIGH );
        digitalWrite( MOTOR_RIGHT_PWM, HIGH );
        isValidInput = true;
        break;

      case '7': // 7) Left
        Serial.println( "Left..." );
        // always stop motors briefly before abrupt changes
        stop();
        delay( DIR_DELAY );
        // set the motor speed and direction
        left(PWM_FAST);
        isValidInput = true;
        break;

      case '8': // 8) Right
        Serial.println( "Right..." );
        // always stop motors briefly before abrupt changes
        stop();
        delay( DIR_DELAY );
        // set the motor speed and direction
        right(PWM_FAST);
        isValidInput = true;
        break;

      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while ( isValidInput == true );

  // repeat the main loop and redraw the menu...
}
