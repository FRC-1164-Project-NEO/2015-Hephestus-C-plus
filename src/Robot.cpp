#include "WPILib.h"
#include <Joystick.h>
#include <CANJaguar.h>
#include <RobotDrive.h>
#include <Solenoid.h>
#include <DigitalInput.h>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	DigitalInput *limitswitchtop;
	DigitalInput *limitswitchbottom;
	Joystick *shoulderStick;
	CANJaguar *shoulderMotor;
	RobotDrive *Drive;
	Joystick *driveStick;
	Solenoid *gripper;
	Solenoid *gripper2;
	CANJaguar *armExtender;

	CANJaguar *frontLeft;
	CANJaguar *frontRight;
	CANJaguar *rearLeft;
	CANJaguar *rearRight;

	void RobotInit()
	{
		frontLeft = new CANJaguar(8);
		frontRight = new CANJaguar(6);
		rearLeft = new CANJaguar(7);
		rearRight = new CANJaguar(4);

		frontLeft->EnableControl();
		frontRight->EnableControl();
		rearLeft->EnableControl();
		rearRight->EnableControl();

		shoulderStick= new Joystick(0);
		limitswitchtop= new DigitalInput(1);
		limitswitchbottom= new DigitalInput(0);
		lw = LiveWindow::GetInstance();
		shoulderMotor = new CANJaguar(3);
		Drive = new RobotDrive(frontLeft, frontRight, rearLeft, rearRight);
		driveStick = new Joystick(1);
		gripper = new Solenoid(1);
		gripper2 = new Solenoid(0);
		armExtender = new CANJaguar(5);

		shoulderMotor->EnableControl();
		armExtender->EnableControl();

		Drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		Drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		Drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, false);
		Drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, false);

		Drive->SetSafetyEnabled(false);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		bool gripperTest;

		if (shoulderStick->GetRawButton(7) == true)
			gripperTest = true;
		else
			gripperTest = false;

		shoulderMotor->Set((shoulderStick->GetY())/2);

		Drive->MecanumDrive_Cartesian(driveStick->GetX()/2,driveStick->GetY()/2,driveStick->GetTwist()/2,0);

		gripper->Set(gripperTest);
		gripper2->Set(!gripperTest);

		armExtender->Set(shoulderStick->GetZ()*0.50);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
