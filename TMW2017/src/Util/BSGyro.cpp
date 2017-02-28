/*
 * BSGyro.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: User
 */

#include "BSGyro.h"
#include "AHRS.h"

BSGyro::BSGyro(I2C::Port i2c_port_id) :	AHRS(i2c_port_id) {
	std::cout << "Constructed BSGyro\n";
}


BSGyro::~BSGyro() {
}

float BSGyro::GetOffset() {
	return Preferences::GetInstance()->GetFloat("YawOffset", 0.00);

}

float BSGyro::GetYaw() {
	const float value = GetOffset() + AHRS::GetYaw();
	std::cout << "GetYaw() = " << value << "\n";
	return value;
}

double BSGyro::PIDGet() {
	AHRS* ahrs = this;
	PIDSource* pid = ahrs;
	const float value = GetOffset() + pid->PIDGet();
	std::cout << "PIDGet = " << value << "\n";
	return value;
}

