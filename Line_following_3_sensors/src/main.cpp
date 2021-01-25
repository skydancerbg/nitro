#include <Arduino.h>

// Define motor driver pins
#define IN1_PIN 6  // PWMB
#define IN2_PIN 10 // DIRB  ---  right
#define IN4_PIN 9  // PWMA
#define IN3_PIN 5  // DIRA  ---  left

// Define Cytron Maker Line sensor connection pins
//   Arduino MEGA pin:        Sensor pin:
#define LN_SENS_PIN_RIGHTEDGE 22       // right edge sensor - Connected to D1 pin of the sensor
// #define LN_SENS_PIN_RIGHT 23       // right sensor - Connected to D2 pin of the sensor
#define LN_SENS_PIN_RIGHT 25       // right sensor - Connected to D2 pin of the sensor
#define LN_SENS_PIN_MIDDLE 24       // middle sensor - Connected to D3 pin of the sensor
// #define LN_SENS_PIN_LEFT 25       // left sensor Connected to D4 pin of the sensor
#define LN_SENS_PIN_LEFT 23       // left sensor Connected to D4 pin of the sensor
#define LN_SENS_PIN_LEFTEDGE 26       // left edge sensor - Connected to D5 pin of the sensor
#define LN_SENS_CALIB_PIN 27   // Connected to CAL pin of the sensor
#define LN_SENS_ANALOG_PIN A15 // Connected to AN pin of the sensor

void setup()
{
  Serial.begin(115200);
  pinMode(LN_SENS_PIN_RIGHTEDGE, INPUT);
  pinMode(LN_SENS_PIN_RIGHT, INPUT);
  pinMode(LN_SENS_PIN_MIDDLE, INPUT);
  pinMode(LN_SENS_PIN_LEFT, INPUT);
  pinMode(LN_SENS_PIN_LEFTEDGE, INPUT);
  pinMode(LN_SENS_CALIB_PIN, OUTPUT);
  pinMode(LN_SENS_ANALOG_PIN, INPUT);
}

void loop()
{
  int leftEdge,left, mid, right, rightEdge;
  //
  // left = digitalRead(LN_SENS_PIN_LEFT);
  // mid = digitalRead(LN_SENS_PIN_MIDDLE);
  // right = digitalRead(LN_SENS_PIN_RIGHT);
  // gledani sre]i dwivenieto
  left = digitalRead(LN_SENS_PIN_RIGHT);
  mid = digitalRead(LN_SENS_PIN_MIDDLE);
  right = digitalRead(LN_SENS_PIN_LEFT);

  leftEdge  = digitalRead(LN_SENS_PIN_RIGHTEDGE);
  rightEdge  = digitalRead(LN_SENS_PIN_LEFTEDGE);

  // Serial.print ("LeftEdge: ");
  // Serial.print (leftEdge);
  // Serial.print (" Left: ");
  // Serial.print (left);
  // Serial.print (" Middle: ");
  // Serial.print (mid);
  // Serial.print (" Right: ");
  // Serial.print (right);
  // Serial.print (" RightEdge: ");
  // Serial.println (rightEdge);
  // delay(500);


  if ((right == 1) && (mid == 0) && (left == 1)) //*******直行*******//
  {
    analogWrite(IN1_PIN, 80);
    analogWrite(IN2_PIN, LOW); //the speed value of motorA is val
    analogWrite(IN3_PIN, LOW); //the speed value of motorB is val
    analogWrite(IN4_PIN, 80);
  }
  else if ((right == 0) && (mid == 1) && (left == 1)) //***左偏,右转***//
  {
    analogWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, 80);  //the speed value of motorB is val
    analogWrite(IN3_PIN, LOW); //the speed value of motorB is val
    analogWrite(IN4_PIN, 180);
  }
  else if ((right == 0) && (mid == 0) && (left == 1)) //***左偏,右转***//
  {
    analogWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, 70);  //the speed value of motorB is val
    analogWrite(IN3_PIN, LOW); //the speed value of motorB is val
    analogWrite(IN4_PIN, 120);
  }
  else if ((right == 1) && (mid == 1) && (left == 0)) //***右偏，左转***//
  {
    analogWrite(IN1_PIN, 180);
    analogWrite(IN2_PIN, LOW); //the speed value of motorB is val
    analogWrite(IN3_PIN, 80);  //the speed value of motorB is val
    analogWrite(IN4_PIN, LOW);
  }

  else if ((right == 1) && (mid == 0) && (left == 0)) //***右偏，左转***//
  {
    analogWrite(IN1_PIN, 120);
    analogWrite(IN2_PIN, LOW); //the speed value of motorB is val
    analogWrite(IN3_PIN, 70);  //the speed value of motorB is val
    analogWrite(IN4_PIN, LOW);
  }
  else if ((right == 0) && (mid == 0) && (left == 0)) //*******停止*******//
  {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, HIGH);
  }
}
