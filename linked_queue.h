// who: Jiahao Liang, Jianwen Qi
// why: lab_5
// when: 10-31-2021

#pragma once
#ifndef _LINKED_QUEUE_H
#define _LINKED_QUEUE_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

template<class T> class LinkedQueue;

template<class T>
class QueueNode
{
public:
	friend class LinkedQueue<T>;

private:
	T data;
	QueueNode<T> *next;
	QueueNode();
	QueueNode(const T&, QueueNode<T>* = nullptr);
};

template<class T>
QueueNode<T>::QueueNode():next(nullptr){}

template<class T>
QueueNode<T>::QueueNode(const T &data, QueueNode<T>* next):data(data), next(next){}

template<class T>
class LinkedQueue
{
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue&);
	~LinkedQueue();
	inline bool isEmpty() const noexcept;
	size_t size();
	inline T front() const;
	inline T rear() const;
	inline void enQueue(const T&);
	inline void deQueue();
	void clear();
	LinkedQueue<T>& operator=(const LinkedQueue<T>&);
	bool operator==(const LinkedQueue<T>&);
	bool operator!=(const LinkedQueue<T>&);
	friend std::ostream &operator<<(std::ostream &out, const LinkedQueue<T> &other)
	{
		if(other.isEmpty())
		{
			throw std::overflow_error("ERROR: EMPTY LINKED QUEUE");
		}
		QueueNode<T> *current = other.head->next;
		while(current != nullptr)
		{
			out << current->data << " ";
			current = current->next;
		}
		return out;
	}
	
private:
	QueueNode<T> *head;
	QueueNode<T> *tail;
};

template<class T>
LinkedQueue<T>::LinkedQueue():head(new QueueNode<T>()), tail(nullptr)
{
}

template<class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other):head(new QueueNode<T>()), tail(nullptr)
{
	if(other.isEmpty())
	{
		return;
	}
	QueueNode<T> *current = other.head->next;
	while(current != nullptr)
	{
		enQueue(current->data);
		current = current->next;
	}
}

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	clear();
	delete tail;
	head = nullptr;
	tail = nullptr;
}

template<class T>
inline bool LinkedQueue<T>::isEmpty() const noexcept
{
	return head->next == nullptr ? true : false;
}

template<class T>
size_t LinkedQueue<T>::size()
{
	if(isEmpty())
	{
		return 0;
	}
	QueueNode<T> *current = head;
	size_t count = 0;
	while(current != nullptr)
	{
		current = current->next;
		count++;
	}
	return count;
}

template<class T>
inline T LinkedQueue<T>::front() const
{
	if(isEmpty())
	{
		return -1;
	}
	return head->next->data;
}

template<class T>
inline T LinkedQueue<T>::rear() const
{
	if(isEmpty())
	{
		return -1;
	}
	return tail->data;
}

template<class T>
inline void LinkedQueue<T>::enQueue(const T& data)
{
	if(isEmpty())
	{
		tail = new QueueNode<T>(data, nullptr);
		head->next = tail;
	}
	else
	{
		tail->next = new QueueNode<T>(data, nullptr);
		tail = tail->next;
	}
}

template<class T>
inline void LinkedQueue<T>::deQueue()
{
	if(isEmpty())
	{
		throw std::overflow_error("ERROR: EMPTY LINKED STACK");
	}
	QueueNode<T> *current = head->next;
	head->next = current->next;
	delete current; current = nullptr;
}

template<class T>
void LinkedQueue<T>::clear()
{
	if(isEmpty())
	{
		return;
	}
	QueueNode<T> *current = nullptr;
	while(head->next != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
}

template<class T>
bool LinkedQueue<T>::operator==(const LinkedQueue<T>& other)
{
	if(isEmpty() && other.isEmpty())
	{
		return true;
	}
	else if(size() != other.size())
	{
		return false;
	}
	QueueNode<T> *current = head->next;
	QueueNode<T> *duplicatedCurrent = other.head->next;
	while(current != nullptr && duplicatedCurrent != nullptr)
	{
		if(current->data != duplicatedCurrent->data)
		{
			return false;
		}
		current = current->next;
		duplicatedCurrent = duplicatedCurrent->next;
	}
	return true;
}

template<class T>
bool LinkedQueue<T>::operator!=(const LinkedQueue<T>& other)
{
	if(isEmpty() && other.isEmpty())
	{
		return false;
	}
	else if(size() != other.size())
	{
		return true;
	}
	QueueNode<T> *current = head->next;
	QueueNode<T> *duplicatedCurrent = other.head->next;
	while(current != nullptr && duplicatedCurrent != nullptr)
	{
		if(current->data == duplicatedCurrent->data)
		{
			current = current->next;
			duplicatedCurrent = duplicatedCurrent->next;
		}
	}
	if(current == nullptr && duplicatedCurrent == nullptr)
	{
		return false;
	}
	return true;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T> &other)
{
	if(other.isEmpty())
	{
		clear();
		return *this;
	}
	if(this == &other)
	{
		return *this;
	}
	if(!isEmpty())
	{
		clear();
		head = new QueueNode<T>();
		tail = nullptr;
	}
	QueueNode<T> *current = other.head->next;
	while(current != nullptr)
	{
		enQueue(current->data);
		current = current->next;
	}
	return *this;
}

#endif