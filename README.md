# GenericMotorDriver
Generic arduino library for controlling brushed DC motor drivers.

## Usage
Create a `MotorController` object using one of two constructors based on the type of motor driver you're using:  
If your motor driver has an enable pin then use the `MotorController(unsigned int forwardsPin, unsigned int backwardsPin, unsigned int enablePin)` constructor.  
If your motor driver does not have an enable pin then use the `MotorController(unsigned int forwardsPin, unsigned int backwardsPin)`  constructor.  
Once this object has been created the motor can be controlled through the `MotorController.set(double setVal)` method. 
This method expects a floating point number between -1 and 1 with 1 being full power forwards, -1 being full power backwards, and 0 being off.  
  
Additionally, a software ramp-rate can be set using the `MotorController.setRampRate(double rampRate)` method. This method expects a positive number representing %/sec, e.g. 1 = 1 second to full power, 0.5 = 2 seconds to full power.  
After being set, it must be enabled with the `MotorController.enableRampRate()` method, and it may be disabled with the `MotorController.disableRampRate()`  method.
Ramp rate is disabled by default, but if it is enabled before a value is set then the default value of 100%/sec is used. The minimum ramp rate is 0.01 and any value below this is ignored.
