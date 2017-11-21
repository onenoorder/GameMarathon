/* 
* Queue.cpp
*
* Created: 17-11-2017 17:32:24
* Author: Gerhard
*/

#include "Queue.h"

template class Queue<SnakeQueueData>;

template<typename T>
Queue<T>::Queue()
{
	_array = new T[200];
} //Queue

template<typename T>
void Queue<T>::Clear(){
	delete[] _array;
	_array = new T[200];
}

template<typename T>
void Queue<T>::Enqueue(T data){
	if (_back < 200) {
		_array[_back] = data;
		_back++;
		} else {
		_array[0] = data;
		_back = 1;
	}
}

template<typename T>
T Queue<T>::Dequeue(){
	T data = _array[_front];
	_array[_front] = {};
	if (_front < 200) {
		_front++;
	}
	else {
		_front = 0;
	}
	return data;
}

template<typename T>
Queue<T>::~Queue()
{
	delete[] _array;
} //~Queue
