/*
 * ListNode.h
 *
 *  Created on: Oct 12, 2009
 *      Author: fgervais
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

template <typename T>
class ListNode {
private:
	T* element;
	ListNode<T>* nextNode;
public:
	ListNode(T* element, ListNode* next);
	virtual ~ListNode();

	T* next();
	void setNext(ListNode* next);
	T* getElement();
};

/*
 * Why are the function implementation here ?
 *
 * See : http://www.parashift.com/c++-faq-lite/templates.html
 */

template <typename T>
T* ListNode<T>::next() {
	return nextNode;
}

template <typename T>
void ListNode<T>::setNext(ListNode* next) {
	this->nextNode = next;
}

template <typename T>
T* ListNode<T>::getElement() {
	return element;
}

#endif /* LISTNODE_H_ */
