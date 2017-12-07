/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};


template<class ItemType>
class LinkedStack {
private:
	L1Item<ItemType>* _pTop;
	int _count;
public:
	void Clear();
	LinkedStack() :_pTop(NULL), _count(0) {}
	~LinkedStack() { this->Clear(); }
	void Push(ItemType &data);
	int Pop(ItemType &data);
	int Pop();
	int GetTop(ItemType &data);
	L1Item<ItemType>* GetTop() { return this->_pTop; }

	bool isEmpty() { return (_count == 0 && _pTop == NULL); }
	bool isFull();
	int GetCount() { return _count; }

};

template<class ItemType>
bool LinkedStack<ItemType>::isFull() {
	L1Item<ItemType> *pNew = new L1Item<ItemType>();
	if (pNew) {
		delete pNew; pNew = NULL;
		return false;
	}
	return true;
}


template<class ItemType>
void LinkedStack<ItemType>::Clear() {
	L1Item<ItemType> * pRun = new L1Item<ItemType>();
	while (this->_pTop) {
		pRun = this->_pTop;
		this->_pTop = this->_pTop->pNext;
		delete pRun; pRun = NULL;
	}
	this->_count = 0;
}

template<class ItemType>
void LinkedStack<ItemType>::Push(ItemType &data) {
	if (this->isFull()) return;

	L1Item<ItemType> *pNew = new L1Item<ItemType>(data);
	pNew->pNext = this->_pTop;
	this->_pTop = pNew;
	this->_count++;
}

template<class ItemType>
int LinkedStack<ItemType>::Pop(ItemType &data) {

	if (this->GetCount() == 0)
		return 0;
	data = this->_pTop->data;
	L1Item<ItemType> *pNew = this->_pTop;
	this->_pTop = this->_pTop->pNext;
	delete pNew; pNew = NULL;
	this->_count--;
	return 1;
}

template<class ItemType>
int LinkedStack<ItemType>::Pop() {
	if (this->_count == 0) return 0;
	L1Item<ItemType> *pNew = this->_pTop;
	this->_pTop = this->_pTop->pNext;
	delete pNew; pNew = NULL;
	this->_count--;
	return 1;
}

template<class ItemType>
int LinkedStack<ItemType>::GetTop(ItemType &data) {
	if (this->_count == 0) return 0;
	data = this->_pTop->data;
	return 1;
}



template <class T>
class L1List {
	L1Item<T>   *_pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() {
		this->clean();
	}

	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	L1Item<T>* getHead() {
		return this->_pHead;
	}

	void setHead(L1Item<T> *p) {
		this->_pHead = p;
	}

	void downSize() {
		this->_size--;
	}

	T&      at(int i) {}
	T&      operator[](int i);

	bool    find(T& a, int& idx) {}
	int     insert(int i, T& a) {}
	int     remove(int i) {}

	int     push_back(T& a);
	int     insertHead(T& a);

	int     removeHead();
	int     removeLast();

	void    reverse(L1Item<T> *&pHead);
	void Reverse() {
		this->reverse(this->_pHead);
	}

	void _reverse(L1Item<T> *&pHead);
	void _Reverse() {
		this->_reverse(this->_pHead);
	}

	void    traverse(void(*op)(T&)) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, void*), void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}
};

template<class T>
void L1List<T>::_reverse(L1Item<T> *&pHead)
{
	L1Item<T> *current = pHead;
	L1Item<T>* next = new L1Item<T>();
	L1Item<T>* prev = new L1Item<T>();
	/*reverse first k nodes of the linked list */
	while (current != NULL)
	{
		next = current->pNext;
		current->pNext = prev;
		prev = current;
		current = next;
	}
	/* next is now a pointer to (k+1)th node
	Recursively call for the list starting from current.
	And make rest of the list as next of first node */
	if (next != NULL)
		pHead = prev;
	/* prev is new head of the input list */
}



/// My code
template <class ItemType>
void L1List<ItemType>::reverse(L1Item<ItemType> *&pHead) {

	if (pHead == NULL) return;

	LinkedStack<ItemType> sNew;
	L1Item<ItemType> *nNew = pHead;
	while (nNew) {
		sNew.Push(nNew->data);
		nNew = nNew->pNext;
	}

	nNew = pHead;
	while (nNew) {
		ItemType data;
		sNew.GetTop(data);
		nNew->data = data;
		sNew.Pop();
		nNew = nNew->pNext;
	}
}


/// My code
template<class T>
T& L1List<T>:: operator[](int i) {
	if (this->isEmpty()) {
		DSAException *ex = new DSAException(-1, "database is empty");
		throw ex;
	}
	L1Item<T>* pNew = this->_pHead;
	while (i > 0 && pNew != NULL) {
		pNew = pNew->pNext;
		i--;
	}
	if (pNew) return pNew->data;

	DSAException *ex = new DSAException(-2, "excessive limitation");
	throw ex;
}


/// My code ::: 
/// Clean all elements in LL

template<class T>
void L1List<T>::clean() {
	while (!isEmpty()) {
		removeHead();
	}
}


/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
	}
	else {
		L1Item<T> *it = new L1Item<T>(a);
		L1Item<T>   *p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = it;
	}
	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;  // bo cho nay 
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}


extern string fnameEventGB;

#endif //A01_LISTLIB_H
