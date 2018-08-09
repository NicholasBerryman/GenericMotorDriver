#pragma once

class MotorController{
  public:
    MotorController(unsigned int forwardsPin, unsigned int backwardsPin);
    MotorController(unsigned int forwardsPin, unsigned int backwardsPin, unsigned int enablePin);
    
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
    int enablePin = -1;
    double setValue = 0.0;
    bool enabledRampRate;
    double rampRate = 1.0;
    long timeAtLastSet = 0;
};

