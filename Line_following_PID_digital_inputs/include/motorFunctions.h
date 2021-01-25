#pragma once

#include <Arduino.h>
#include "robotDefines.h"

void motorStop();
//--------------------------------------------- 
void motorForward();
//---------------------------------------------
void motorBackward();
//---------------------------------------------
void motorFwTime (unsigned int time);
//---------------------------------------------
void motorBwTime (unsigned int time);
//------------------------------------------------
void motorTurn(int direction, int degrees);
//---------------------------------------------------
void motorPIDcontrol();
//-----------------------------
void drivePolygon(unsigned int time, int sides); // for motor test only

