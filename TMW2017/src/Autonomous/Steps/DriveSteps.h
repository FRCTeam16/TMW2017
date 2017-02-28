/*
 * PIDDrive.h
 */

#ifndef SRC_AUTONOMOUS_PIDDRIVE_H_
#define SRC_AUTONOMOUS_PIDDRIVE_H_

#include "WPILib.h"
#include <Autonomous/Step.h>
#include <Util/CollisionDetector.h>
#include <Util/BSGyro.h>
#include <RobotMap.h>


class ZeroDriveEncoders : public Step {
public:
	ZeroDriveEncoders() {}
	~ZeroDriveEncoders() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	bool firstRun = true;
	int lastEncoderPosition = 0;
};


class DriveUnit {
public:
	enum Units { kPulses, kInches };
	static double ToPulses(double value, Units units);
	static const std::string PULSES_PER_INCH;
};


/**
 * Uses encoder counting to drive to a specified target distance
 */
class SimpleEncoderDrive : public Step {
public:
	SimpleEncoderDrive(float _angle, float _yspeed, float _xspeed, int _targetDistance) :
		angle(_angle), ySpeed(_yspeed), xSpeed(_xspeed), targetDistance(_targetDistance) {}
	bool Run(std::shared_ptr<World> world) override;
private:
	bool firstRun = true;
	double startTime = -1;
	const float angle;
	const float ySpeed;
	const float xSpeed;
	const float targetDistance;
};


/**
 * Sets target distance as PID setpoint to drive towards.  Distances must be positive
 */
class PIDControlledDrive : public Step {
public:
	PIDControlledDrive(double _angle, double _speed, double _targetDistance,
			int _threshold, DriveUnit::Units _units, bool _reverse = false) :
			angle(_angle), speed(_speed), targetDistance(_targetDistance), distanceThreshold(
					_threshold), units(_units), reverse(_reverse),
					collisionDetector(new CollisionDetector(RobotMap::gyro, 1.0)) {}
	bool Run(std::shared_ptr<World> world) override;
private:
	double startTime = -1;
	const double angle;
	const double speed;
	const double targetDistance;
	const double distanceThreshold;
	const DriveUnit::Units units;
	const bool reverse;
	const std::unique_ptr<CollisionDetector> collisionDetector ;

	double startingEncoderCount = 0;
	double targetSetpoint = 0;
};

class XYPIDControlledDrive : public Step {
public:
	XYPIDControlledDrive(double _angle, double _speed,
			double _XtargetDistance, double _YtargetDistance,
			int _threshold, DriveUnit::Units _units, bool _reverse = false) :
		angle(_angle), speed(_speed), XtargetDistance(_XtargetDistance),
		YtargetDistance(_YtargetDistance), distanceThreshold(_threshold),
		units(_units), reverse(_reverse),
		collisionDetector(new CollisionDetector(RobotMap::gyro, 1.0)) {}
	bool Run(std::shared_ptr<World> world) override;
private:
	double startTime = -1;
	const double angle;
	const double speed;
	const double XtargetDistance;
	const double YtargetDistance;
	const double distanceThreshold;
	const DriveUnit::Units units;
	const bool reverse;
	const std::unique_ptr<CollisionDetector> collisionDetector;

	double startingEncoderCount = 0;
	double targetSetpoint = 0;
};

#endif /* SRC_AUTONOMOUS_PIDDRIVE_H_ */
