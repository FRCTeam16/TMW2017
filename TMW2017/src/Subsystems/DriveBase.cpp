// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"

#include "DriveBase.h"
#include "../RobotMap.h"
#include "../Util/RAWCConstants.h"
#include "Drive/CrabSpeed.h"
#include "Drive/DriveEncoderPIDSource.h"
#include "AHRS.h"

//#define DEBUG 1

#ifdef DEBUG
#define D(x) x
#define DM(x) (std::cout << x << std::endl)
#else
#define D(x)
#define DM(x)
#endif


using namespace frc;
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveBase::DriveBase() : Subsystem("DriveBase") {
	std::cout << "DriveBase::DriveBase()\n";
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    frontLeftSteer = RobotMap::driveBaseFrontLeftSteer;
    frontLeftPos = RobotMap::driveBaseFrontLeftPos;
    frontLeft = RobotMap::driveBaseFrontLeft;
    frontRightSteer = RobotMap::driveBaseFrontRightSteer;
    frontRightPos = RobotMap::driveBaseFrontRightPos;
    frontRight = RobotMap::driveBaseFrontRight;
    rearLeftSteer = RobotMap::driveBaseRearLeftSteer;
    rearLeftPos = RobotMap::driveBaseRearLeftPos;
    rearLeft = RobotMap::driveBaseRearLeft;
    rearRightSteer = RobotMap::driveBaseRearRightSteer;
    rearRightPos = RobotMap::driveBaseRearRightPos;
    rearRight = RobotMap::driveBaseRearRight;
    frontLeftDrive = RobotMap::driveBaseFrontLeftDrive;
    frontRightDrive = RobotMap::driveBaseFrontRightDrive;
    rearLeftDrive = RobotMap::driveBaseRearLeftDrive;
    rearRightDrive = RobotMap::driveBaseRearRightDrive;
    pDP = RobotMap::driveBasePDP;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    crabSpeedTwist.reset(new CrabSpeed());

    InitializeOffsets();

    wheelbase.W = 23.5/2;
    wheelbase.X = 27.5;
    wheelbase.Y = 23.5/2;

    // Enable Controllers
	std::vector<std::shared_ptr<PIDController>> controllers = {
			frontLeft, frontRight, rearLeft, rearRight };
	std::for_each(controllers.begin(), controllers.end(),
			[](std::shared_ptr<PIDController> &controller) {
		controller->Enable();
	});

	// Initialize Drive Control Twist
    driveControlTwist.reset(
    		new PIDController(0.01, 0.0, 0.05,
    				RobotMap::gyro.get(), crabSpeedTwist.get(), 0.02 ));
    driveControlTwist->SetContinuous(true);
    driveControlTwist->SetAbsoluteTolerance(2.0);
    driveControlTwist->Enable();
    driveControlTwist->SetOutputRange(-0.5, 0.5);
    driveControlTwist->SetInputRange(-180, 180);

    // Initialize Steering
    const std::vector<std::shared_ptr<CANTalon>> steering {
    	frontLeftSteer, frontRightSteer, rearLeftSteer, rearRightSteer };
    std::for_each(steering.begin(), steering.end(),
    		[](std::shared_ptr<CANTalon> steer) {
    	steer->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    });

    // Initialize Drive Talons + PID feedback
    Preferences *prefs = Preferences::GetInstance();
    const double driveP = prefs->GetFloat("DriveP");
    const double driveI = prefs->GetFloat("DriveI");
    const double driveD = prefs->GetFloat("DriveD");
    const double driveF = prefs->GetFloat("DriveF");
    const double driveIZone = prefs->GetFloat("DriveIZone");

	const std::vector<std::shared_ptr<CANTalon>> drives {
		frontLeftDrive, frontRightDrive, rearLeftDrive, rearRightDrive};
	std::for_each(drives.begin(), drives.end(),
			[&](std::shared_ptr<CANTalon> drive) {
		drive->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
		drive->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		drive->SetControlMode(CANSpeedController::kSpeed);
		drive->ConfigEncoderCodesPerRev(3);
		drive->SetP(driveP);
		drive->SetI(driveI);
		drive->SetD(driveD);
		drive->SetF(driveF);
		drive->SetIzone(driveIZone);
	});

	// Drive PID Control
	const double driveControlP = prefs->GetFloat("DriveControlP");
	const double driveControlI = prefs->GetFloat("DriveControlI");
	const double driveControlD = prefs->GetFloat("DriveControlD");
	const double driveControlF = prefs->GetFloat("DriveControlF");
	const double driveControlIZone = prefs->GetFloat("DriveControlIZone");
	driveControlEncoderSource.reset(new DriveEncoderPIDSource(frontRightDrive, &inv.FR));
	driveControlDistanceSpeed.reset(new CrabSpeed());
	driveControlSpeedController.reset(
			new PIDController(driveControlP, driveControlI, driveControlD, driveControlF,
					driveControlEncoderSource.get(),
					driveControlDistanceSpeed.get()));
	driveControlSpeedController->Enable();
	std::cout << "DriveBase::DriveBase() Finished\n";
}

