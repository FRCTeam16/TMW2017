/*
 * BSGyro.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: User
 */

#include "BSGyro.h"
#include "AHRS.h"

BSGyro::BSGyro(I2C::Port i2c_port_id) :	ahrs(new AHRS(i2c_port_id)) {
	std::cout << "Constructed BSGyro\n";
}

BSGyro::~BSGyro() {
}

float BSGyro::GetOffset() {
	return offset;
}

void BSGyro::SetOffset(float _offset) {
	frc::SmartDashboard::PutNumber("BSGyro Set Offset", _offset);
	offset = _offset;
}

float BSGyro::GetYaw() {
	return GetOffset() + ahrs->GetYaw();
}

double BSGyro::PIDGet() {
	return GetYaw();
}

AHRS* BSGyro::GetAHRS() {
	return ahrs.get();
}

