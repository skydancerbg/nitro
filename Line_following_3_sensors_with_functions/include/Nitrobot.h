#ifndef _NITROBOT_H_
#define _NITROBOT_H_
#endif

#include <stdint.h>
#include "Arduino.h"

#define NB_CTRL_BTN_PIN 53

#define NB_IR_PIN 11

// MOTOR CONTROLLER
#define NB_IN1_PIN 6
#define NB_IN2_PIN 10
#define NB_IN4_PIN 9
#define NB_IN3_PIN 5

#define NB_Usonic_Pin 3
#define NB_RGB_PIN 2
#define NB_SERVO_PIN 13

#define NB_IR_AVOIDANCE_LEFT_PIN 12
#define NB_IR_AVOIDANCE_RIGHT_PIN A5
#define NB_PHOTO_LEFT_PIN A3
#define NB_PHOTO_RIGHT_PIN A4
// For Emakefun line sensor
//! SENSOR POSITIONS LISTED OPPOSITE OF THE DIRECTION OF MOVEMENT 
#define NB_INFRARED_TRACKING_PIN1 A2
#define NB_INFRARED_TRACKING_PIN2 A1
#define NB_INFRARED_TRACKING_PIN3 A0

// // Define Cytron Maker Line sensor connection pins
// //! SENSOR POSITIONS LISTED IN THE DIRECTION OF MOVEMENT
// //   Arduino MEGA pin:        Sensor pin:
// #define NB_LN_SENS_PIN_RIGHTEDGE 22       // right edge sensor - Connected to D1 pin of the sensor
// // #define LN_SENS_PIN_RIGHT 23       // right sensor - Connected to D2 pin of the sensor
// #define NB_LN_SENS_PIN_RIGHT 25       // right sensor - Connected to D2 pin of the sensor
// #define NB_LN_SENS_PIN_MIDDLE 24       // middle sensor - Connected to D3 pin of the sensor
// // #define LN_SENS_PIN_LEFT 25       // left sensor Connected to D4 pin of the sensor
// #define NB_LN_SENS_PIN_LEFT 23       // left sensor Connected to D4 pin of the sensor
// #define NB_LN_SENS_PIN_LEFTEDGE 26       // left edge sensor - Connected to D5 pin of the sensor
// #define NB_LN_SENS_CALIB_PIN 27   // Connected to CAL pin of the sensor
// // https://github.com/arduino/Arduino/blob/1.8.4/hardware/arduino/avr/variants/mega/pins_arduino.h#L51-L83
// #define NB_LN_SENS_ANALOG_PIN A15 // Connected to AN pin of the sensor

// Define Cytron Maker Line sensor connection pins
//! Za testa razmeniam liav i desen senzor!!!!!!! da se razkara
//   Arduino MEGA pin:        Sensor pin:
#define NB_LN_SENS_PIN_RIGHTEDGE 22       // right edge sensor - Connected to D1 pin of the sensor
#define NB_LN_SENS_PIN_RIGHT 23       // right sensor - Connected to D2 pin of the sensor
// #define NB_LN_SENS_PIN_RIGHT 25       // right sensor - Connected to D2 pin of the sensor
#define NB_LN_SENS_PIN_MIDDLE 24       // middle sensor - Connected to D3 pin of the sensor
#define NB_LN_SENS_PIN_LEFT 25       // left sensor Connected to D4 pin of the sensor
// #define NB_LN_SENS_PIN_LEFT 23       // left sensor Connected to D4 pin of the sensor
#define NB_LN_SENS_PIN_LEFTEDGE 26       // left edge sensor - Connected to D5 pin of the sensor
#define NB_LN_SENS_CALIB_PIN 27   // Connected to CAL pin of the sensor
// https://github.com/arduino/Arduino/blob/1.8.4/hardware/arduino/avr/variants/mega/pins_arduino.h#L51-L83
#define NB_LN_SENS_ANALOG_PIN A15 // Connected to AN pin of the sensor


#define NB_PS2X_CLK 11
#define NB_PS2X_CMD 7
#define NB_PS2X_ATT 8
#define NB_PS2X_DAT 4

#define NB_NRF24L01_CE 4
#define NB_NRF24L01_CSN 7
#define NB_NRF24L01_MOSI 11
#define NB_NRF24L01_MISO 12
#define NB_NRF24L01_SCK 13
#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define MIDDLE 3


