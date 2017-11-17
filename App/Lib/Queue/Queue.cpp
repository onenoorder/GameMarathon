/* 
* Queue.cpp
*
* Created: 17-11-2017 17:32:24
* Author: Gerhard
*/


#include "Queue.h"

// default constructor
Queue::Queue()
{
	_array = new QueueData[200];
} //Queue

void Queue::Clear(){
	delete[] _array;
	_array = new QueueData[200];
}

void Queue::Enqueue(QueueData data){
	if (_back < 200) {
		_array[_back] = data;
		_back++;
		} else {
		_array[0] = data;
		_back = 1;
	}
}

void Queue::Enqueue(short x, short y){
	Enqueue(QueueData { x, y });
}

QueueData Queue::Dequeue(){
	QueueData data = _array[_front];
	_array[_front] = {};
	if (_front < 200) {
		_front++;
	}
	else {
		_front = 0;
	}
	return data;
}

// default destructor
Queue::~Queue()
{
	delete[] _array;
} //~Queue
