/*
 * LEDCommunications.h
 *
 *  Created on: Mar 2, 2017
 *      Author: User
 */

#ifndef SRC_SUBSYSTEMS_LEDCOMMUNICATIONS_H_
#define SRC_SUBSYSTEMS_LEDCOMMUNICATIONS_H_

#include "WPILib.h"
#include "Manager.h"

class LEDCommunications : public Manager {
private:
	std::unique_ptr<I2C> i2c;
	int counter = 0;
	const int scanFrequency = 25;
public:
	LEDCommunications(int portNumber);
	virtual ~LEDCommunications() {}
	virtual void Run() override;
	virtual void SMDB() override;
	virtual void InitManager(const RunMode runMode);
};

#endif /* SRC_SUBSYSTEMS_LEDCOMMUNICATIONS_H_ */
