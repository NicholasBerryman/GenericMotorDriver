#pragma once

#ifndef PWMRANGE
#define PWMRANGE 255
#endif

class MotorController{
  public:
    /**
     * \param pin1 First pin
     * \param pin2 Second pin
     * \param pin1IsDirection false if pin1 is not used for direction, true if pin1 is a direction pin (Should be labelled on motor driver board)
     */
    MotorController(unsigned int pin1, unsigned int pin2, bool pin1IsDirection);
    /**
     * \param forwardsPin pin for forward speed
     * \param backwardsPin pin for reverse speed
     * \param enablePin pin for enabling the motor
     */
    MotorController(unsigned int forwardsPin, unsigned int backwardsPin, int enablePin);
    
    /**
     * \param powerPercent Number between -1 and 1 representing power to send to the motor (negative values cause motor to reverse)
     */
    void set(double powerPercent);
    double get();
    void setRampRate(double rampRatePerSec);
    void enableRampRate();
    void disableRampRate();

  private:
    unsigned int forwardPin;
    unsigned int backwardPin;
    bool pin1Direction;
    int enablePin = -1;
    double setValue = 0.0;
    bool enabledRampRate = false;
    double rampRate = 1.0;
    long timeAtLastSet = 0;
};
