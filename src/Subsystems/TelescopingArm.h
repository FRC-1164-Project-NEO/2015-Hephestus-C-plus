#ifndef TelescopingArm_H
#define TelescopingArm_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class TelescopingArm: public Subsystem
{
private:
	CANJaguar *armExtender;\

	double integral = 0;
	double lastError = 0;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	TelescopingArm();
	void Update(float z);

	void InitDefaultCommand();
};

#endif
