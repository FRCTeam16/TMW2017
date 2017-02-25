/*
 * DriveEncoderPIDSource.h
 *
 *  Created on: Jan 28, 2017
 *      Author: User
 */

#ifndef SRC_SUBSYSTEMS_DRIVEENCODERPIDSOURCE_H_
#define SRC_SUBSYSTEMS_DRIVEENCODERPIDSOURCE_H_

#include "WPILib.h"
class CANTalon;

class DriveEncoderPIDSource : public PIDSource {
public:
	DriveEncoderPIDSource(std::shared_ptr<CANTalon> _motor, int *_inverted);
	virtual ~DriveEncoderPIDSource();
	virtual double PIDGet();
	void SetInitialEncoderValue();
private:
	std::shared_ptr<CANTalon> motor;
	int *inverted;
	double initialEncoderValue = 0;
};

#endif /* SRC_SUBSYSTEMS_DRIVEENCODERPIDSOURCE_H_ */
