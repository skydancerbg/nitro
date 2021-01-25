#include <Arduino.h>
#include "Nitrobot.h"

// Possible combinations of the infrared tracking sensor values in binary representation
// Binary value 1 (5V) means line detected, binary 0 (0V) means no line detected
// 0b in the beggining means binary, then each sensor reading in binary /1 or 0/
// from left to right in the direction of robot movement
// TODO originalnite s aktiwna nula!!!!!
// #define IT_ALL_BLACK  0b000
// #define IT_ALL_WHITE  0b111
// #define IT_RIGHT1     0b011
// #define IT_RIGHT2     0b001
// #define IT_CENTER     0b101 
// #define IT_CENTER1    0b010 //This combination is not possible when we use 3 sensors, if left and right sensors are on the line, the middle one will be on the line too
// #define IT_LEFT1      0b110
// #define IT_LEFT2      0b100
// TODO invertirani originalnite !!!!!
#define IT_ALL_BLACK  0b111
#define IT_ALL_WHITE  0b000
#define IT_RIGHT1     0b100 //0b011
#define IT_RIGHT2     0b110//0b001
#define IT_CENTER     0b010 //0b101 
#define IT_CENTER1    0b101 //0b010 //This combination is not possible when we using 3 sensors
                                    //if left and right sensors are on the line, the middle one will be on the line too
#define IT_LEFT1      0b001 //0b110
#define IT_LEFT2      0b011 //0b100

static byte dat = 0;
static int degree = 90;
static int speed = 0;
static int direction = 1;

// Note:  For description of the  direction of movement in US English forward/backward is used,
//        in UK English forwards/backwards is used. Both ways are correct.

void Move();
void MoveForward();
void MoveBackward();
void Stop();
void TurnLeft();
void TurnRight();
void Drive();
byte GetLineSensorReading();
byte GetLeftSensorValue();
byte GetMiddleSensorValue();
byte GetRightSensorValue();

void setup()
{
  Serial.begin(115200);
  pinMode(NB_LN_SENS_PIN_RIGHTEDGE, INPUT);
  pinMode(NB_LN_SENS_PIN_RIGHT, INPUT);
  pinMode(NB_LN_SENS_PIN_MIDDLE, INPUT);
  pinMode(NB_LN_SENS_PIN_LEFT, INPUT);
  pinMode(NB_LN_SENS_PIN_LEFTEDGE, INPUT);
  pinMode(NB_LN_SENS_CALIB_PIN, OUTPUT);
  pinMode(NB_LN_SENS_ANALOG_PIN, INPUT);
}

void loop()
{
  static byte previousReading;
  switch (GetLineSensorReading())
  {
  case IT_ALL_BLACK:
    Stop();
    break;
  case IT_ALL_WHITE:
    if (previousReading == IT_RIGHT1)
    {
      while (GetLineSensorReading() == IT_ALL_WHITE)
      {
        speed= 80;
        degree=180;
        Drive();
      }
      previousReading = 0;
      break;
    }
    if (previousReading == IT_LEFT1)
    {
      while (GetLineSensorReading() == IT_ALL_WHITE)
      {
        speed=80;
        degree=0;
        Drive();
      }
      previousReading = 0;
      break;
    }
    if (previousReading == IT_RIGHT2)
    {
      while (GetLineSensorReading() == IT_ALL_WHITE)
      {
        speed = 60;
        degree=160;
        Drive();
      }
      previousReading = 0;
      break;
    }
    if (previousReading == IT_LEFT2)
    {
      while (GetLineSensorReading() == IT_ALL_WHITE)
      {
        speed=60;
        degree=20;
        Drive();
      }
      previousReading = 0;
      break;
    }
    Stop();
    break;
  case IT_CENTER:
    speed=45;
    MoveForward();
    break;
  case IT_RIGHT1:
    speed=80;
    degree=180;
    Drive();
    previousReading = IT_RIGHT1;
    break;
  case IT_RIGHT2:
    speed=60;
    degree = 160;
    Drive();
    previousReading = IT_RIGHT2;
    break;
  case IT_LEFT1:
    speed=80;
    degree =0;
    Drive();
    previousReading = IT_LEFT1;
    break;
  case IT_LEFT2:
    speed= 60;
    degree=20;
    Drive();
    previousReading = IT_LEFT2;
    break;
  }
}

