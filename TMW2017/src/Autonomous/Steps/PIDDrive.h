/*
 * PIDDrive.h
 */

#ifndef SRC_AUTONOMOUS_PIDDRIVE_H_
#define SRC_AUTONOMOUS_PIDDRIVE_H_

#include "../Step.h"


class ZeroDriveEncoders : public Step {
public:
	ZeroDriveEncoders() {}
	~ZeroDriveEncoders() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	bool firstRun = true;
	int lastEncoderPosition;
};

/**
 * Uses encoder counting to drive to a specified target distance
 */
class PIDDrive : public Step {
public:
	PIDDrive(float _angle, float _yspeed, float _xspeed, int _targetDistance) :
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
 * Sets target distance as PID setpoint to drive towards
 */
class PIDControlledDrive : public Step {
public:
	enum Units { kPulses, kInches };
	PIDControlledDrive(double _angle, double _targetDistance, int _threshold, Units _units) :
		angle(_angle), targetDistance(_targetDistance), distanceThreshold(_threshold), units(_units) {}
	bool Run(std::shared_ptr<World> world) override;
private:
	double startTime = -1;
	const double angle;
	const double targetDistance;
	const double distanceThreshold;
	const Units units;
};

#endif /* SRC_AUTONOMOUS_PIDDRIVE_H_ */
