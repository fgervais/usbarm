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
public:
	Vector();
	virtual ~Vector();

	void addElement(const T& element);
	T& getElement(uint32_t position);
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
	tail = head;
}

template <typename T>
Vector<T>::~Vector() {
	/* Free memory */

}

template <typename T>
void Vector<T>::addElement(const T& element) {
	ListNode<T> node(element,0);

	// Adding the first element
	if(head == 0) {
		head = &node;
	}
	else {
		tail->setNext(&node);
		tail = &node;
	}
	count++;
}

template <typename T>
T& Vector<T>::getElement(uint32_t position) {
	static ListNode<T>* iterator = head;
	static uint32_t iteratorPosition = 0;

	if(position < count) {
		//TODO: Raise an exception?
	}

	if(position < iteratorPosition) {
		// Reset iterator
		iteratorPosition = 0;
		iterator = head;
	}

	// Browse through the linked list
	for(; iteratorPosition<position; iteratorPosition++) {
		iterator = iterator->next();
	}

	// Return a non constant type
	return const_cast<T&>(iterator->getElement());
}

template <typename T>
uint32_t Vector<T>::size() {
	return count;
}

#endif /* VECTOR_H_ */
