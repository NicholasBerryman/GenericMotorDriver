#include <Arduino.h>
#include "MotorController.h"

MotorController::MotorController(unsigned int forwardsPin, unsigned int backwardsPin, bool pin1IsDirection){
  this->forwardPin = forwardsPin;
  this->backwardPin = backwardsPin;
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pin1Direction = pin1IsDirection;
  enabledRampRate = false;
}

MotorController::MotorController(unsigned int forwardPin, unsigned int backwardsPin, int enablePin) 
  : MotorController::MotorController(forwardPin,backwardsPin, false)
{
  this->enablePin = (unsigned int)enablePin;
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
        if (!pin1Direction){
          analogWrite(forwardPin, PWMRANGE*setValue);
          analogWrite(backwardPin, 0);
        }
        else{
          digitalWrite(forwardPin, 1);
          analogWrite(backwardPin, setValue);
        }
      }
    }
    else if (setValue < 0){
      if (enablePin >= 0){
        digitalWrite(forwardPin, 0);
        digitalWrite(backwardPin, 1);
      }
      else{
        if (!pin1Direction){
          analogWrite(forwardPin, 0);
          analogWrite(backwardPin, PWMRANGE*-setValue);
        }
        else{
          digitalWrite(forwardPin, 0);
          analogWrite(backwardPin, setValue);
        }
      }
    }
    else{
      digitalWrite(forwardPin,0);
      digitalWrite(backwardPin,0);
    }
    double setVal = PWMRANGE*setValue;
    if (enablePin >= 0) analogWrite(enablePin, abs(setVal));
  }
  timeAtLastSet = millis();
}
