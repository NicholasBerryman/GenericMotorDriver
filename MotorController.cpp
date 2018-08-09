#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(unsigned int forwardsPin, unsigned int backwardsPin){
  this->forwardPin = forwardsPin;
  this->backwardPin = backwardsPin;
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
}

MotorController::MotorController(unsigned int forwardPin, unsigned int backwardsPin, unsigned int enablePin) 
  : MotorController::MotorController(forwardPin,backwardsPin)
{
  this->enablePin = enablePin;
  pinMode(enablePin, OUTPUT);
}

void MotorController::setRampRate(double toSet){
  rampRate = toSet;
  if (rampRate <= 0.01){
    rampRate = 0.01;
  }
}

void MotorController::enableRampRate(){
  enabledRampRate = true;
}

void MotorController::disableRampRate(){
  enabledRampRate = false;
  timeAtLastSet = 0;
}

double MotorController::get(){
  return setValue;
}

void MotorController::set(double powerPercent){
  if (powerPercent > 1) powerPercent = 1;
  else if (powerPercent < -1) powerPercent = -1;
  
  if (timeAtLastSet != 0 || !enabledRampRate){
    double adjustedRamp = rampRate * (millis()-timeAtLastSet)/1000.0;
    if (!enabledRampRate || abs(setValue - powerPercent) <= adjustedRamp)
      setValue = powerPercent;
    else if (powerPercent < setValue)
      setValue -= adjustedRamp;
    else if (powerPercent > setValue){
      setValue += adjustedRamp;
    }

    
    if (setValue > 0){
      if (enablePin >= 0){
        digitalWrite(forwardPin, 1);
        digitalWrite(backwardPin, 0);
      }
      else{
        analogWrite(forwardPin, 255*setValue);
        analogWrite(backwardPin, 0);
      }
    }
    else if (setValue < 0){
      if (enablePin >= 0){
        digitalWrite(forwardPin, 0);
        digitalWrite(backwardPin, 1);
      }
      else{
        analogWrite(forwardPin, 0);
        analogWrite(backwardPin, 255*-setValue);
      }
    }
    else{
      digitalWrite(forwardPin,0);
      digitalWrite(backwardPin,0);
    }
    if (enablePin >= 0) analogWrite(enablePin, 255*setValue);
  }
  timeAtLastSet = millis();
}



