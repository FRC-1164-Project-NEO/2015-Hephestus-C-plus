#include "TelescopingArm.h"
//#include "../RobotMap.h"
#include <Joystick.h>
#include <CANJaguar.h>

TelescopingArm::TelescopingArm() :
		Subsystem("ExampleSubsystem")
{
	armExtender = new CANJaguar(5);

	armExtender->EnableControl();

}

void TelescopingArm::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void TelescopingArm::Update(float z){
	double error = 0;
	double derivitive = 0;
	double output = 0;

	error =
	armExtender->Set(z*0.50);
}