void DriveBase::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveBase::InitializeOffsets() {
	RAWCConstants *constantsFile = RAWCConstants::getInstance();
	positionOffsets.FL = constantsFile->getValueForKey("FLOff");
	positionOffsets.FR = constantsFile->getValueForKey("FROff");
	positionOffsets.RL = constantsFile->getValueForKey("RLOff");
	positionOffsets.RR = constantsFile->getValueForKey("RROff");
	std::cout << "DriveBase initialized offsets\n";
}

void DriveBase::Lock() {
	DriveInfo<double> steering;
	steering.FL = 2.5;
	steering.FR = 0.75;
	steering.RL = 3.25;
	steering.RR = 4.5;
	SetSteering(steering);

	DriveInfo<double> lockSpeed;
	SetDriveSpeed(lockSpeed);
}

DriveInfo<double> DriveBase::CalculatePositionOffsets() {
	auto offsetCalculator = [&](const std::shared_ptr<AnalogInput> &position) {
		return position->GetAverageVoltage() - 2.5;
	};
	positionOffsets.FL = offsetCalculator(frontLeftPos);
	positionOffsets.FR = offsetCalculator(frontRightPos);
	positionOffsets.RL = offsetCalculator(rearLeftPos);
	positionOffsets.RR = offsetCalculator(rearRightPos);
	return GetPositionOffsets();
}

void DriveBase::SetPositionOffsets(DriveInfo<double> &info) {
	positionOffsets = info;
}

DriveInfo<double> DriveBase::GetPositionOffsets() const {
	return positionOffsets;
}

void DriveBase::ZeroTurnInfo() {
	turns.FL = 0;
	turns.FR = 0;
	turns.RL = 0;
	turns.RR = 0;
}

void DriveBase::ZeroDriveEncoders() {
	const std::vector<std::shared_ptr<CANTalon>> drives {frontLeftDrive, frontRightDrive, rearLeftDrive, rearRightDrive};
	std::for_each(drives.begin(), drives.end(),
			[](std::shared_ptr<CANTalon> motor) {
		motor->SetPosition(0);
	});
}

void DriveBase::InitTeleop() {
	this->EnableSteerPIDControllers(true);
	this->UseOpenLoopDrive();
	Preferences *prefs = Preferences::GetInstance();
	driveControlTwist->SetPID(
			prefs->GetFloat("TwistP", 0.02),
			prefs->GetFloat("TwistI", 0.0),
			prefs->GetFloat("TwistD", 0.12));
	driveControlTwist->SetOutputRange(-0.5, 0.5);
}

void DriveBase::EnableSteerPIDControllers(const bool enable) {
	std::cout << "DriveBase::EnableSteerPIDControllers(" << enable << ")\n";
	std::vector<std::shared_ptr<PIDController>> controllers = { frontLeft,
			frontRight, rearLeft, rearRight };
	if (enable) {
		std::for_each(controllers.begin(), controllers.end(),
				[](std::shared_ptr<PIDController> &pid) {pid->Enable();});
	} else {
		std::for_each(controllers.begin(), controllers.end(),
				[](std::shared_ptr<PIDController> &pid) {pid->Disable();});
	}
}

