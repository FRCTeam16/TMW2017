// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"
#include "CANTalon.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

#include "AHRS.h"
#include <Util/BSGyro.h>

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<CANTalon> driveBaseFrontLeftSteer;
	static std::shared_ptr<AnalogInput> driveBaseFrontLeftPos;
	static std::shared_ptr<PIDController> driveBaseFrontLeft;
	static std::shared_ptr<CANTalon> driveBaseFrontRightSteer;
	static std::shared_ptr<AnalogInput> driveBaseFrontRightPos;
	static std::shared_ptr<PIDController> driveBaseFrontRight;
	static std::shared_ptr<CANTalon> driveBaseRearLeftSteer;
	static std::shared_ptr<AnalogInput> driveBaseRearLeftPos;
	static std::shared_ptr<PIDController> driveBaseRearLeft;
	static std::shared_ptr<CANTalon> driveBaseRearRightSteer;
	static std::shared_ptr<AnalogInput> driveBaseRearRightPos;
	static std::shared_ptr<PIDController> driveBaseRearRight;
	static std::shared_ptr<CANTalon> driveBaseFrontLeftDrive;
	static std::shared_ptr<CANTalon> driveBaseFrontRightDrive;
	static std::shared_ptr<CANTalon> driveBaseRearLeftDrive;
	static std::shared_ptr<CANTalon> driveBaseRearRightDrive;
	static std::shared_ptr<PowerDistributionPanel> driveBasePDP;
	static std::shared_ptr<CANTalon> gearSystemGearPickUp;
	static std::shared_ptr<Solenoid> gearSystemLift;
	static std::shared_ptr<Solenoid> gearSystemRotate;
	static std::shared_ptr<Solenoid> gearSystemExtend;
	static std::shared_ptr<DoubleSolenoid> gearSystemSqueeze;
	static std::shared_ptr<Compressor> gearSystemGearCompressor;
	static std::shared_ptr<AnalogInput> gearSystemPressureGauge;
	static std::shared_ptr<CANTalon> climberSystemClimber;
	static std::shared_ptr<DoubleSolenoid> climberSystemProd;
	static std::shared_ptr<CANTalon> shooterSystemElevator;
	static std::shared_ptr<CANTalon> shooterSystemHopper;
	static std::shared_ptr<CANTalon> shooterSystemShooter1;
	static std::shared_ptr<CANTalon> shooterSystemShooter2;
	static std::shared_ptr<CANTalon> ballPickupSystemBallPickup;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<BSGyro> gyro;
	static std::shared_ptr<DigitalOutput> gearUpStatusIndicator;
	static std::shared_ptr<DigitalOutput> indicatorLight;
	static void init();
};
#endif
