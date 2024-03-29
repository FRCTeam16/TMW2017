/*
 * ZeroGyroOffset.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: User
 */

#include <Commands/ZeroGyroOffset.h>

ZeroGyroOffset::ZeroGyroOffset() : Command() {
	SetRunWhenDisabled(true);
}

void ZeroGyroOffset::Initialize() {
	std::cout << "****** Zeroing BSGyro Offset ******\n";
	RobotMap::gyro->SetOffset(0.0);
	SetTimeout(1);
}

void ZeroGyroOffset::Execute() {
}

bool ZeroGyroOffset::IsFinished() {
	return IsTimedOut();
}

void ZeroGyroOffset::End() {
}

void ZeroGyroOffset::Interrupted() {

}
