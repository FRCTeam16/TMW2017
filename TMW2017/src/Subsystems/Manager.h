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
	virtual ~Manager() {};
	virtual void Run() = 0;
	virtual void SMDB() {}
	virtual void InitManager() = 0;
};



#endif /* SRC_SUBSYSTEMS_MANAGER_H_ */
