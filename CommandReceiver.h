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
	virtual void addCommandWriter() = 0;
	virtual void receiveCommand() = 0;
	virtual ~CommandReceiver() = 0;
};

#endif /* COMMANDRECEIVER_H_ */
