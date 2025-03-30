#pragma once

class Queue {

    private:
    int* array;
    int capacity;
    int front;
    int rear;
    int count;

    public:
    Queue(int size);
    ~Queue();

    void enqueue(int item);
    int dequeue();
    int peek() const;
    bool isFull() const;
    bool isEmpty() const;
    int size() const;    

};
