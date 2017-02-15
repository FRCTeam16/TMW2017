/*
 * Manager.h
 *
 *  Created on: Feb 4, 2017
 *      Author: User
 */

#ifndef SRC_SUBSYSTEMS_MANAGER_H_
#define SRC_SUBSYSTEMS_MANAGER_H_

class Manager {
public:
	enum RunMode { kAuto, kTele };

	virtual ~Manager() {};
	virtual void Run() = 0;
	virtual void SMDB() {}
	virtual void InitManager(const RunMode runMode) = 0;

};



#endif /* SRC_SUBSYSTEMS_MANAGER_H_ */
