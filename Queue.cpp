// Noga Peled
// nogapeled19@gmail.com

#include "Queue.hpp"
#include <iostream>
#include <stdexcept>

// Constructor: initializes a queue with given capacity
Queue::Queue(int size) : capacity(size), front(0), rear(-1), count(0) {

    array = new int[capacity];
}

Queue::~Queue() // Destructor: frees the allocated array
{
    delete[] array;
}

void Queue::enqueue(int item) // Adds an item to the rear of the queue
{
    if (isFull())
    {
        throw std::overflow_error("The queue is full.");
    }
    rear = (rear + 1) % capacity;
    array[rear] = item;
    count = count + 1;
    
}

int Queue::dequeue() // Removes and returns the front item of the queue
{
    if (isEmpty())
    {
        throw std::underflow_error("The queue is empty.");
    }

    int item = array[front];
    front = (front + 1) % capacity;
    count = count - 1;
    return item;
    
}

int Queue::peek() const // Returns the front item without removing it
{
    if (isEmpty())
    {
        throw std::underflow_error("The queue is empty.");
    }
    return array[front];

}

bool Queue::isFull() const // Returns true if the queue is full
{
    return count == capacity;
}

bool Queue::isEmpty() const // Returns true if the queue is empty
{
    return count == 0;
}

int Queue::cap() const // Returns the total capacity of the queue
{
    return capacity;
}