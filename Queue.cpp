#include "Queue.hpp"
#include <iostream>
#include <stdexcept>

Queue::Queue(int size) : capacity(0), front(0), rear(-1), count(0) {

    try
    {
        array = new int[capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "Failed to allocate memory for the queue : " << e.what() << std::endl;
    }
    
}

Queue::~Queue()
{
    delete[] array;
}

void Queue::enqueue(int item)
{
    if (isFull())
    {
        throw std::overflow_error("The queue is full.");
    }
    rear = (rear + 1) % capacity;
    array[rear] = item;
    count = count + 1;
    
}

int Queue::dequeue()
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

int Queue::peek() const
{
    if (isEmpty())
    {
        throw std::underflow_error("The queue is empty.");
    }
    return array[front];

}

bool Queue::isFull() const
{
    return count == capacity;
}

bool Queue::isEmpty() const
{
    return count == 0;
}

int Queue::size() const
{
    return capacity;
}