/*
 * LEDCommunications.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: User
 */

#include <Subsystems/LEDCommunications.h>
#include "RobotMap.h"
#include "Robot.h"

static float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


LEDCommunications::LEDCommunications(int portNumber) {
	i2c.reset(new I2C(frc::I2C::Port::kOnboard, portNumber));
}

void LEDCommunications::Run() {
	if ((++counter %= scanFrequency) != 0) {
		return;
	}

	// http://wpilib.screenstepslive.com/s/3120/m/7912/l/175524-sending-data-from-the-crio-to-an-arduino
	// https://www.chiefdelphi.com/forums/showthread.php?t=132572
	// 4x wheel speed
	// 4x wheel amps
	// 1 gear captured?
	// 1 time remaining

	const double maxSpeed = 13000;
	const double maxCurrent = 12;

	const int DATA_SIZE = 10;
	uint8_t data[10];
	int i = 0;
	data[i++] = map(abs(RobotMap::driveBaseFrontLeftDrive->GetSpeed()), 0, maxSpeed, 0, 255);
	data[i++] = map(abs(RobotMap::driveBaseFrontRightDrive->GetSpeed()), 0, maxSpeed, 0, 255);
	data[i++] = map(abs(RobotMap::driveBaseRearLeftDrive->GetSpeed()), 0, maxSpeed, 0, 255);
	data[i++] = map(abs(RobotMap::driveBaseRearLeftDrive->GetSpeed()), 0, maxSpeed, 0, 255);

	data[i++] = map(RobotMap::driveBaseFrontLeftDrive->GetOutputCurrent(), 0, maxCurrent, 0, 255);
	data[i++] = map(RobotMap::driveBaseFrontRightDrive->GetOutputCurrent(), 0, maxCurrent, 0, 255);
	data[i++] = map(RobotMap::driveBaseRearLeftDrive->GetOutputCurrent(), 0, maxCurrent, 0, 255);
	data[i++] = map(RobotMap::driveBaseRearLeftDrive->GetOutputCurrent(), 0, maxCurrent, 0, 255);

	data[i++] = map((float)Robot::gearSystem->HasGear(), 0, 1, 0, 255);
	const double maxTime = DriverStation::GetInstance().IsAutonomous() ? 15 : 135;
	data[i++] = map(DriverStation::GetInstance().GetMatchTime(), maxTime, 0, 255, 0);

	// Debug
	for (int i=0; i < DATA_SIZE; i++) {
		std::cout << "data[" << i << "] = " << data[i] << "\n";
	}

	i2c->Transaction(data, 10, nullptr, 0);
}

void LEDCommunications::SMDB() {

}

void LEDCommunications::InitManager(const RunMode runMode) {

}
