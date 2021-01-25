#include <Arduino.h>

// Stefan 13.11.2020 V2

// https://tutorial.cytron.io/2019/08/21/esp32-pd-line-following-robot-with-maker-line/

#include "Definitions.h"
#include "Nitrobot.h"

#define MAX_SPEED 255
// #define MAX_SPEED 180
// #define MIN_SPEED 150

int adcMakerLine = 0;
int adcSetPoint = 0;
int proportional = 0;
int lastProportional = 0;
int derivative = 0;
int powerDifference = 0;
int motorLeft = 0;
int motorRight = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const int interval = 10;

bool start_following = false;

void robotMove(int speedLeft, int speedRight);

void setup()
{
  pinMode(NB_LN_SENS_PIN_RIGHTEDGE, INPUT);
  pinMode(NB_LN_SENS_PIN_RIGHT, INPUT);
  pinMode(NB_LN_SENS_PIN_MIDDLE, INPUT);
  pinMode(NB_LN_SENS_PIN_LEFT, INPUT);
  pinMode(NB_LN_SENS_PIN_LEFTEDGE, INPUT);
  pinMode(NB_LN_SENS_CALIB_PIN, OUTPUT);
  pinMode(NB_LN_SENS_ANALOG_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(NB_CTRL_BTN_PIN, INPUT);

  adcSetPoint = analogRead(NB_LN_SENS_ANALOG_PIN);
  // Serial.begin(115200);
  // Serial.println("NITRObot PD Line Following Robot with Maker Line");
  // digitalWrite(LED_BUILTIN, LOW); //LED ON

  // while (digitalRead(NB_CTRL_BTN_PIN) == HIGH)
  // {
  //   adcSetPoint = analogRead(NB_LN_SENS_ANALOG_PIN);
  //   Serial.print("ADC SET POINT:\t");
  //   Serial.println(adcSetPoint);
  //   delay(100);
  // }
}

void loop()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;

    adcMakerLine = analogRead(NB_LN_SENS_ANALOG_PIN);

    // Serial.print("ADC:\t");
    // Serial.println(adcMakerLine);

    if (adcMakerLine < 51)
    { // Out of line
      robotMove(0, 0);
    }
    else if (adcMakerLine > 972)
    { // Detects cross line
      robotMove(MAX_SPEED - 25, MAX_SPEED - 25);
    }
    else
    {
      proportional = adcMakerLine - adcSetPoint;
      derivative = proportional - lastProportional;
      lastProportional = proportional;

      powerDifference = (proportional * 1.5) + (derivative * 5);

      if (powerDifference > MAX_SPEED)
      {
        powerDifference = MAX_SPEED;
      }
      if (powerDifference < -MAX_SPEED)
      {
        powerDifference = -MAX_SPEED;
      }

      if (powerDifference < 0)
      {
        motorLeft = MAX_SPEED + powerDifference;
        motorRight = MAX_SPEED;
      }
      else
      {
        motorLeft = MAX_SPEED;
        motorRight = MAX_SPEED - powerDifference;
      }
      robotMove(motorLeft, motorRight);
    }
  }
}

void robotMove(int speedLeft, int speedRight)
{
  speedLeft = constrain(speedLeft, -255, 255);
  speedRight = constrain(speedRight, -255, 255);
  if (speedLeft > 0)
  {
    int speedL = map(speedLeft, 0, 255, 255, 0);
    analogWrite(NB_MOTOR_LEFT_FWD_PIN, speedL);
    analogWrite(NB_MOTOR_LEFT_BKWD_PIN, LOW);
  }
  else
  {
    int speedL = map(speedLeft, -255, 0, 0, 255);
    //SET BACKWARD ROTATION
    analogWrite(NB_MOTOR_LEFT_FWD_PIN, LOW);
    analogWrite(NB_MOTOR_LEFT_BKWD_PIN, speedL);

      Sprint("ROBOT MOVE                            L: Left (-):\t");
      Sprintln(speedLeft);
  }

  if (speedRight > 0)
  {
    int speedR = map(speedRight, 0, 255, 255, 0);
    //SET FORWARD ROTATION
    analogWrite(NB_MOTOR_RIGHT_FWD_PIN, speedR);
    analogWrite(NB_MOTOR_RIGHT_BKWD_PIN, LOW);

    Sprint("ROBOT MOVE           Right:   \t");
    Sprintln(speedRight);
  }
  else
  {
    int speedR = map(speedRight, -255, 0, 0, 255);
    //SET BACKWARDS ROTATION
    analogWrite(NB_MOTOR_RIGHT_FWD_PIN, LOW);
    analogWrite(NB_MOTOR_RIGHT_BKWD_PIN, speedR);
  }
}

//=======================================================================