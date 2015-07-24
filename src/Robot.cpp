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
	int POV;

	void RobotInit()
	{
		frontLeft = new CANJaguar(8);
		frontRight = new CANJaguar(7);
		rearLeft = new CANJaguar(6);
		rearRight = new CANJaguar(4);

		frontLeft->EnableControl();
		frontRight->EnableControl();
		rearLeft->EnableControl();
		rearRight->EnableControl();

		shoulderStick= new Joystick(0);
		limitswitchtop= new DigitalInput(1);
		limitswitchbottom= new DigitalInput(1);
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
		if(shoulderStick->GetPOV()==0||shoulderStick->GetPOV()==45||shoulderStick->GetPOV()==315 ){
				POV=1;
		}
		else if(shoulderStick->GetPOV()==180||shoulderStick->GetPOV()==135||shoulderStick->GetPOV()==225){
				POV=-1;
		}
		else if(shoulderStick->GetPOV()==-1||shoulderStick->GetPOV()==270||shoulderStick->GetPOV()==90){
				POV=0;
		}
		if(limitswitchtop->Get()){
			if(POV==1){
				POV=0;
			}
		}
		if(limitswitchbottom->Get()){
			if(POV==-1){
				POV=0;
			}
		}
		shoulderMotor->Set((shoulderStick-> GetY())/10);

		Drive->SetSafetyEnabled(false);

		Drive->MecanumDrive_Cartesian(driveStick->GetX(),driveStick->GetY(),driveStick->GetTwist(),0);

		gripper->Set(shoulderStick->GetRawButton(1));

		armExtender->Set(POV);


	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