void DriveBase::UseOpenLoopDrive() {
	const std::vector<std::shared_ptr<CANTalon>> drives { frontLeftDrive,
			frontRightDrive, rearLeftDrive, rearRightDrive };
	std::for_each(drives.begin(), drives.end(),
			[](std::shared_ptr<CANTalon> motor) {
				motor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
			});
}

void DriveBase::UseClosedLoopDrive() {
	const std::vector<std::shared_ptr<CANTalon>> drives { frontLeftDrive,
				frontRightDrive, rearLeftDrive, rearRightDrive };
	std::for_each(drives.begin(), drives.end(),
			[](std::shared_ptr<CANTalon> motor) {
				motor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
			});
}

void DriveBase::Crab(double twist, double y, double x, bool useGyro) {
	float FWD = y;
	float STR = x;

	if (useGyro) {
		const double robotangle = RobotMap::gyro->GetYaw() * M_PI / 180;
		FWD =  y * cos(robotangle) + x * sin(robotangle);
		STR = -y * sin(robotangle) + x * cos(robotangle);
	}

	const double radius = sqrt(pow(2*wheelbase.Y, 2) + pow(wheelbase.X,2));
	double AP = STR - twist * wheelbase.X / radius;
	double BP = STR + twist * wheelbase.X / radius;
	double CP = FWD - twist * 2 * wheelbase.Y / radius;
	double DP = FWD + twist * 2 * wheelbase.Y / radius;

	DriveInfo<double> setpoint;
	setpoint.FL = 2.5;
	setpoint.FR = 2.5;
	setpoint.RL = 2.5;
	setpoint.RR = 2.5;

	if (DP != 0 || BP != 0) {
		setpoint.FL = (2.5 + 2.5 / M_PI * atan2(BP, DP));
	}
	if (BP != 0 || CP != 0) {
		setpoint.FR = (2.5 + 2.5 / M_PI * atan2(BP, CP));
	}
	if (AP != 0 || DP != 0) {
		setpoint.RL = (2.5 + 2.5 / M_PI * atan2(AP, DP));
	}
	if (AP != 0 || CP != 0) {
		setpoint.RR = (2.5 + 2.5 / M_PI * atan2(AP, CP));
	}

	SetSteering(setpoint);


	DriveInfo<double> speed;
	speed.FL = sqrt(pow(BP, 2) + pow(DP, 2));
	speed.FR = sqrt(pow(BP, 2) + pow(CP, 2));
	speed.RL = sqrt(pow(AP, 2) + pow(DP, 2));
	speed.RR = sqrt(pow(AP, 2) + pow(CP, 2));

	double speedarray[] = {fabs(speed.FL), fabs(speed.FR), fabs(speed.RL), fabs(speed.RR)};
	const double maxspeed = *std::max_element(speedarray, speedarray+4);

	DriveInfo<double> ratio;
	if (maxspeed > 1 || maxspeed < -1) {
		ratio.FL = speed.FL / maxspeed;
		ratio.FR = speed.FR / maxspeed;
		ratio.RL = speed.RL / maxspeed;
		ratio.RR = speed.RR / maxspeed;
	} else {
		ratio.FL = speed.FL;
		ratio.FR = speed.FR;
		ratio.RL = speed.RL;
		ratio.RR = speed.RR;
	}
	ratio.FR = -ratio.FR;
	ratio.RR = -ratio.RR;
	SetDriveSpeed(ratio);
}