void Move()
{
  if (direction == 1)
  {
    MoveForward();
  }
  else if (direction == 2)
  {
    MoveBackward();
  }
  else if (direction == 3)
  {
    TurnLeft();
  }
  else if (direction == 4)
  {
    TurnRight();
  }
  else
  {
    Stop();
  }
}

byte GetLineSensorReading()
{
  dat = 0;
  dat = digitalRead(NB_LN_SENS_PIN_LEFT);
  dat |= digitalRead(NB_LN_SENS_PIN_MIDDLE) << 1;
  dat |= digitalRead(NB_LN_SENS_PIN_RIGHT) << 2;
  return dat;
}
byte GetLeftSensorValue()
{
  return digitalRead(NB_LN_SENS_PIN_LEFT);
}

byte GetMiddleSensorValue()
{
  return digitalRead(NB_LN_SENS_PIN_MIDDLE);
}

byte GetRightSensorValue()
{
  return digitalRead(NB_LN_SENS_PIN_RIGHT);
}
void MoveForward()
{
  int value = (speed / 10) * 25;
  analogWrite(NB_IN1_PIN, value);
  analogWrite(NB_IN2_PIN, LOW);
  analogWrite(NB_IN3_PIN, LOW);
  analogWrite(NB_IN4_PIN, value);
}

void MoveBackward()
{
  int value = (speed / 10) * 25;
  analogWrite(NB_IN1_PIN, LOW);
  analogWrite(NB_IN2_PIN, value);
  analogWrite(NB_IN3_PIN, value);
  analogWrite(NB_IN4_PIN, LOW);
}

void Stop()
{
  digitalWrite(NB_IN1_PIN, HIGH);
  digitalWrite(NB_IN2_PIN, HIGH);
  digitalWrite(NB_IN3_PIN, HIGH);
  digitalWrite(NB_IN4_PIN, HIGH);
}

void TurnLeft()
{
  int value = (speed / 10) * 25.5; //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
  analogWrite(NB_IN1_PIN, value);
  analogWrite(NB_IN2_PIN, LOW);
  analogWrite(NB_IN3_PIN, value);
  analogWrite(NB_IN4_PIN, LOW);
}

void TurnRight()
{
  int value = (speed / 10) * 25.5; //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
  analogWrite(NB_IN1_PIN, LOW);
  analogWrite(NB_IN2_PIN, value);
  analogWrite(NB_IN3_PIN, LOW);
  analogWrite(NB_IN4_PIN, value);
}

void Drive()
{
  int value = (speed / 10) * 25.5; //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
  float f;
  if (degree >= 0 && degree <= 90)
  {
    f = (float)(degree) / 90;
    analogWrite(NB_IN1_PIN, (float)(value * f));
    analogWrite(NB_IN2_PIN, LOW);
    analogWrite(NB_IN3_PIN, LOW);
    analogWrite(NB_IN4_PIN, value);
  }
  else if (degree > 90 && degree <= 180)
  {
    f = (float)(180 - degree) / 90;
    analogWrite(NB_IN1_PIN, value);
    analogWrite(NB_IN2_PIN, LOW);
    analogWrite(NB_IN3_PIN, LOW);
    analogWrite(NB_IN4_PIN, (float)(value * f));
  }
  else if (degree > 180 && degree <= 270)
  {
    f = (float)(degree - 180) / 90;
    analogWrite(NB_IN1_PIN, LOW);
    analogWrite(NB_IN2_PIN, value);
    analogWrite(NB_IN3_PIN, (float)(value * f));
    analogWrite(NB_IN4_PIN, LOW);
  }
  else if (degree >= 270 && degree <= 360)
  {
    f = (float)(360 - degree) / 90;
    analogWrite(NB_IN1_PIN, LOW);
    analogWrite(NB_IN2_PIN, (float)(value * f));
    analogWrite(NB_IN3_PIN, value);
    analogWrite(NB_IN4_PIN, LOW);
  }
  else
  {
    Stop();
  }
}