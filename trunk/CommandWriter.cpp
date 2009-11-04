/*
 * CommandWriter.cpp
 *
 *  Created on: 2009-09-29
 *      Author: oex
 */

#include "CommandWriter.h"

void CommandWriter::setOutput(CommandReceiver *output) {
	this->output = output;
}

void CommandWriter::write(Command *command) {

}

CommandWriter::CommandWriter(CommandReceiver *output) {


}

CommandWriter::~CommandWriter() {

}
