/*
 * BSGyro.h
 *
 *  Created on: Feb 27, 2017
 *      Author: User
 */

#ifndef SRC_UTIL_BSGYRO_H_
#define SRC_UTIL_BSGYRO_H_

#include "WPILib.h"
#include "AHRS.h"

class BSGyro : public PIDSource {
private:
	std::unique_ptr<AHRS> ahrs;
	float GetOffset();
public:
	BSGyro(I2C::Port i2c_port_id);
	virtual ~BSGyro();
	float GetYaw();
	double PIDGet();
	AHRS* GetAHRS();
};

#endif /* SRC_UTIL_BSGYRO_H_ */