void DriveBase::SetSteering(DriveInfo<double> setpoint) {
	if (driveFront) {
		DM("FL");
		SetSteerSetpoint(setpoint.FL, frontLeftPos,
						positionOffsets.FL, frontLeft, frontLeftSteer,
						turns.FL, inv.FL);
		DM("FR");
		SetSteerSetpoint(setpoint.FR, frontRightPos,
						positionOffsets.FR, frontRight, frontRightSteer,
						turns.FR, inv.FR);
		DM("RL");
		SetSteerSetpoint(setpoint.RL, rearLeftPos,
						positionOffsets.RL, rearLeft, rearLeftSteer,
						turns.RL, inv.RL);
		DM("RR");
		SetSteerSetpoint(setpoint.RR, rearRightPos,
						positionOffsets.RR, rearRight, rearRightSteer,
						turns.RR, inv.RR);
	} else {
		SetSteerSetpoint(setpoint.RR, frontLeftPos,
						positionOffsets.FL, frontLeft, frontLeftSteer,
						turns.FL, inv.FL);
		SetSteerSetpoint(setpoint.RL, frontRightPos,
						positionOffsets.FR, frontRight, frontRightSteer,
						turns.FR, inv.FR);
		SetSteerSetpoint(setpoint.FR, rearLeftPos,
						positionOffsets.RL, rearLeft, rearLeftSteer,
						turns.RL, inv.RL);
		SetSteerSetpoint(setpoint.FL, rearRightPos,
						positionOffsets.RR, rearRight, rearRightSteer,
						turns.RR, inv.RR);
	}
}

void DriveBase::SetSteerSetpoint(double setpoint,
		std::shared_ptr<AnalogInput> actual, double offset,
		std::shared_ptr<PIDController> PIDCon, std::shared_ptr<CANTalon> steer,
		int turns, int &inv) {
	const double volt = actual->GetVoltage();

	if (turns >= MaxTurns) {
		PIDCon->Disable();
		steer->Set(-1);
	} else if (turns <= -MaxTurns) {
		PIDCon->Disable();
		steer->Set(1);
	} else if (fabs(CorrectSteerSetpoint(setpoint + offset) - volt) < 1.25
			|| fabs(CorrectSteerSetpoint(setpoint + offset) - volt) > 3.75) {
		PIDCon->Enable();
		if ((turns + 1 == MaxTurns
				&& CorrectSteerSetpoint(volt - offset) - CorrectSteerSetpoint(setpoint) > 2.5)
				|| (turns - 1 == -MaxTurns
						&& CorrectSteerSetpoint(volt - offset) - CorrectSteerSetpoint(setpoint) < -2.5)) {
			PIDCon->SetSetpoint(CorrectSteerSetpoint(setpoint + offset - 2.5));
			inv = -1;
			D(std::cout << "SetSteer Inv #1 = -1" << std::endl;)
		} else {
			PIDCon->SetSetpoint(CorrectSteerSetpoint(setpoint + offset));
			inv = 1;
			D(std::cout << "SetSteer Inv #2 = 1" << std::endl;)
		}
	} else {
		PIDCon->Enable();
		if ((turns + 1 == MaxTurns
				&& CorrectSteerSetpoint(volt - offset) - CorrectSteerSetpoint(setpoint - 2.5) > 2.5)
				|| (turns - 1 == -MaxTurns
						&& CorrectSteerSetpoint(volt - offset) - CorrectSteerSetpoint(setpoint - 2.5) < -2.5)) {
			PIDCon->SetSetpoint(CorrectSteerSetpoint(setpoint + offset));
			inv = 1;
			D(std::cout << "SetSteer Inv #3 = 1" << std::endl;)
		} else {
			PIDCon->SetSetpoint(CorrectSteerSetpoint(setpoint + offset - 2.5));
			D(std::cout << "SetSteer Inv #4 = -1" << std::endl;)
			inv = -1;
		}
	}
}

double DriveBase::CorrectSteerSetpoint(double setpoint) {
	//Used to correct steering setpoints to within the 0 to 5 V scale
	if (setpoint < 0) {
		return setpoint + 5;
	} else if (setpoint > 5) {
		return setpoint - 5;
	} else if (setpoint == 5) {
		return 0;
	} else {
		return setpoint;
	}
}


