/*
 * GamepadReportListener.h
 *
 *  Created on: Nov 18, 2009
 *      Author: fgervais
 */

#ifndef GAMEPADREPORTLISTENER_H_
#define GAMEPADREPORTLISTENER_H_

class Usb;

class GamepadReportListener {
public:
	GamepadReportListener();
	virtual ~GamepadReportListener();

	virtual void gamepadReportReceived(Usb* usb) =0;
};

#endif /* GAMEPADREPORTLISTENER_H_ */
