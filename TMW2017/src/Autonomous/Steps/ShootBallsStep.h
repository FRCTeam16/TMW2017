/*
 * ShootBallsStep.h
 *
 *  Created on: Feb 20, 2017
 *      Author: User
 */

#ifndef SRC_AUTONOMOUS_STEPS_SHOOTBALLSSTEP_H_
#define SRC_AUTONOMOUS_STEPS_SHOOTBALLSSTEP_H_


#include <Autonomous/Step.h>

class ShootBallsStep : public Step {
private:
	double startTime = -1;
	const double timeToShoot;
	bool waitingForShooterMotors = true;
	double beginShootingTime = -1;
public:
	ShootBallsStep(double _timeToShoot) :
		startTime(-1), timeToShoot(_timeToShoot) {}
	~ShootBallsStep() {}
	bool Run(std::shared_ptr<World> world) override;
};

#endif /* SRC_AUTONOMOUS_STEPS_SHOOTBALLSSTEP_H_ */
