/*
 * AveragingDriveEncoderPIDSource.h
 *
 *  Created on: Mar 26, 2017
 *      Author: User
 */

#ifndef SRC_SUBSYSTEMS_DRIVE_AVERAGINGDRIVEENCODERPIDSOURCE_H_
#define SRC_SUBSYSTEMS_DRIVE_AVERAGINGDRIVEENCODERPIDSOURCE_H_

#include "WPILib.h"
#include <Subsystems/DriveBase.h>
class CANTalon;

class AveragingDriveEncoderPIDSource : public PIDSource {
public:
	AveragingDriveEncoderPIDSource(DriveInfo<std::shared_ptr<CANTalon>> _motor);
	virtual ~AveragingDriveEncoderPIDSource();
	virtual double PIDGet();
	void SetInitialEncoderValue();
private:
	DriveInfo<std::shared_ptr<CANTalon>> motor;
	DriveInfo<double> initialEncoderValue;
	DriveInfo<bool> motorEnabled {true};
};

#endif /* SRC_SUBSYSTEMS_DRIVE_AVERAGINGDRIVEENCODERPIDSOURCE_H_ */
