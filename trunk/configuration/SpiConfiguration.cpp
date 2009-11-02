/*
 * SpiConfiguration.cpp
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#include "SpiConfiguration.h"

SpiConfiguration::SpiConfiguration() {
	lineMode 	= 0;
	frameFormat = 0;
	slaveSelect = 0;
	firstBit 	= 0;
	prescaler 	= 0;
	configuration = 0;
	clockPolarity = 0;
	clockPhase 	= 0;
}

SpiConfiguration::~SpiConfiguration() {

}
