/*
 * AveragingDriveEncoderPIDSource.h
 *
 *  Created on: Mar 26, 2017
 *      Author: User
 */

#ifndef SRC_SUBSYSTEMS_DRIVE_AVERAGINGDRIVEENCODERPIDSOURCE_H_
#define SRC_SUBSYSTEMS_DRIVE_AVERAGINGDRIVEENCODERPIDSOURCE_H_

#include "WPILib.h"
#include <CANTalon.h>
#include "Util/DriveInfo.h"

class CANTalon;

class AveragingDriveEncoderPIDSource : public PIDSource {
public:
	AveragingDriveEncoderPIDSource(DriveInfo<std::shared_ptr<CANTalon>> _motor);
	virtual ~AveragingDriveEncoderPIDSource();
	virtual double PIDGet();
	void SetInitialEncoderValue();
	void SetShowDebug(bool _showDebug);
private:
	DriveInfo<std::shared_ptr<CANTalon>> motor;
	DriveInfo<double> initialEncoderValue;
	double CalculateAverage(const DriveInfo<double> &error, const DriveInfo<bool> &motorEnabled);
	bool showDebug = false;
};

#endif /* SRC_SUBSYSTEMS_DRIVE_AVERAGINGDRIVEENCODERPIDSOURCE_H_ */
