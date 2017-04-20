/*
 * AckermannDrive.h
 *
 *  Created on: Mar 2, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_ACKERMANNDRIVE_H_
#define SRC_AUTONOMOUS_STEPS_ACKERMANNDRIVE_H_

#include "WPILib.h"
#include <Autonomous/Step.h>

class AckermannDrive : public Step {
public:
	AckermannDrive(double _speed, double _targetAngle, double _threshold = 1.0) :
		speed(_speed), targetAngle(_targetAngle), threshold(_threshold) {}
	virtual ~AckermannDrive() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	const double speed;
	const double targetAngle;
	const double threshold;
	double startTime = -1;
	double startAngle;
};


class RedShootOnlyAckermannDrive : public Step {
public:
	RedShootOnlyAckermannDrive(double _speed, double _targetAngle, double _threshold = 1.0) :
		speed(_speed), targetAngle(_targetAngle), threshold(_threshold) {}
	virtual ~RedShootOnlyAckermannDrive() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	const double speed;
	const double targetAngle;
	const double threshold;
	double startTime = -1;
	double startAngle;
};


class AckermannDriveYawDiff : public Step {
public:
	AckermannDriveYawDiff(double _speed, double _targetYawDiff) : speed(_speed), targetYawDiff(_targetYawDiff) {}
	virtual ~AckermannDriveYawDiff() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	const double speed;
	const double targetYawDiff;
	double startTime = -1;
	double startAngle;
};

#endif /* SRC_AUTONOMOUS_STEPS_ACKERMANNDRIVE_H_ */
