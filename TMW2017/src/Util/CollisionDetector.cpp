/*
 * CollisionDetector.cpp
 */

#include "CollisionDetector.h"
#include <iostream>

CollisionDetector::CollisionDetector(std::shared_ptr<BSGyro> imu_, double threshold_ ) :
	imu(imu_), threshold(threshold_) {
}

CollisionDetector::~CollisionDetector() {
}

bool CollisionDetector::Detect() {
	// @see http://www.pdocs.kauailabs.com/navx-mxp/examples/collision-detection/
	double current_accel_x = imu->GetAHRS()->GetWorldLinearAccelX();
	double current_jerk_x = current_accel_x - last_accel_x;
	last_accel_x = current_accel_x;

	double current_accel_y = imu->GetAHRS()->GetWorldLinearAccelY();
	double current_jerk_y = current_accel_y - last_accel_y;
	last_accel_y = current_accel_y;

//	std::cout << "CollisionDetector jerk: x->" << current_jerk_x
//			  << " y-> " << current_jerk_y << "\n";

	frc::SmartDashboard::PutNumber("Current Jerk X", current_jerk_x);
	frc::SmartDashboard::PutNumber("Current Jerk Y", current_jerk_y);

	return ((fabs(current_jerk_x) > threshold) ||
			(fabs(current_jerk_y) > threshold));
}


