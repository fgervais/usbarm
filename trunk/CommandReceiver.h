/*
 * CommandReceiver.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#ifndef COMMANDRECEIVER_H_
#define COMMANDRECEIVER_H_

class CommandReceiver {
public:
	CommandReceiver();
	void addCommandWriter();
	void receiveCommand();
	virtual ~CommandReceiver();
};

#endif /* COMMANDRECEIVER_H_ */
