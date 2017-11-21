/* 
* Queue.h
*
* Created: 17-11-2017 17:32:25
* Author: Gerhard
*/


#ifndef __QUEUE_H__
#define __QUEUE_H__
class BombermanBomb;
struct SnakeQueueData{
	short X;
	short Y;
};

template <typename T>
class Queue
{
//variables
public:
protected:
private:
	T *_array;
	unsigned char _front = 0;
	unsigned char _back = 0;
	int _length;
	int _nextIndex;
//functions
public:
	Queue();
	void Clear();
	int Length(); 
	void Enqueue(T data);
	T Dequeue();
	T Peek();
	T Peek(int indx);
	~Queue();
protected:
private:

}; //Queue

#endif //__QUEUE_H__
