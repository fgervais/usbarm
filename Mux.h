/*
 * Mux.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "CommandReceiver.h"

#ifndef MUX_H_
#define MUX_H_

class Output;

//todo verify if the interface is correctly implements.. (i'm really not sure)
class Mux {

public:
	Mux();
	void addCommandWriter();
	void receiveCommand();
	void setOutput(Output* output);
	virtual ~Mux();

private:
	Output* output;
};

#endif /* MUX_H_ */
