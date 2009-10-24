/*
 * Mux.h
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "Output.h"
#include "CommandReceiver.h"

#ifndef MUX_H_
#define MUX_H_

//todo verify if the interface is correctly implements.. (i'm really not sure)
class Mux: public CommandReceiver {
private:
	Output* output;
public:


	Mux();
	void addCommandWriter();
	void receiveCommand();
	void setOutput(Output* output);
	virtual ~Mux();
};

#endif /* MUX_H_ */