void DriveBase::SetDriveSpeed(DriveInfo<double> speed) {
	const float driveOutLimit = 50;
	const int hotCountLimit = 100;
	const int coolCountLimit = 1000;

	frontLeftDrive->GetOutputCurrent() > driveOutLimit ? hotCount.FL++ : hotCount.FL =0;
	frontRightDrive->GetOutputCurrent() > driveOutLimit ? hotCount.FR++ : hotCount.FR =0;
	rearLeftDrive->GetOutputCurrent() > driveOutLimit ? hotCount.RL++ : hotCount.RL =0;
	rearRightDrive->GetOutputCurrent() > driveOutLimit ? hotCount.RR++ : hotCount.RR =0;

	if (hotCount.FL == 0 && hotCount.FR == 0 && hotCount.RL == 0 && hotCount.RR == 0 ) {
		coolCount++;
	} else {
		coolCount = 0;
	}

	if (hotCount.FL > hotCountLimit && hotCount.FR > hotCountLimit &&
			hotCount.RL > hotCountLimit  && hotCount.RR > hotCountLimit) {
		driveLimit = 0.5;
	}

	if (coolCount > coolCountLimit) {
		driveLimit = 1.0;
	}

	// Check one of our drives to see if the mode is open or closed loop
	// FIXME: RPM Scale factor needs to be in preferences
	const float SCALE_FACTOR =
			(CANSpeedController::ControlMode::kPercentVbus == frontLeftDrive->GetControlMode()) ?
					1 : 13000;
	if(driveFront) {
		frontLeftDrive-> Set(speed.FL * inv.FL * SCALE_FACTOR);
		frontRightDrive->Set(speed.FR * inv.FR * SCALE_FACTOR);
		rearLeftDrive->  Set(speed.RL * inv.RL * SCALE_FACTOR);
		rearRightDrive-> Set(speed.RR * inv.RR * SCALE_FACTOR);
	}
	else {
		frontLeftDrive-> Set(speed.RR * inv.FL * SCALE_FACTOR);
		frontRightDrive->Set(speed.RL * inv.FR * SCALE_FACTOR);
		rearLeftDrive->  Set(speed.FR * inv.RL * SCALE_FACTOR);
		rearRightDrive-> Set(speed.FL * inv.RR * SCALE_FACTOR);
	}
}

void DriveBase::Steer(float radian, float speed, float a) {
	std::cout << "Radian:" << radian << "|| Speed:" << speed << std::endl;

	A=a;

	thetaRC = M_PI - radian;  //convert steering angle to rear center wheel angle
	DriveInfo<double> steerRatio;

	if(thetaRC != M_PI / 2)	//If we are not driving straight forward...
	{
		if(thetaRC < M_PI / 2)	//Right Turn
		{
			RightTurn4Wheels();
		}
		else if(thetaRC > M_PI / 2)	//Left Turn
		{
			LeftTurn4Wheels();
		}
	}
	else	//thetaRC = M_PI / 2
	{
		theta.FL = M_PI / 2;
		theta.FR = M_PI / 2;
		theta.RL = M_PI / 2;
		theta.RR = M_PI / 2;

		steerRatio.FL = 1;
		steerRatio.FR = 1;
		steerRatio.RL = 1;
		steerRatio.RR = 1;
	}
	//Solve for fastest wheel speed
	double speedarray[] = {fabs(steerSpeed.FL), fabs(steerSpeed.FR), fabs(steerSpeed.RL), fabs(steerSpeed.RR)};

	 int length = 4;
     double maxspeed = speedarray[0];
     for(int i = 1; i < length; i++)
     {
          if(speedarray[i] > maxspeed)
                maxspeed = speedarray[i];
     }

	//Set ratios based on maximum wheel speed
	steerRatio.FL = steerSpeed.FL/maxspeed;
	steerRatio.FR = steerSpeed.FR/maxspeed;
	steerRatio.RL = steerSpeed.RL/maxspeed;
	steerRatio.RR = steerSpeed.RR/maxspeed;

	//Set drive speeds
	steerRatio.FL = -steerRatio.FL * speed;
	steerRatio.FR = steerRatio.FR * speed;
	steerRatio.RL = -steerRatio.RL * speed;
	steerRatio.RR = steerRatio.RR * speed;
	SetDriveSpeed(steerRatio);

	//Set Steering PID Setpoints
	DriveInfo<double> setPoint;
	setPoint.FL = (1.25 + 2.5/M_PI*theta.FL);
	setPoint.FR = (1.25 + 2.5/M_PI*theta.FR);
	setPoint.RL = (1.25 + 2.5/M_PI*theta.RL);
	setPoint.RR = (1.25 + 2.5/M_PI*theta.RR);

	SetSteering(setPoint);
}

