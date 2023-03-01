//
// circular_queue.h
// Created by Jiahao Liang on 11/1/21.

#pragma once
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdexcept>
#include <memory>
#include <array>
#include <cstddef>
#include <iostream>

template<class T, size_t N>
class CircularQueue
{
public:
	CircularQueue();
	~CircularQueue();
	bool isEmpty() const noexcept;
	bool isFull() const noexcept;
	size_t size() const noexcept;
	void enQueue(const T&);
	void deQueue();
	T getFront() const;
	T getRear() const;
	friend std::ostream& operator<<(std::ostream &out, const CircularQueue &other)
	{
		for(size_t i = other.front; i != other.rear; i = (i+1) % N)
		{
			out << other.queueArray->at(i) << " ";
		}
		return out;
	}
	
private:
	std::unique_ptr<std::array<T, N>> queueArray;
	int front;
	int rear;
};

template<class T, size_t N>
CircularQueue<T, N>::CircularQueue():queueArray(std::make_unique<std::array<T,N>>(std::array<T,N>{})), front(0), rear(0){}

template<class T, size_t N>
CircularQueue<T, N>::~CircularQueue()
{
	queueArray.reset();
	queueArray = nullptr;
}

template<class T, size_t N>
bool CircularQueue<T, N>::isEmpty() const noexcept
{
	return front == rear ? true : false;
}

template<class T, size_t N>
bool CircularQueue<T, N>::isFull() const noexcept
{
	return front == (rear+1) % N ? true : false;
}

template<class T, size_t N>
size_t CircularQueue<T, N>::size() const noexcept
{
	return (rear + N - front) % N;
}

template<class T, size_t N>
void CircularQueue<T, N>::enQueue(const T &data)
{
	if(isFull())
	{
		throw std::overflow_error("ERROR: OVERFLOW");
	}
	queueArray->at(rear) = data;
	rear = (rear + 1) % N;
}

template<class T, size_t N>
void CircularQueue<T, N>::deQueue()
{
	if(isEmpty())
	{
		throw std::underflow_error("ERROR: UNDERFLOW");
	}
	front = (front + 1) % N;
}

template<class T, size_t N>
T CircularQueue<T, N>::getFront() const
{
	if(isEmpty())
	{
		return -1;
	}
	return queueArray->at(front);
}

template<class T, size_t N>
T CircularQueue<T, N>::getRear() const
{
	if(isEmpty())
	{
		return -1;
	}
	return queueArray->at(rear-1);
}

#endif