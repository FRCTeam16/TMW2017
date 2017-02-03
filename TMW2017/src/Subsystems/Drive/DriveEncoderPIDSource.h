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
	DriveEncoderPIDSource(std::shared_ptr<CANTalon> _motor);
	virtual ~DriveEncoderPIDSource();
	virtual double PIDGet();
private:
	std::shared_ptr<CANTalon> motor;
};

#endif /* SRC_SUBSYSTEMS_DRIVEENCODERPIDSOURCE_H_ */
