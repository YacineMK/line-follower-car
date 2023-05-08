#include <QTRSensors.h>
#include <AFMotor.h>

#define SENSOR_PIN_1 A0
#define SENSOR_PIN_2 A1
#define SENSOR_PIN_3 A2
#define SENSOR_PIN_4 A3
#define SENSOR_PIN_5 A4
#define SENSOR_PIN_6 A5
#define SENSOR_PIN_7 A6
#define SENSOR_PIN_8 A7
//#define MOTOR_SPEED 140

int MOTOR_SPEED_SET = 0;
const int MOTOR_SPEED_MAX = 70;

AF_DCMotor leftMotor(6);
AF_DCMotor rightMotor(5);

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

void moveForward() {
  // Set the motor speeds to move forward
  
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  
  for (MOTOR_SPEED_SET = 0; MOTOR_SPEED_SET < MOTOR_SPEED_MAX; MOTOR_SPEED_SET +=2){
    leftMotor.setSpeed(MOTOR_SPEED_SET);
    rightMotor.setSpeed(MOTOR_SPEED_SET);
  }
}

void turnRight() {
  // Set the motor speeds to turn right

  leftMotor.run(FORWARD);
  rightMotor.run(RELEASE);
}
void turnLeft() {
  // Set the motor speeds to turn right
  leftMotor.run(RELEASE);
  rightMotor.run(FORWARD);
}

void arreter(){
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  }



void setup()
{
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){SENSOR_PIN_1, SENSOR_PIN_2, SENSOR_PIN_3, SENSOR_PIN_4, SENSOR_PIN_5,SENSOR_PIN_6,SENSOR_PIN_7, SENSOR_PIN_8}, 8);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop(){
    const int droite = analogRead(SENSOR_PIN_3);
    const int avance1 = analogRead(SENSOR_PIN_4);
    const int avance2 = analogRead(SENSOR_PIN_5);
    const int gauche = analogRead(SENSOR_PIN_6);

    if (avance1 >= 800 && avance2 >= 800 && droite < 200 && gauche < 200){
        moveForward();
      }else if(avance1 >= 800 && avance2 >= 800 && droite >= 800){
          turnRight();
          delay(500);
        }else if (avance1 >= 800 && avance2 >= 800 && gauche >= 800 && droite < 200) {
           turnLeft();
           delay(500);
          }
          /*else if(avance1 >= 800 && avance2 >= 800 && droite > 800 && gauche > 800){
          }*/
          else {
              arreter();
            }
     delay(200);
  }
