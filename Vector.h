/*
 * Vector.h
 *
 *  Created on: Oct 12, 2009
 *      Author: fgervais
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdint.h>
#include "ListNode.h"

template <typename T>
class Vector {
private:
	uint32_t count;
	ListNode<T>* head;
	ListNode<T>* tail;
	uint32_t savedIteratorPosition;
public:
	Vector();
	virtual ~Vector();

	void addElement(const T& element);
	T getElement(uint32_t position);
	uint32_t size();
};

/*
 * Why are the function implementation here ?
 *
 * See : http://www.parashift.com/c++-faq-lite/templates.html
 */

template <typename T>
Vector<T>::Vector() {
	// Basic initialization
	count = 0;
	head = 0;
}

template <typename T>
Vector<T>::~Vector() {
	/* Free memory */

}

template <typename T>
void Vector<T>::addElement(const T& element) {
	// Adding the first element
	if(head == 0) {
		ListNode<T> node(&element,0);
	}
	else {
		ListNode<T> node(&element,0);
		tail->setNext(&node);
		tail = &node;
	}
	count++;
}

template <typename T>
T Vector<T>::getElement(uint32_t position) {
	ListNode<T>* iterator = head;
	// Browse through the linked list
	for(uint32_t i=0; i<position; i++) {
		iterator = iterator->next();
	}

	return iterator->getElement();
}

template <typename T>
uint32_t Vector<T>::size() {
	return count;
}

#endif /* VECTOR_H_ */
