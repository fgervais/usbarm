/*
 * UsbEventListener.h
 *
 *  Created on: Nov 5, 2009
 *      Author: fgervais
 */

#ifndef USBEVENTLISTENER_H_
#define USBEVENTLISTENER_H_

class Usb;

class UsbEventListener {
public:
	UsbEventListener();
	virtual ~UsbEventListener();
	virtual void reportReceived(Usb* usb) = 0;
};

#endif /* USBEVENTLISTENER_H_ */
