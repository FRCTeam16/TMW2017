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
	AckermannDrive(double _speed, int _distance) : speed(_speed), distance(_distance) {}
	virtual ~AckermannDrive() {}
	bool Run(std::shared_ptr<World> world) override;
private:
	const double speed;
	const int distance;
	double startTime = -1;
	int encoderStartPosition = 0;

};

#endif /* SRC_AUTONOMOUS_STEPS_ACKERMANNDRIVE_H_ */
