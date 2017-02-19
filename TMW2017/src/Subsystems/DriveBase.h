// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVEBASE_H
#define DRIVEBASE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Drive/CrabSpeed.h"

template <typename T>
struct DriveInfo {
	T FL = 0;
	T FR = 0;
	T RL = 0;
	T RR = 0;
};

struct Wheelbase {
	double W = 0;
	double X = 0;
	double Y = 0;
};

class DriveBase: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> frontLeftSteer;
	std::shared_ptr<AnalogInput> frontLeftPos;
	std::shared_ptr<PIDController> frontLeft;
	std::shared_ptr<CANTalon> frontRightSteer;
	std::shared_ptr<AnalogInput> frontRightPos;
	std::shared_ptr<PIDController> frontRight;
	std::shared_ptr<CANTalon> rearLeftSteer;
	std::shared_ptr<AnalogInput> rearLeftPos;
	std::shared_ptr<PIDController> rearLeft;
	std::shared_ptr<CANTalon> rearRightSteer;
	std::shared_ptr<AnalogInput> rearRightPos;
	std::shared_ptr<PIDController> rearRight;
	std::shared_ptr<CANTalon> frontLeftDrive;
	std::shared_ptr<CANTalon> frontRightDrive;
	std::shared_ptr<CANTalon> rearLeftDrive;
	std::shared_ptr<CANTalon> rearRightDrive;
	std::shared_ptr<PowerDistributionPanel> pDP;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	DriveInfo<double> positionOffsets;
	DriveInfo<int> turns;
	DriveInfo<int> inv;
	DriveInfo<int> hotCount;

	double A = 0;					// steer mode
	double thetaRC = 0;
	DriveInfo<double> theta;		// steer mode theta
	DriveInfo<double> steerSpeed;	// steer mode wheel speeds

	int coolCount = 0;
	double driveLimit = 1.0;

	Wheelbase wheelbase;
	std::unique_ptr<PIDController> driveControlTwist;
	std::unique_ptr<CrabSpeed> crabSpeedTwist;
	std::unique_ptr<PIDSource> driveControlEncoderSource;
	std::unique_ptr<PIDController> driveControlSpeedController;
	std::unique_ptr<CrabSpeed> driveControlDistanceSpeed;

	const int MaxTurns = 1000;
	bool driveFront = true;

	void InitializeOffsets();
	void EnableSteerPIDControllers(const bool enable);

	void SetSteering(DriveInfo<double> setpoint);
	void SetSteerSetpoint(double setpoint,
			std::shared_ptr<AnalogInput> actual, double offset,
			std::shared_ptr<PIDController> PIDCon, std::shared_ptr<CANTalon> steer,
			int turns, int &inv);
	double CorrectSteerSetpoint(double setpoint);
	void SetSteerSetpoint(float setpoint, std::shared_ptr<AnalogInput> actual,
			float offset, std::shared_ptr<PIDController> PIDCon,
			std::shared_ptr<CANTalon> steer, int turns, int &inv);
	void SetDriveSpeed(DriveInfo<double> speed);

	void LeftTurn4Wheels();
	void RightTurn4Wheels();

public:
	DriveBase();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	DriveInfo<double> CalculatePositionOffsets();
	void SetPositionOffsets(DriveInfo<double> &info);
	DriveInfo<double> GetPositionOffsets() const;
	void ZeroTurnInfo();
	void ZeroDriveEncoders();

	void InitTeleop();

	void Crab(double twist, double y, double x, bool useGyro);

	void SetTargetAngle(double angle);
	double GetTwistControlOutput();

	void SetTargetDriveDistance(double distance);
	void UseClosedLoopDrive();
	void UseOpenLoopDrive();

	double GetDriveControlEncoderPosition();
	double GetDriveControlOutput();
	double GetDriveControlError();

	std::shared_ptr<CANTalon> GetFrontLeftDrive();

	// Ackerman Steering
	void Steer(float radian, float speed, float a);

};
#endif
