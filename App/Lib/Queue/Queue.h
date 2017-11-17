/* 
* Queue.h
*
* Created: 17-11-2017 17:32:25
* Author: Gerhard
*/


#ifndef __QUEUE_H__
#define __QUEUE_H__

struct QueueData{
	short X;
	short Y;
};

class Queue
{
//variables
public:
protected:
private:
	QueueData *_array;
	unsigned char _front = 0;
	unsigned char _back = 0;

//functions
public:
	Queue();
	void Clear();
	void Enqueue(QueueData data);
	void Enqueue(short x, short y);
	QueueData Dequeue();
	~Queue();
protected:
private:

}; //Queue

#endif //__QUEUE_H__