void DriveBase::LeftTurn4Wheels()
{
	const double Z = ((A * wheelbase.X) * tan(M_PI - thetaRC));				//find turning radius

	//calculate angles based on turning radius
	theta.RL = M_PI - atan((Z - wheelbase.W) / (A * wheelbase.X));
	theta.RR = M_PI - atan((Z + wheelbase.W) / (A * wheelbase.X));
	theta.FR = M_PI / 2;
	theta.FL = M_PI / 2;

	if(A != 1) //not turning about front wheels
	{
		theta.FL = atan((Z - wheelbase.Y) / ((1 - A) * wheelbase.X));	//These are identical for right and left turns
		theta.FR = atan((Z + wheelbase.Y) / ((1 - A) * wheelbase.X));	//These are identical for right and left turns
	}
	//Solve each wheel turning radii (wheel speed)
	steerSpeed.FL = (Z - wheelbase.Y) / sin(theta.FL);
	steerSpeed.FR = (Z + wheelbase.Y) / sin(theta.FR);
	steerSpeed.RL = (Z - wheelbase.W) / sin(M_PI - theta.RL);
	steerSpeed.RR = (Z + wheelbase.W) / sin(M_PI - theta.RR);
}

void DriveBase::RightTurn4Wheels()
{
	const double Z = ((A * wheelbase.X) * tan(thetaRC));				//find turning radius

	//calculate angles based on turning radius
	theta.RL = atan((Z + wheelbase.W) / (A * wheelbase.X));
	theta.RR = atan((Z - wheelbase.W) / (A * wheelbase.X));
	theta.FR = M_PI / 2;
	theta.FL = M_PI / 2;


	if(A != 1)  //not turning about front wheels
	{
		theta.FR = M_PI - atan((Z - wheelbase.Y) / ((1 - A) * wheelbase.X));	//These are identical for right and left turns
		theta.FL = M_PI - atan((Z + wheelbase.Y) / ((1 - A) * wheelbase.X));	//These are identical for right and left turns
	}

	//Solve each wheel turning radii (wheel speed)
	steerSpeed.FL = (Z + wheelbase.Y) / sin(M_PI - theta.FL);
	steerSpeed.FR = (Z - wheelbase.Y) / sin(M_PI - theta.FR);
	steerSpeed.RL = (Z + wheelbase.W) / sin(theta.RL);
	steerSpeed.RR = (Z - wheelbase.W) / sin(theta.RR);
}




void DriveBase::SetTargetAngle(double angle) {
	driveControlTwist->SetSetpoint(angle);
}

double DriveBase::GetTwistControlOutput() {
	return driveControlTwist->Get();
}

double DriveBase::GetTwistControlError() {
	return driveControlTwist->GetError();
}

void DriveBase::SetTargetDriveDistance(double distance, double maxSpeed) {
	driveControlSpeedController->SetSetpoint(distance);
	driveControlEncoderSource->SetInitialEncoderValue();
	driveControlSpeedController->SetOutputRange(-maxSpeed, maxSpeed);
}

double DriveBase::GetDriveControlEncoderPosition() {
	return driveControlEncoderSource->PIDGet();
}

double DriveBase::GetDriveControlOutput() {
	return driveControlDistanceSpeed->Get();
}

double DriveBase::GetDriveControlError() {
	return driveControlSpeedController->GetError();
}

std::shared_ptr<CANTalon> DriveBase::GetFrontLeftDrive() {
	return frontLeftDrive;
}

std::shared_ptr<CANTalon> DriveBase::GetRearRightDrive() {
	return rearRightDrive;
}


