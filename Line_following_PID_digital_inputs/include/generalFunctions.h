#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "robotDefines.h"

void ledBlink(void);
//-----------------------------------------------------------------------------
 void checkBTcmd(SoftwareSerial &BT1);  
//------------------------------------------------------------------------
void manualCmd();
//------------------------------------------------------------------------
void sendBTdata (SoftwareSerial &BT1, int data); // send data to BT
//--------------------------------------------------------
void calculatePID();
//-----------------------------------------------
void testLineFollowSensors();
